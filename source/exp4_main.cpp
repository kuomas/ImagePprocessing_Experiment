#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using cv::COLOR_BGR2HSV;
using cv::COLOR_HSV2RGB;
using cv::imread;
using cv::Mat;
using cv::namedWindow;
using cv::setTrackbarPos;
using cv::Vec3b;
using cv::waitKey;

/* 调节图像的鲜艳程度 */
void adjustVividness(Mat src_img, Mat& out_img, int vividness)
{
    Mat hsv_img;
    cvtColor(src_img, hsv_img, COLOR_BGR2HSV); // 将图像转换为HSV格式
    for(int i = 0; i != hsv_img.rows; ++i)
        for(int j = 0; j != hsv_img.cols; ++j)
        {
            // 取出HSV格式图像的S的值
            double s = hsv_img.at<Vec3b>(i, j)[1];
            // 为了避免鲜艳度变化太大，将系数缩小10倍在乘以S的值
            s = s * vividness / 10.0;
            // 因为S的范围为[0,255]为了避免超出，限制一下在赋给图像中的S
            hsv_img.at<Vec3b>(i, j)[1] = s > 255 ? 255 : s;
        }
    cvtColor(hsv_img, out_img, COLOR_HSV2RGB); // 将调节好的图像转回BGR
}

// 用于调节图像鲜艳度并实时显示的回调函数
void trackbarCallback(int vividness, void* src)
{
    Mat out_img;
    adjustVividness(*static_cast<Mat*>(src), out_img, vividness); // 调节图像的鲜艳程度
    imshow("Enhanced Image", out_img);                            // 显示
}

int exp4_main()
{
    Mat src_img = imread("../../../resource/exp4_example.jpg"); // 读取一张彩色图像
    Mat out_img;
    int vividness = 10;
    namedWindow("Enhanced Image");
    // 此次调用adjustVividness函数是为了在调节跟踪条之前也显示调节后的图像
    adjustVividness(src_img, out_img, vividness);
    imshow("Source Image", src_img);   // 显示原来的图像
    imshow("Enhanced Image", out_img); // 显示调节后的图像
    createTrackbar("Vividness", "Enhanced Image", nullptr, 100, trackbarCallback,
                   &src_img); // 创建跟踪条，用于调节鲜艳度(右移增强，左移减弱)
    setTrackbarPos("Vividness", "Enhanced Image", vividness);
    waitKey(0);
    return 0;
}
