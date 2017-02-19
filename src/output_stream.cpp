#include <output_stream.h>

#include <iostream>
#include <qdebug.h>

output_stream::output_stream()
    : work_(new boost::asio::io_service::work( io_service_ ))
{
    threads_.create_thread([this]() {
        fprintf(stderr, "output_stream::output_stream() - Thread start...\n");
	    io_service_.run();
	    fprintf(stderr, "output_stream::output_stream() - Thread finish...\n");
    });
}

output_stream::~output_stream()
{
    io_service_.stop();
	threads_.join_all();
}

void output_stream::post()
{

}

