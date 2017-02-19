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

#include "ImageGL.h"

#include <cuda.h>
#include <cudaGL.h>

#include <cassert>

#include "helper_cuda_drvapi.h"


namespace cuda {


ImageGL::ImageGL(unsigned int nDispWidth,
                 unsigned int nDispHeight,
                 PixelFormatGL ePixelFormat)
    : nWidth_(nDispWidth)
    , nHeight_(nDispHeight)
    , e_PixFmt_(ePixelFormat)
    , bIsCudaResource_(false)
{

    glGenBuffersARB(1, &gl_pbo_);

    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, gl_pbo_);
    glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, nWidth_*nHeight_*4, NULL, GL_STREAM_DRAW_ARB);
    glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

    registerAsCudaResource();

}

ImageGL::~ImageGL()
{
    unregisterAsCudaResource();

    glDeleteBuffersARB(1, &gl_pbo_);
}

void
ImageGL::registerAsCudaResource()
{
    // register the OpenGL resources that we'll use within CD
    checkCudaErrors(cuGLRegisterBufferObject(gl_pbo_));
    getLastCudaDrvErrorMsg("cuGLRegisterBufferObject (gl_pbo_) failed");
    bIsCudaResource_ = true;
}

void
ImageGL::unregisterAsCudaResource()
{
    cuCtxPushCurrent(oContext_);
    checkCudaErrors(cuGLUnregisterBufferObject(gl_pbo_));
    bIsCudaResource_ = false;
    cuCtxPopCurrent(NULL);
}


void
ImageGL::setCUDAcontext(CUcontext oContext)
{
    oContext_ = oContext;
    printf("ImageGL::CUcontext = %08lx\n", (unsigned long)oContext);
}

void
ImageGL::setCUDAdevice(CUdevice oDevice)
{
    oDevice_ = oDevice;
    printf("ImageGL::CUdevice  = %08lx\n", (unsigned long)oDevice);
}

bool
ImageGL::isCudaResource()
const
{
    return bIsCudaResource_;
}

void
ImageGL::map(CUdeviceptr *pImageData, size_t *pImagePitch)
{
    checkCudaErrors(cuGLMapBufferObject(pImageData, pImagePitch, gl_pbo_));
    assert(0 != *pImagePitch);
}

void
ImageGL::unmap()
{
    checkCudaErrors(cuGLUnmapBufferObject(gl_pbo_));
}

void
ImageGL::clear(unsigned char nClearColor)
{
    // Can only be cleared if surface is a CUDA resource
    assert(bIsCudaResource_);

    size_t       imagePitch;
    CUdeviceptr  pImageData;

    map(&pImageData, &imagePitch);
    // clear the surface to solid white
    checkCudaErrors(cuMemsetD8(pImageData, nClearColor, nWidth_*nHeight_* Bpp()));
    unmap();

}

}
