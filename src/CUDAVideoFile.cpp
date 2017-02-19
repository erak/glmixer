#include "CUDAVideoFile.moc"

// NVIdia libCUDADecoder
#include "cudaModuleMgr.h"
#include "cudaProcessFrame.h"
#include "helper_cuda_drvapi.h"

// GLMixer
#include "defines.h"

// utility
#include <QApplication>


bool CUDAVideoFile::cudaregistered = false;
CUdevice CUDAVideoFile::g_oDevice = 0;



class CUDADecodingThread: public videoFileThread
{
public:
    CUDADecodingThread(CUDAVideoFile *video) : videoFileThread(video)
    {

    }
    ~CUDADecodingThread()
    {

    }

    void run();

private:

};




CUDAVideoFile::CUDAVideoFile(QObject *parent, bool generatePowerOfTwo,
                             int swsConversionAlgorithm, int destinationWidth,
                             int destinationHeight) :
    VideoFile(parent, generatePowerOfTwo, swsConversionAlgorithm, destinationWidth, destinationHeight), apVideoSource(0), apFrameQueue(0), apVideoDecoder(0), apVideoParser(0)
{

//    AllocationException().raise();

    if (!cudaregistered) {
        cuInit(0);

        CUdevice cuda_device;
        cuda_device = findCudaDeviceDRV();
        checkCudaErrors(cuDeviceGet(&g_oDevice, cuda_device));

        // get device name
        char deviceName[256];
        checkCudaErrors(cuDeviceGetName(deviceName, 256, g_oDevice));

        // check minimum capability
        int bSupported = checkCudaCapabilitiesDRV(1, 1, g_oDevice);
        if (!bSupported)
        {
            qWarning("  -> GPU: \"%s\" does not meet the minimum spec of SM 1.1\n", deviceName);
            qWarning("  -> A GPU with a minimum compute capability of SM 1.1 or higher is required.\n");
            AllocationException().raise();
        }

        // get compute capabilities & memory
        int major, minor;
        size_t totalGlobalMem;
        checkCudaErrors(cuDeviceComputeCapability(&major, &minor, g_oDevice));
        checkCudaErrors(cuDeviceTotalMem(&totalGlobalMem, g_oDevice));
        qDebug()<< "Found CUDA GPU Device" << deviceName << "(SM "<< major << '.' << minor << "compute capability, " << (float)totalGlobalMem/(1024*1024) << "MB memory)";

        cudaregistered = true;
    }

    // initialize fields
    g_oContext = 0;
    g_pCudaModule = 0;
    g_kernelNV12toARGB = 0;
    g_kernelPassThru = 0;
    g_CtxLock = NULL;
    g_KernelSID = 0;

    // Create CUDA context
    checkCudaErrors(cuCtxCreate(&g_oContext, CU_CTX_BLOCKING_SYNC, g_oDevice));

    // Create CUDA Module Manager : Open PTX pre-compiled CUDA assembly
    // TODO : NV Runtime compilation of the PTX
    try {

        g_pCudaModule = new CUmoduleManager("NV12ToARGB_drvapi64.ptx", qPrintable(QApplication::applicationDirPath()), 2, 2, 2);
    }
    catch (char const *p_file)
    {
        // If the CUmoduleManager constructor fails to load the PTX file, it will throw an exception
        qWarning("\n>> CUmoduleManager::Exception!  %s not found!\n", p_file);
        qWarning(">> Please rebuild NV12ToARGB_drvapi.cu or re-install this sample.\n");
        AllocationException().raise();
    }

    // Get functions from CUDA Module
    g_pCudaModule->GetCudaFunction("NV12ToARGB_drvapi",   &g_kernelNV12toARGB);
//    g_pCudaModule->GetCudaFunction("Passthru_drvapi",     &g_kernelPassThru);

    // create the CUDA resources

    // bind the context lock to the CUDA context
    CUresult result = cuvidCtxLockCreate(&g_CtxLock, g_oContext);
    if (result != CUDA_SUCCESS)
    {
        qWarning("cuvidCtxLockCreate failed: %d\n", result);
        AllocationException().raise();
    }

    // un-bind context
    CUcontext cuCurrent = NULL;
    result = cuCtxPopCurrent(&cuCurrent);
    if (result != CUDA_SUCCESS)
    {
        printf("cuCtxPopCurrent: %d\n", result);
        AllocationException().raise();
    }

    if (decod_tid)
        delete decod_tid;

    decod_tid = new CUDADecodingThread(this);
    QObject::connect(decod_tid, SIGNAL(failed()), this, SIGNAL(failed()));

}

CUDAVideoFile::~CUDAVideoFile()
{

    if (g_CtxLock)
        checkCudaErrors(cuvidCtxLockDestroy(g_CtxLock));

    cleanup(true);
}

bool CUDAVideoFile::isOpen() const
{
    return apVideoSource != NULL;
}

