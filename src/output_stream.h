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

    void post();

private:
    boost::asio::io_service     io_service_;
    boost::thread_group         threads_;

    std::shared_ptr< boost::asio::io_service::work > work_;
};