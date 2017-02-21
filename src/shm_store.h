#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <thread>
#include <mutex>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <QImage>

using namespace boost::interprocess;

class shm_store {

public:
    shm_store();
    ~shm_store();

    void post(const QImage& image);

private:
    void run();    
    void write(const QImage& image);

    std::shared_ptr<boost::asio::io_service> io_service_;
    std::shared_ptr<boost::asio::io_service::work> work_;

    boost::thread_group threads_;

    std::shared_ptr<managed_shared_memory> segment_;

    size_t* texture_;
    size_t counter_;
};
