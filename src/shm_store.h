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

#include <QImage>

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
};