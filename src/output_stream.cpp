#include <output_stream.h>

#include <iostream>

output_stream::output_stream() 
    : streaming_(false)
{
}

void output_stream::start()
{
    thread_ = std::thread([this]()
    {   
        set_streaming(true);

        while(is_streaming())
        {
            std::cout << "streaming..." << std::endl;
        }
    });
}

void output_stream::stop()
{
    set_streaming(false);
    thread_.join();
}

void output_stream::send()
{
    // std::lock_guard<std::mutex> lock(lock_);
}

bool output_stream::is_streaming()
{
    std::lock_guard<std::mutex> lock(lock_);
    return streaming_;
}

void output_stream::set_streaming(const bool streaming)
{
    std::lock_guard<std::mutex> lock(lock_);
    streaming_ = streaming;
}
