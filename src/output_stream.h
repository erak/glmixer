#pragma once

#include <iostream>
#include <thread>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

class output_stream {

public:
    output_stream();
    ~output_stream();

    void post(const size_t size);

private:
    void log(const std::string message) const;
    void run();
    
    void stream(const size_t size);    

    std::shared_ptr<boost::asio::io_service>        io_service_;
    std::shared_ptr<boost::asio::io_service::work>  work_;

    boost::thread_group         threads_;
};