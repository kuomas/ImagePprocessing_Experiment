#include "texture_feature.hpp"
#include <opencv2/imgproc.hpp>

using cv::Point;
using cv::Scalar;
using cv::Size;

/* 将图像的灰度值调整到一定范围内 */
void grayAdjust(Mat gray_img, Mat& out_img, int target_gray)
{
    out_img = Mat(Size(gray_img.rows, gray_img.cols), CV_8UC1, Scalar(0));
    for(int i = 0; i != gray_img.rows; ++i)
        for(int j = 0; j != gray_img.cols; ++j)
            out_img.at<uchar>(i, j) = gray_img.at<uchar>(i, j) / (256 / target_gray);
}

/* 计算灰度共生矩阵 */
Mat getGlcm(Mat gray_img, bool flag, int gray_level, int dx, int dy)
{
    grayAdjust(gray_img, gray_img, gray_level); // 将图像的灰度值调整到相应的灰度级
    Mat glcm(gray_level, gray_level, CV_8UC1, Scalar(0));
    for(int i = 0; i != gray_img.rows; ++i)
        for(int j = 0; j != gray_img.cols; ++j)
        {
            int x = gray_img.at<uchar>(i, j); // 灰度共生矩阵的x坐标
            if((i + dx < gray_img.rows) && (j + dy < gray_img.cols))
            {
                int y = gray_img.at<uchar>(i + dx, j + dy); // 灰度共生矩阵的y坐标
                // 将矩阵的位于(x,y)的元素值自增1
                glcm.at<uchar>(x, y) += 1;
            }
            // flag决定方向是否双向
            if(flag && (i - dx > 0) && (j - dy > 0))
            {
                int _y = gray_img.at<uchar>(i - dx, j - dy); // 灰度共生矩阵的y坐标
                // 将矩阵的位于(x,y)的元素值自增1
                glcm.at<uchar>(x, _y) += 1;
            }
        }
    return glcm; // 返回矩阵
}

// 计算均值
int mean(Mat glcm)
{
    int mean_val = 0;
    for(int i = 0; i != glcm.rows; ++i)
        for(int j = 0; j != glcm.cols; ++j)
            mean_val += (glcm.at<uchar>(i, j) * i);
    return mean_val;
}

// 计算方差
int variance(Mat glcm)
{
    int var_val  = 0;
    int mean_val = mean(glcm);
    for(int i = 0; i != glcm.rows; ++i)
        for(int j = 0; j != glcm.cols; ++j)
            var_val += (glcm.at<uchar>(i, j) * (i - mean_val));
    return var_val;
}

// 计算对比度特征
int conFeature(Mat glcm)
{
    int con_val = 0;
    for(int i = 0; i != glcm.rows; ++i)
        for(int j = 0; j != glcm.cols; ++j)
            con_val += ((i - j) * (i - j) * glcm.at<uchar>(i, j));
    return con_val;
}

// 计算能量特侦
int asmFeature(Mat glcm)
{
    int asm_val = 0;
    for(int i = 0; i != glcm.rows; ++i)
        for(int j = 0; j != glcm.cols; ++j)
            asm_val += (glcm.at<uchar>(i, j) * glcm.at<uchar>(i, j));
    return asm_val;
}

// 计算熵特征
int entFeature(Mat glcm)
{
    int ent_val = 0;
    for(int i = 0; i != glcm.rows; ++i)
        for(int j = 0; j != glcm.cols; ++j)
        {
            int temp = glcm.at<uchar>(i, j);
            if(temp != 0) ent_val += (temp * log(temp));
        }
    return -ent_val;
}

// 计算相关性特征
int corrFeature(Mat glcm)
{
    double corr_val = 0;
    double mean_val = mean(glcm);
    double var_val  = variance(glcm);
    for(int i = 0; i != glcm.rows; ++i)
        for(int j = 0; j != glcm.cols; ++j)
            corr_val += ((i - mean_val) * (j - mean_val) * glcm.at<uchar>(i, j) * glcm.at<uchar>(i, j)) / var_val;
    return corr_val;
}

// 将值调整到一定范围内，方便绘图
void pointAdjust(double& ft1, double& ft2, int max)
{
    while(abs(ft1) >= max || abs(ft2) >= max)
    {
        ft1 /= 2;
        ft2 /= 2;
    }
}

// 绘制特征相对位置
void plotFeaturePosition(int width, int height, Mat& out_img, double rfx, double sfx, double rfy, double sfy)
{
    /* 将值调整到坐标系能显示的范围内 */
    pointAdjust(rfx, sfx, height / 2);
    pointAdjust(rfy, sfy, width / 2);
    /* 绘制smooth图像的特征 */
    rectangle(out_img, Point(height / 2 + sfx, width / 2 - sfy), Point(height / 2 + sfx, width / 2 - sfy),
              Scalar(0, 255, 0));
    /* 绘制rough图像的特征 */
    rectangle(out_img, Point(height / 2 + rfx, width / 2 - rfy), Point(height / 2 + rfx, width / 2 - rfy),
              Scalar(255, 0, 0));
}
