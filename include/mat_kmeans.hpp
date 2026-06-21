#pragma once
#include <opencv2/core/mat.hpp>

using cv::Mat;

void imageKMeans(Mat src_img, Mat& out_img, int k = 2);
