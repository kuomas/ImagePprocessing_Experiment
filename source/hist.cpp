#include "hist.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>

using cv::NORM_MINMAX;
using cv::Point;
using std::cerr;
using std::endl;
using cv::Scalar;

/** 直方图计算 **/
void calcGrayHist(Mat gray_img, int gray_scale, Mat hist_val)
{
    bool overflow = false; // 某个灰度级像素数超过65535的标志

    if(gray_img.channels() != 1) // 是不是灰度图
    {
        cerr << "This image is not a greyscale image!" << endl;
        exit(-1);
    }
    /* 遍历图像元素,统计各灰度级像素个数，当某个灰度的像素数大于65535时将overflow设置为真
       以便后面缩小数据 */
    for(auto it = gray_img.begin<uchar>(); it != gray_img.end<uchar>(); ++it)
        if((++hist_val.at<int>(*it / (256 / gray_scale), 0)) > 65535) overflow = true;
    /* 为了符合某些opencv自带函数的参数类型，缩小整体的值使处于0-65535之间 */
    while(overflow) // 如果某灰度级像素数大于65535
    {
        overflow = false;
        for(int i = 0; i != gray_scale; ++i) // 遍历灰度级
        {
            hist_val.at<int>(i, 0) >>= 1;      // 值缩小为原来的一半
            if(hist_val.at<int>(i, 0) > 65535) // 还大于65535
                overflow = true;               // 设置为真，以便再次缩小像素数
        }
    }
}

/** 绘制直方图 **/
Mat plotHist(Mat hist_val, int width, int height)
{
    int steps    = width / hist_val.rows;              // 计算绘图的步长
    Mat hist_img = Mat::zeros(height, width, CV_8UC1); // 存储直方图的矩阵

    // 将数据缩放到0到直方图的高减10之间，便于绘图和观察，广义上的归一化
    normalize(hist_val, hist_val, 0, height - 10, NORM_MINMAX);
    for(int i = 0; i != hist_val.rows; ++i) // 绘制直方图
    {
        // 在直方图的矩阵中绘制实心矩形
        rectangle(hist_img, Point(i * steps + 1, height - 1),
                  Point((i + 1) * steps - 1, height - hist_val.at<int>(i, 0)), Scalar(255), -1);
    }
    return hist_img; // 返回绘制好的直方图
}

/** 直方图均衡化，得到映射关系 **/
vector<int> histEqual(Mat hist_val, Mat out_val)
{
    vector<float> density;                        // 各灰度级密度
    vector<int>   map;                            // 映射关系
    vector<float> new_density(hist_val.rows, 0);  // 均衡化后灰度级密度
    double        sum_piexs   = sum(hist_val)[0]; // 总像素数
    double        sum_density = 0;                // 各灰度级累积密度

    // 遍历直方图数据
    for(auto it = hist_val.begin<int>(); it != hist_val.end<int>(); ++it)
    {
        density.push_back(*it / sum_piexs);                     // 计算各灰度级密度
        sum_density += (*it / sum_piexs);                       // 计算累计密度
        map.push_back((hist_val.rows - 1) * sum_density + 0.5); // 求映射关系
    }
    for(int i = 0; i != hist_val.rows; ++i)
    {
        new_density[map[i]]   = density[i];                 // 计算均衡化灰度级密度
        out_val.at<int>(i, 0) = new_density[i] * sum_piexs; // 计算均衡化直方图数据
    }
    return map; // 返回映射关系
}

/** 灰度图像增强 **/
void enhanceGrayImage(Mat src_img, Mat out_img, vector<int> map)
{
    // 遍历图像元素
    for(int j = 0; j != src_img.rows; ++j)
        for(int i = 0; i != src_img.cols; ++i)
        {
            uchar gray_value = src_img.at<uchar>(j, i); // 得到图像的灰度值
            out_img.at<uchar>(j, i) =
                256 / map.size() * map[gray_value / (256 / map.size())]; // 根据映射关系计算映射后的灰度值
        }
}
