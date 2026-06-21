#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using cv::BORDER_DEFAULT;
using cv::imread;
using cv::Mat;
using cv::NORM_MINMAX;
using cv::Point;
using cv::Rect;
using cv::Scalar;
using cv::Size;
using cv::waitKey;

int exp5_main(void)
{
    Mat src_img  = imread("../../../resource/exp5_example.png", 0);
    Mat temp_img = imread("../../../resource/exp5_template.png", 0);
    Mat result_img(src_img.rows, src_img.cols, CV_64FC1);
    Mat temp_result(src_img.rows, src_img.cols, CV_8UC1);
    Mat process_img;
    copyMakeBorder(src_img, process_img, 0, temp_img.rows, 0, temp_img.cols, BORDER_DEFAULT);
    for(int i = 0; i != process_img.rows - temp_img.rows; ++i)
        for(int j = 0; j != process_img.cols - temp_img.cols; ++j)
        {
            Mat    _img = process_img(Rect(j, i, temp_img.cols, temp_img.rows));
            double sum  = 0;
            for(int m = 0; m != temp_img.rows; ++m)
                for(int n = 0; n != temp_img.cols; ++n)
                {
                    sum += pow((_img.at<uchar>(m, n) - temp_img.at<uchar>(m, n)), 2);
                }
            result_img.at<double>(i, j) = sum;
        }
    normalize(result_img, result_img, 0, 255, NORM_MINMAX);
    result_img.convertTo(temp_result, CV_8UC1);
    Point minIndex;
    minMaxLoc(temp_result, nullptr, nullptr, &minIndex);
    imshow("source image", src_img);
    rectangle(src_img, Rect(minIndex.x, minIndex.y, temp_img.cols, temp_img.rows), Scalar(255), 2);
    resize(temp_img, temp_img, Size(400, 400));
    imshow("template image", temp_img);
    imshow("result", src_img);
    waitKey(0);
    return 0;
}
