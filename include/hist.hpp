#ifndef HIST_HPP
#define HIST_HPP

#include <opencv2/core/mat.hpp>

using cv::Mat;
using std::vector;

void        calcGrayHist(Mat gray_img, int gray_scale, Mat hist_val);
Mat         plotHist(Mat hist_val, int width, int height);
vector<int> histEqual(Mat hist_val, Mat out_val);
void        enhanceGrayImage(Mat src_img, Mat out_img, vector<int> map);

#endif
