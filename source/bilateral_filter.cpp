#include "bilateral_filter.hpp"

using cv::Rect;
using cv::Scalar;
using std::vector;

/* 生成空间距离权重模板 */
vector<vector<double>> generateDistanceMask(int size, double sigma_s)
{
    // 定义一个大小为(size*size)的vector用来存放模板
    vector<vector<double>> mask(size, vector<double>(size, 0));
    int                    k = (size - 1) / 2; // 模板中心位置
    for(int i = 0; i != size; ++i)
        for(int j = 0; j != size; ++j)
        {
            // 求空间距离权重的指数部分
            double index_s = (pow(i - k - 1, 2) + pow(j - k - 1, 2)) / (2 * pow(sigma_s, 2));
            mask[i][j]     = exp(-index_s); // 求得空间距离权重
        }
    return mask; // 返回求得的空间距离权重模板
}

/* 双边滤波 */
void bilateralFilter(Mat& src_img, Mat& out_img, int mask_size, double sigma_s, double sigma_r)
{
    int k = (mask_size - 1) / 2; // 滤波模板的中心位置
    // 得到空间距离权重模板
    vector<vector<double>> mask_s = generateDistanceMask(mask_size, sigma_s);
    // 将输出的图片初始化为原图大小
    out_img = Mat(src_img.rows, src_img.cols, CV_8UC1, Scalar(0));
    /* 以下两句将源图向外扩充大小为k，颜色为灰度值128，便于对原图边缘处滤波*/
    Mat pro_img(src_img.rows + 2 * k, src_img.cols + 2 * k, CV_8UC1, Scalar(128));
    src_img.copyTo(pro_img(Rect(k, k, src_img.cols, src_img.rows)));
    for(int j = k; j != pro_img.rows - k; ++j)
        for(int i = k; i != pro_img.cols - k; ++i)
        {
            double gray_sum = 0, weight_sum = 0;
            // 定义一个大小为(size*size)的vector用来存放滤波模板
            vector<vector<double>> mask(mask_size, vector<double>(mask_size, 0));
            // 截取被滤波图片的部分
            Mat temp_img = pro_img(Rect(i - k, j - k, mask_size, mask_size));
            /* 求滤波模板及权重和 */
            for(int m = 0; m != mask_size; ++m)
                for(int n = 0; n != mask_size; ++n)
                {
                    // 求像素值权重的指数部分
                    double index_r =
                        pow((temp_img.at<uchar>(m, n) - temp_img.at<uchar>(k, k)), 2) / (2 * pow(sigma_r, 2));
                    mask[m][n] = mask_s[m][n] * exp(-index_r); // 求得滤波权重
                    weight_sum += mask[m][n];                  // 滤波权重每个值累加
                }
            // 模板权重归一化及求某点的滤波后的灰度值
            for(int m = 0; m != mask_size; ++m)
                for(int n = 0; n != mask_size; ++n)
                {
                    mask[m][n] /= weight_sum;
                    gray_sum += (mask[m][n] * double(temp_img.at<uchar>(m, n)));
                }
            // 将求得的灰度值写入图片矩阵中
            out_img.at<uchar>(j - k, i - k) = uchar(gray_sum);
        }
}
