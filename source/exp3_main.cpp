#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <random>

#include "texture_feature.hpp"

using cv::imread;
using cv::Point;
using cv::Rect;
using cv::Scalar;
using cv::Size;
using cv::waitKey;
using std::default_random_engine;
using std::uniform_int_distribution;

int exp3_main(void)
{
    int                                size = 10;
    default_random_engine              engine(time(0));
    uniform_int_distribution<unsigned> random_xy(0, 511 - size);
    /* 读入两幅纹理存在明显差异的图像 */
    Mat smooth_img = imread("../../../resource/exp3_Texture2.jpeg", 0);
    Mat rough_img  = imread("../../../resource/exp3_Texture1.jpeg", 0);
    resize(smooth_img, smooth_img, Size(512, 512));
    resize(rough_img, rough_img, Size(512, 512));
    int width = 400, height = 400;
    Mat FeaturePositionAE(width, height, CV_8UC3, Scalar(0, 0, 0));
    Mat FeaturePositionCC(width, height, CV_8UC3, Scalar(0, 0, 0));
    /* 画x，y轴 */
    line(FeaturePositionAE, Point(0, height / 2), Point(width - 1, height / 2), Scalar(255, 255, 255));
    line(FeaturePositionAE, Point(width / 2, 0), Point(width / 2, height - 1), Scalar(255, 255, 255));
    line(FeaturePositionCC, Point(0, height / 2), Point(width - 1, height / 2), Scalar(255, 255, 255));
    line(FeaturePositionCC, Point(width / 2, 0), Point(width / 2, height - 1), Scalar(255, 255, 255));
    for(size_t i = 0; i != 5000; ++i)
    {
        /* 在每张大图中任意选取一个10*10小图像 */
        Mat smooth_img10x = smooth_img(Rect(random_xy(engine), random_xy(engine), size, size));
        Mat rough_img10x  = rough_img(Rect(random_xy(engine), random_xy(engine), size, size));
        /* 计算每张图像的灰度共生矩阵 */
        Mat rough_glcm  = getGlcm(rough_img10x, true);
        Mat smooth_glcm = getGlcm(smooth_img10x, true);
        /* 计算能量特征 */
        double rough_asm  = asmFeature(rough_glcm);
        double smooth_asm = asmFeature(smooth_glcm);
        /* 计算熵特征 */
        double rough_ent  = entFeature(rough_glcm);
        double smooth_ent = entFeature(smooth_glcm);
        /* 以横轴为能量特征，纵轴为熵特征，在坐标系中汇出特征值的位置 */
        plotFeaturePosition(width, height, FeaturePositionAE, rough_asm, smooth_asm, rough_ent, smooth_ent);
        /* 计算对比度特征 */
        double rough_con  = conFeature(rough_glcm);
        double smooth_con = conFeature(smooth_glcm);
        /* 计算相关性特征 */
        double rough_corr  = corrFeature(rough_glcm);
        double smooth_corr = corrFeature(smooth_glcm);
        /* 以横轴为相关性特征，纵轴为对比度特征，在坐标系中汇出特征值的位置 */
        plotFeaturePosition(width, height, FeaturePositionCC, rough_corr, smooth_corr, rough_con, smooth_con);
    }
    /* 缩放到容易查看的范围内 */
    resize(FeaturePositionAE, FeaturePositionAE, Size(512, 512), 0, 0, 0);
    resize(FeaturePositionCC, FeaturePositionCC, Size(512, 512), 0, 0, 0);
    /* 显示(绿色为smooth，蓝色为rough) */
    imshow("Asm-Ent", FeaturePositionAE);
    /* 显示(绿色为smooth，蓝色为rough) */
    imshow("Corr-Con", FeaturePositionCC);
    waitKey(0);
    return 0;
}
