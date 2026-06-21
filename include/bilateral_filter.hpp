#ifndef BILATERAL_FILTER_HPP
#define BILATERAL_FILTER_HPP

#include <opencv2/core/mat.hpp>

using cv::Mat;

void bilateralFilter(Mat &src_img, Mat &out_img, int mask_size, double sigma_s, double sigma_r);

#endif