bool CUDAVideoFile::open(QString file, double markIn, double markOut, bool ignoreAlphaChannel)
{
    // Open the file with libav to get info
    // TODO replace by pure CUDA parsing functions
    VideoFile::open(file, markIn, markOut, ignoreAlphaChannel);
    if (video_st->nb_frames < 2)
        return false;

    //
    //  Create Video Manager (aka VideoSource)
    //
    // Push the current CUDA context
    CUresult result = cuCtxPushCurrent(g_oContext);

    // frame queue
    apFrameQueue = new cuda::FrameQueue();
    if (!apFrameQueue)
        return false;

    // Video Manager
    apVideoSource = new cuda::VideoManager(file.toStdString(), apFrameQueue);
    if (!apVideoSource)
        return false;

    // retrieve the video source (width,height)
    apVideoSource->getSourceDimensions(targetWidth, targetHeight);
    // set image format
    targetFormat = AV_PIX_FMT_RGBA;


    // TODO : handle other modes than CUVID
    g_eVideoCreateFlags = cudaVideoCreate_PreferCUVID;

    //
    //  Create Video Decoder and parser
    //

    apVideoDecoder = new cuda::VideoDecoder(apVideoSource->format(), g_oContext, g_eVideoCreateFlags, g_CtxLock);
    if (!apVideoDecoder)
        return false;

    apVideoParser = new cuda::VideoParser(apVideoDecoder, apFrameQueue, &g_oContext);
    if (!apVideoParser)
        return false;

    apVideoSource->setParser(*apVideoParser);

    // Create a Stream ID for handling Readback

    checkCudaErrors(cuStreamCreate(&g_KernelSID,   0));
    printf("   CUDA Streams (%s) <g_KernelSID   = %p>\n", ((g_KernelSID   == 0) ? "Disabled" : "Enabled"), g_KernelSID);

//    checkCudaErrors(cuStreamCreate(&g_ReadbackSID, 0));
//    printf("   CUDA Streams (%s) <g_ReadbackSID = %p>\n", ((g_ReadbackSID == 0) ? "Disabled" : "Enabled"), g_ReadbackSID);

    // free context
    CUcontext cuCurrent = NULL;
    result = cuCtxPopCurrent(&cuCurrent);
    if (result != CUDA_SUCCESS)
    {
        printf("cuCtxPopCurrent: %d\n", result);
        return false;
    }

    return true;
}

void CUDAVideoFile::close()
{
    // TODO : close libav as we still open the file with libav for getting info
    VideoFile::close();

    cleanup();
}

void CUDAVideoFile::start()
{
    // nothing to play if there is ONE frame only...
//    if ( getNumFrames() < 2)
        return;

    if (quit)
    {
        qDebug() << filename << QChar(124).toLatin1() << tr("CUDAVideoFile Starting.");


        // reset quit flag
        quit = false;

        // start timer and decoding threads
        ptimer->start();
        decod_tid->start();

        if(apVideoSource)
            apVideoSource->start();

        qDebug() << filename << QChar(124).toLatin1() << tr("CUDAVideoFile Started.");
    }

    /* say if we are running or not */
    emit running(!quit);
}

void CUDAVideoFile::stop()
{
    if (!quit)
    {
        qDebug() << filename << QChar(124).toLatin1() << tr("CUDAVideoFile Stopping.");

        // request quit
        quit = true;

        // unlock all conditions
        pictq_cond->wakeAll();
        seek_cond->wakeAll();

        // wait for thread to end
        while ( !decod_tid->wait( 500 ) ) {
            // try to enforce exit
            decod_tid->forceQuit();
            // unlock all conditions
            pictq_cond->wakeAll();
            seek_cond->wakeAll();
        }

        if (apVideoSource) {
            apFrameQueue->endDecode();
            apVideoSource->stop();
        }

        qDebug() << filename << QChar(124).toLatin1() << tr("CUDAVideoFile Stopped.");
    }

    /* say if we are running or not */
    emit running(!quit);

}

void CUDAVideoFile::requestSeek(double time, bool lock)
{

}

void CUDAVideoFile::cleanup(bool destroyContext)
{
    if (apFrameQueue)
        delete apFrameQueue;
    apFrameQueue = 0;

    if (apVideoDecoder)
        delete apVideoDecoder;
    apVideoDecoder = 0;

    if (apVideoParser)
        delete apVideoParser;
    apVideoParser = 0;

    if (apVideoSource)
        delete apVideoSource;
    apVideoSource = 0;

    if (g_KernelSID)
        checkCudaErrors(cuStreamDestroy(g_KernelSID));

//    if (g_ReadbackSID)
//        checkCudaErrors(cuStreamDestroy(g_ReadbackSID));

    if (destroyContext && g_oContext) {
        checkCudaErrors(cuCtxDestroy(g_oContext));
        g_oContext = 0;
    }
}


