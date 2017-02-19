/*
 * Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */

#ifndef NV_IMAGE_GL
#define NV_IMAGE_GL

#include <cuda.h>
#include <GL/glew.h>

#if defined(__APPLE__) || defined(__MACOSX)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#define PAD_ALIGN(x,mask) ( (x + mask) & ~mask )


namespace cuda {


const int Format2Bpp[] = { 1, 4, 0 };

class ImageGL
{
    public:
        enum PixelFormatGL
        {
            LUMINANCE_PIXEL_FORMAT,
            BGRA_PIXEL_FORMAT,
            UNKNOWN_PIXEL_FORMAT
        };

        ImageGL(unsigned int nDispWidth, unsigned int nDispHeight,
                PixelFormatGL ePixelFormat = BGRA_PIXEL_FORMAT);

        // Destructor
        ~ImageGL();

        void
        registerAsCudaResource();

        void
        unregisterAsCudaResource();

        void
        setCUDAcontext(CUcontext oContext);

        void
        setCUDAdevice(CUdevice oDevice);

        int Bpp()
        {
            return Format2Bpp[(int)e_PixFmt_];
        }

        bool
        isCudaResource()
        const;

        // Map this image's DX surface into CUDA memory space.
        // Parameters:
        //      ppImageData - point to point to image data. On return this
        //          pointer references the mapped data.
        //      pImagePitch - pointer to image pitch. On return of this
        //          pointer contains the pitch of the mapped image surface.
        //      This method will fail, if this image is not a registered CUDA resource.
        void
        map(CUdeviceptr *ppImageData, size_t *pImagePitch);

        void
        unmap();

        // Clear the image.
        // Parameters:
        //      nClearColor - the luminance value to clear the image to. Default is white.
        // Note:
        //      This method will not work if this image is not registered as a CUDA resource at the
        //      time of this call.
        void
        clear(unsigned char nClearColor = 0xff);

        unsigned int
        nWidth()
        const
        {
            return nWidth_;
        }

        unsigned int
        nHeight()
        const
        {
            return nHeight_;
        }

        GLuint getPBO()
        {
            return gl_pbo_;
        }


    private:
        GLuint gl_pbo_;     // OpenGL pixel buffer object

        unsigned int nWidth_;
        unsigned int nHeight_;
        PixelFormatGL e_PixFmt_;
        bool bIsProgressive_;
        bool bIsCudaResource_;

        CUcontext oContext_;
        CUdevice  oDevice_;
};

}

#endif // IMAGE_GL

