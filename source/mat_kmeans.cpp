#include "mat_kmeans.hpp"
#include <iostream>
#include <random>

using cv::Vec3b;
using std::cerr;
using std::default_random_engine;
using std::endl;
using std::uniform_real_distribution;
using std::vector;

void MattoKmeans(Mat in, vector<vector<double>>& out)
{
    for(int i = 0; i != in.rows; ++i)
        for(int j = 0; j != in.cols; ++j)
        {
            switch(in.channels())
            {
                case 1 :
                {
                    vector<double> v1;
                    v1.push_back(i * in.cols + j);
                    v1.push_back(in.at<uchar>(i, j));
                    out.push_back(v1);
                    break;
                }
                case 3 :
                {
                    vector<double> v3;
                    v3.push_back(i * in.cols + j);
                    v3.push_back(in.at<Vec3b>(i, j)[0]);
                    v3.push_back(in.at<Vec3b>(i, j)[1]);
                    v3.push_back(in.at<Vec3b>(i, j)[2]);
                    out.push_back(v3);
                    break;
                }
                default : cerr << "no define!!!" << endl; break;
            }
        }
}

void k_means(vector<vector<double>> in, vector<vector<double>>& out, vector<vector<double>> center)
{
    double                         pre_cha = 0, sum_var = 1;
    vector<vector<vector<double>>> k_data(center.size());
    out = vector<vector<double>>(center.size());
    while(abs(sum_var - pre_cha) > 0.1)
    {
        k_data  = vector<vector<vector<double>>>(center.size());
        pre_cha = sum_var;
        sum_var = 0;
        for(size_t i = 0; i != in.size(); ++i)
        {
            double min_dist  = DBL_MAX;
            size_t min_index = 0, j = 0;
            for(size_t m = 0; m != center.size(); ++m)
            {
                double dist = 0;
                for(j = 1; j != in[i].size(); ++j)
                    dist += pow(in[i][j] - center[m][j - 1], 2);
                if(dist < min_dist)
                {
                    min_dist  = dist;
                    min_index = m;
                }
            }
            k_data[min_index].push_back(in[i]);
            sum_var += min_dist;
        }
        vector<vector<double>> temp_center(center.size(), vector<double>(center[0].size()));
        for(size_t i = 0; i != k_data.size(); ++i)
        {
            for(size_t j = 0; j != k_data[i].size(); ++j)
            {
                for(size_t k = 1; k != k_data[i][j].size(); ++k)
                    temp_center[i][k - 1] += k_data[i][j][k] / k_data[i].size();
            }
        }
        center = temp_center;
    }
    size_t i = 0;
    for(auto data : k_data)
    {
        for(auto elem : data)
            out[i].push_back(elem[0]);
        ++i;
    }
}

void KmeanstoMat(vector<vector<double>> in, Mat& out)
{
    uchar color = 255 / (in.size() - 1);
    for(uint8_t i = 0; i != in.size(); ++i)
        for(size_t j = 0; j != in[i].size(); ++j)
        {
            int row                 = int(in[i][j]) / out.cols;
            int col                 = int(in[i][j]) % out.cols;
            out.at<uchar>(row, col) = i * color;
        }
}

void imageKMeans(Mat src_img, Mat& out_img, int k)
{
    default_random_engine             engine(time(0));
    uniform_real_distribution<double> random(0, 255);
    vector<vector<double>>            in;
    vector<vector<double>>            out;
    vector<vector<double>>            center;
    out_img = Mat(src_img.rows, src_img.cols, CV_8UC1);
    for(int i = 0; i != k; ++i)
    {
        vector<double> vec3;
        for(int j = 0; j != src_img.channels(); ++j)
            vec3.push_back(random(engine));
        center.push_back(vec3);
    }
    MattoKmeans(src_img, in);
    k_means(in, out, center);
    KmeanstoMat(out, out_img);
}
