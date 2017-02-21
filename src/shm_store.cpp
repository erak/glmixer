#include <shm_store.h>

#include <iostream>
#include <qdebug.h>

using namespace boost::interprocess;

boost::mutex g_stream_lock;

shm_store::shm_store()
    : io_service_(new boost::asio::io_service)
    , work_(new boost::asio::io_service::work(*io_service_))
    , temp_texture_(new cv::Mat())
{
    shared_memory_object::remove("glmtexture");

    segment_.reset(new managed_shared_memory(create_only, "glmtexture", 65536));
    texture_ = segment_->construct<cv::Mat>("tex")(*temp_texture_);
    index_ = segment_->construct<size_t>("index")(0);

    threads_.create_thread(boost::bind(&shm_store::run, this));
}

shm_store::~shm_store()
{
    work_.reset();
	threads_.join_all();

    segment_->destroy<cv::Mat>("tex");
    segment_->destroy<size_t>("index");

    shared_memory_object::remove("glmtexture");
}

void shm_store::post(const QImage& image)
{
    io_service_->post(boost::bind(&shm_store::write, this, image));
}

void shm_store::write(const QImage& image)
{
    // auto bits = image.bits();
    // QImage image(image.constBits(), image.width(), image.height(), QImage::Format_ARGB32);
    
    temp_texture_.reset(new cv::Mat(image.height(), image.width(), CV_8UC3,
                        const_cast<uchar*>(image.bits()),
                        image.bytesPerLine())/*.clone()*/);
    *index_ = *index_ + 1;

//    cv::imshow("image", *texture_);
}

void shm_store::run()
{
    io_service_->run();
}
