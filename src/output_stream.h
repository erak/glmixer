#pragma once

#include <iostream>
#include <thread>
#include <mutex>

class output_stream {

public:
    output_stream();

    void start();
    void stop();
    void send();

private:
    bool is_streaming();
    void set_streaming(const bool);

    bool        streaming_;
    std::mutex  lock_;
    std::thread thread_;
};