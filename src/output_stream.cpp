#include <output_stream.h>

#include <iostream>
#include <qdebug.h>

boost::mutex g_stream_lock;

output_stream::output_stream()
    : io_service_(new boost::asio::io_service)
    , work_(new boost::asio::io_service::work(*io_service_))
{
    threads_.create_thread(boost::bind(&output_stream::run, this));
}

output_stream::~output_stream()
{
    work_.reset();
	threads_.join_all();
}

void output_stream::post(const QImage& image)
{
    io_service_->post(boost::bind(&output_stream::write, this, image));
}

void output_stream::write(const QImage& image)
{
    auto bits = image.bits();
}

void output_stream::run()
{
    io_service_->run();
}

void output_stream::log(const std::string message) const
{
    fprintf(stderr, std::string("output_stream - " + message + "\n").c_str());
}





