#include <conio.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>

#include "hist.hpp"

using cv::COLOR_BGR2GRAY;
using cv::Scalar;
using cv::Size;
using cv::VideoCapture;
using cv::waitKey;
using std::cerr;
using std::endl;
using std::ref;
using std::thread;

bool exitFlag = 0; // 此标志是为了当图像显示线程结束时，结束图像处理线程

void imsProcess(Mat& hist_img, Mat& gray_img, Mat& equal_hist_img, Mat& enhance_img)
{
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        cerr << "Couldn't open capture..." << endl;
        exit(-1);
    }
    /* 直方图均衡化 */
    int gray_scale = 128;
    Mat hist_val(gray_scale, 1, CV_16UC3, Scalar(0, 0, 0));
    Mat equal_hist_val(hist_val);
    Mat frame;
    while(!exitFlag)
    {
        /* 读取视频的一帧 */
        cap >> frame;
        if(frame.empty()) continue;
        resize(frame, frame, Size(512, 384));
        cvtColor(frame, gray_img, COLOR_BGR2GRAY);
        calcGrayHist(gray_img, gray_scale, hist_val);
        hist_img        = plotHist(hist_val, 512, 384);
        vector<int> map = histEqual(hist_val, equal_hist_val);
        equal_hist_img  = plotHist(hist_val, 512, 384);
        enhanceGrayImage(gray_img, enhance_img, map);
    }
}

void imsShow(Mat& hist_img, Mat& gray_img, Mat& equal_hist_img, Mat& enhance_img)
{
    while(true)
    {
        imshow("Hist", hist_img);
        imshow("Gray_Image", gray_img);
        imshow("Equal Hist", equal_hist_img);
        imshow("Enhance Image", enhance_img);
        if(waitKey(10) >= 0 || _kbhit())
        {
            exitFlag = 1;
            break;
        }
    }
}

int exp1_main()
{
    Mat    gray_img(384, 512, CV_8UC1, Scalar(0));
    Mat    hist_img(gray_img);
    Mat    equal_hist_img(gray_img);
    Mat    enhance_img(384, 512, CV_8UC1, Scalar(0));
    thread improThread(imsProcess, ref(hist_img), ref(gray_img), ref(equal_hist_img),
                       ref(enhance_img)); // 创建一个线程，进行图像处理
    thread imshowThread(imsShow, ref(hist_img), ref(gray_img), ref(equal_hist_img),
                        ref(enhance_img)); // 创建一个线程，进行图像显示
    std::cout << "Press any key to exit the program..." << endl;
    // 线程阻塞等待
    improThread.join();
    imshowThread.join();
    return 0;
}
