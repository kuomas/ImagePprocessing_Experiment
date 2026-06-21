#ifndef TEXT_FAETURE_HPP
#define TEXT_FAETURE_HPP

#include <opencv2/core/mat.hpp>

using cv::Mat;

Mat  getGlcm(Mat gray_img, bool flag = false, int gray_level = 8, int dx = 0, int dy = 1);
int  conFeature(Mat glcm);
int  asmFeature(Mat glcm);
int  entFeature(Mat glcm);
int  corrFeature(Mat glcm);
void plotFeaturePosition(int width, int height, Mat& out_img, double rfx, double sfx, double rfy, double sfy);

#endif
