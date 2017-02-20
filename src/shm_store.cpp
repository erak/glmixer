#include <shm_store.h>

#include <iostream>
#include <qdebug.h>

boost::mutex g_stream_lock;

shm_store::shm_store()
    : io_service_(new boost::asio::io_service)
    , work_(new boost::asio::io_service::work(*io_service_))
{
    threads_.create_thread(boost::bind(&shm_store::run, this));
}

shm_store::~shm_store()
{
    work_.reset();
	threads_.join_all();
}

void shm_store::post(const QImage& image)
{
    io_service_->post(boost::bind(&shm_store::write, this, image));
}

void shm_store::write(const QImage& image)
{
    // auto bits = image.bits();
    // QImage image(image.constBits(), image.width(), image.height(), QImage::Format_ARGB32);
    auto matrix = cv::Mat(image.height(), image.width(), CV_8UC3, 
                   const_cast<uchar*>(image.bits()), 
                   image.bytesPerLine()).clone();
    

}

void shm_store::run()
{
    io_service_->run();
}





