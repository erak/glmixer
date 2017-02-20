#include <output_stream.h>

#include <iostream>
#include <qdebug.h>

boost::mutex g_stream_lock;

output_stream::output_stream()
    : io_service_(new boost::asio::io_service)
    , work_(new boost::asio::io_service::work(*io_service_))
{
    threads_.create_thread(boost::bind(&output_stream::run, this));
    // video_.open("gl_mixer_stream.avi", 
    //     // cv::VideoWriter::fourcc('H','2','6','4'), 25, cv::Size(640, 480), true);
    //     // cv::VideoWriter::fourcc('F','M','P','4'), 25, cv::Size(800, 600), true);
    //     cv::VideoWriter::fourcc('P','I','M','1'), 60, cv::Size(800, 600), true);
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
    // auto bits = image.bits();
    // QImage image(image.constBits(), image.width(), image.height(), QImage::Format_ARGB32);
    auto matrix = cv::Mat(image.height(), image.width(), CV_8UC3, 
                   const_cast<uchar*>(image.bits()), 
                   image.bytesPerLine()).clone();

    // cv::namedWindow( "image", 1 );
    // cv::imshow("image", matrix);

    // if (video_.isOpened())
    // {
    //     video_ << matrix;
    // }
}

void output_stream::run()
{
    io_service_->run();
}

void output_stream::log(const std::string message) const
{
    fprintf(stderr, std::string("output_stream - " + message + "\n").c_str());
}





