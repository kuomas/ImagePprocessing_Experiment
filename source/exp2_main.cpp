#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "bilateral_filter.hpp"

using cv::imread;
using cv::waitKey;

int exp2_main(void)
{
    Mat out_img;
    Mat src_img = imread("../../../resource/exp2_example.jpg", 0); // 读取图片并转为单通道，即灰度图
    bilateralFilter(src_img, out_img, 11, 16, 8);    // 双边滤波处理
    imshow("Srouce Image", src_img);                 // 显示原图(灰度图)
    imshow("Bilateral Filter Image", out_img);       // 显示双边滤波后的图
    waitKey(0);
    return 0;
}