void CUDADecodingThread::run()
{
    CUVIDPARSERDISPINFO oDisplayInfo;

    size_t pFramePitch = 0;

    CUDAVideoFile *cudastream = (CUDAVideoFile *) is;

    _working = true;
    while (is && !is->quit && !_forceQuit)
    {
        //
        //        Copy Decoded Frame To Texture
        //

        if ( cudastream->apFrameQueue->dequeue(&oDisplayInfo) )
        {
            CCtxAutoLock lck(cudastream->g_CtxLock);

            // Push the current CUDA context
            CUresult result = cuCtxPushCurrent(cudastream->g_oContext);

            CUdeviceptr  pDecodedFrame = 0;
            CUdeviceptr  pInteropFrame = 0;

            CUVIDPROCPARAMS oVideoProcessingParameters;
            memset(&oVideoProcessingParameters, 0, sizeof(CUVIDPROCPARAMS));
            oVideoProcessingParameters.progressive_frame = oDisplayInfo.progressive_frame;
            oVideoProcessingParameters.second_field      = 0;
            oVideoProcessingParameters.top_field_first   = oDisplayInfo.top_field_first;
            oVideoProcessingParameters.unpaired_field    = true;

            unsigned int nWidth = 0;
            unsigned int nHeight = 0;
            unsigned int nDecodedPitch = 0;

            // map decoded video frame to CUDA surface
            cudastream->apVideoDecoder->mapFrame(oDisplayInfo.picture_index, &pDecodedFrame, &nDecodedPitch, &oVideoProcessingParameters);
            nWidth  = PAD_ALIGN(cudastream->apVideoDecoder->targetWidth() , 0x3F);
            nHeight = PAD_ALIGN(cudastream->apVideoDecoder->targetHeight(), 0x0F);

            // compute pts
            double pts = (double) oDisplayInfo.timestamp / (double) cudastream->apVideoParser->getClockRate();

            //
            //  map CUDA surface to Video Picture
            //

            VideoPicture::Action actionFrame = VideoPicture::ACTION_SHOW;
            VideoPicture *vp = new VideoPicture();

//            unsigned char          *g_bFrameData;
//            checkCudaErrors( cuMemAllocHost((void **)&g_bFrameData, (nDecodedPitch * nHeight * 3 / 2)));

//            result = cuMemcpyDtoHAsync(g_bFrameData, pDecodedFrame, (nDecodedPitch * nHeight * 3 / 2), cudastream->g_ReadbackSID);

//            if (result != CUDA_SUCCESS)
//            {
//                printf("cuMemcpyDtoHAsync returned %d\n", (int)result);
//                checkCudaErrors(result);
//            }

            checkCudaErrors(cuMemAlloc(&pInteropFrame, cudastream->apVideoDecoder->targetWidth() * cudastream->apVideoDecoder->targetHeight() * 2));
            pFramePitch = cudastream->apVideoDecoder->targetWidth() * 2;



            //
            //  CUDA Post-process Frame
            //
            //

            static  bool g_bUpdateCSC = true;
            if (g_bUpdateCSC)
            {
                // CCIR 601/709
                float hueColorSpaceMat[9];
                eColorSpace        g_eColorSpace = ITU601;
                float              g_nHue        = 0.0f;
                setColorSpaceMatrix(g_eColorSpace,    hueColorSpaceMat, g_nHue);
                updateConstantMemory_drvapi(cudastream->g_pCudaModule->getModule(),
                                            hueColorSpaceMat);
                g_bUpdateCSC = false;
            }
            // TODO: Stage for handling video post processing

            // Final Stage: NV12toARGB color space conversion
            CUresult eResult;
            eResult = cudaLaunchNV12toARGBDrv(pDecodedFrame, nDecodedPitch,
                                              pInteropFrame, pFramePitch,
                                              nWidth, nHeight,
                                              cudastream->g_kernelNV12toARGB,
                                              cudastream->g_KernelSID);


            //
            //  queue the video picture with the imageGL
            //

            vp->fill(pInteropFrame, pts);
            vp->addAction(actionFrame);

            // wait until we have space for a new pic
            // the condition is released in video_refresh_timer()
            is->pictq_mutex->lock();
            while ( (is->pictq.count() > is->pictq_max_count) && !is->quit )
                is->pictq_cond->wait(is->pictq_mutex);
            is->pictq_mutex->unlock();


            /* now we inform our display thread that we have a pic ready */
            is->pictq_mutex->lock();
            // enqueue this picture in the queue
            is->pictq.enqueue(vp);
            // inform about the new size of the queue
            is->pictq_mutex->unlock();

            //
            // Done for this frame
            //

            // unmap video frame
            // unmapFrame() synchronizes with the VideoDecode API (ensures the frame has finished decoding)
            cudastream->apVideoDecoder->unmapFrame(pDecodedFrame);
            // release the frame, so it can be re-used in decoder
            cudastream->apFrameQueue->releaseFrame(&oDisplayInfo);

            // Detach from the Current thread
            checkCudaErrors(cuCtxPopCurrent(NULL));

        }

        // check if decoding has come to an end.
        // if yes, signal the app to shut down.
        if (cudastream->apFrameQueue->isDecodeFinished())
        {

            // If we want to loop reload the video file and restart
            if ( cudastream->loop_video )
            {
//                reinitCudaResources();
//                g_pVideoSource->start();
            }

        }


    } // end while

    _working = false;


    // if normal exit through break (couldn't get any more packet)
    if (is) {
        cudastream->cleanup();
    }

}

