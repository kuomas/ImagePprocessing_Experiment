#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "mat_kmeans.hpp"

using cv::imread;
using cv::resize;
using cv::Size;
using cv::waitKey;

int exp6_main()
{
    Mat src_img1 = imread("../../../resource/exp6_2.jpg");
    Mat src_img2 = imread("../../../resource/exp6_1.jpg");
    Mat out_img1, out_img2;

    resize(src_img1, src_img1, Size(400, 300));
    resize(src_img2, src_img2, Size(400, 300));
    imageKMeans(src_img1, out_img1, 2);
    imageKMeans(src_img2, out_img2, 2);

    imshow("source image 1", src_img1);
    imshow("result image 1", out_img1);
    imshow("source image 2", src_img2);
    imshow("result image 2", out_img2);

    waitKey(0);
    return 0;
}
