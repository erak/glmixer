#ifndef CUDAVIDEOFILE_H
#define CUDAVIDEOFILE_H

#include "VideoFile.h"
#include "VideoManager.h"
#include "FrameQueue.h"
#include "VideoDecoder.h"
#include "VideoParser.h"
#include "ImageGL.h"



class CUDAVideoFile : public VideoFile
{    
    Q_OBJECT

    friend class CUDADecodingThread;

public:
    CUDAVideoFile(QObject *parent = 0,  bool generatePowerOfTwo = false,
                  int swsConversionQuality = 0, int destinationWidth = 0,
                  int destinationHeight = 0);

    virtual  ~CUDAVideoFile();

    bool open(QString file, double  markIn = -1.0, double  markOut = -1.0, bool ignoreAlphaChannel = false);
    bool isOpen() const;
    void close();
    void start();
    void stop();

private:

    void requestSeek(double time, bool lock = false);

    // CUDA wrapper
    cuda::VideoManager *apVideoSource;
    cuda::FrameQueue *apFrameQueue;
    cuda::VideoDecoder *apVideoDecoder;
    cuda::VideoParser *apVideoParser;
    void cleanup(bool destroyContext = false);

    // CUDA internal
    cudaVideoCreateFlags g_eVideoCreateFlags;
    CUcontext          g_oContext;
    class CUmoduleManager   *g_pCudaModule;
    CUfunction         g_kernelNV12toARGB;
    CUfunction         g_kernelPassThru;
    CUvideoctxlock     g_CtxLock;
    CUstream           g_KernelSID;
//    CUstream           g_ReadbackSID;


    // registration global of CUDA
    static bool cudaregistered;
    static CUdevice g_oDevice;

};

#endif // CUDAVIDEOFILE_H
