#include <output_stream.h>

#include <iostream>
#include <qdebug.h>

output_stream::output_stream()
    : work_(new boost::asio::io_service::work( io_service_ ))
{
    threads_.create_thread([this]() {
        std::cout << "Thread Start\n";
	    io_service_.run();
	    std::cout << "Thread Finish\n";
    });
}

output_stream::~output_stream()
{
    io_service_.stop();
	threads_.join_all();
}

void output_stream::post()
{
    // post to boost work object
}

