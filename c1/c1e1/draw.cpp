/**
 * @file draw.cpp
 * @author ogres.roar (ogres.roar@gmail.com)
 * @brief Concise Computer Vision: An Introductioninto Theory and Algorithms  Exercise 1.1 1-3
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 * @details 读取data/10.png 分通道绘制柱状图 并做数据拼接
 *
 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char **)
{
    Mat img = imread("data/10.png", IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    vector<Mat> channels;
    Mat red, green, blue, r_hist, g_hist, b_hist, r_histimage, g_histimage, b_histimage;

    int hist_w = 800;
    int hist_h = 800;
    float range[] = {0, 256};
    const float *histRange = {range};
    int hist_bin_size = 32;

    // 把img分成三个通道
    split(img, channels);

    // red channel histogram
    red = channels[2];

    calcHist(&red, 1, 0, Mat(), r_hist, 1, &hist_bin_size, &histRange, true, false);
    normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
    // 创建一个空的灰度图，用来绘制直方图
    r_histimage = Mat::zeros(hist_h, hist_w, CV_8UC1);
    // 绘制直方图
    for (int i = 1; i < hist_bin_size; i++)
    {
        line(r_histimage, Point(i * hist_w / hist_bin_size, hist_h), Point(i * hist_w / hist_bin_size, hist_h - cvRound(r_hist.at<float>(i - 1))), Scalar(255), 2, 8, 0);
    }

    // green channel histogram
    green = channels[1];
    calcHist(&green, 1, 0, Mat(), g_hist, 1, &hist_bin_size, &histRange, true, false);
    normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
    g_histimage = Mat::zeros(hist_h, hist_w, CV_8UC1);
    for (int i = 1; i < hist_bin_size; i++)
    {
        line(g_histimage, Point(i * hist_w / hist_bin_size, hist_h), Point(i * hist_w / hist_bin_size, hist_h - cvRound(g_hist.at<float>(i - 1))), Scalar(255), 2, 8, 0);
    }

    // blue channel histogram
    blue = channels[0];
    calcHist(&blue, 1, 0, Mat(), b_hist, 1, &hist_bin_size, &histRange, true, false);
    normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
    b_histimage = Mat::zeros(hist_h, hist_w, CV_8UC1);
    for (int i = 1; i < hist_bin_size; i++)
    {
        line(b_histimage, Point(i * hist_w / hist_bin_size, hist_h), Point(i * hist_w / hist_bin_size, hist_h - cvRound(b_hist.at<float>(i - 1))), Scalar(255), 2, 8, 0);
    }

    Mat output = Mat::zeros(hist_h * 2, hist_w * 4, CV_8UC3);
    Mat tmp = Mat::zeros(hist_h, hist_w, CV_8UC1);
    Rect rect = Rect(0, 0, hist_w, hist_h);
    vector<Mat> nchannels;

    Mat dst = output(rect);
    img.copyTo(dst);

    dst = output(Rect(0, hist_h, hist_w, hist_h));
    nchannels.clear();
    nchannels.push_back(b_histimage);
    nchannels.push_back(g_histimage);
    nchannels.push_back(r_histimage);
    merge(nchannels, dst);

    rect = Rect(hist_w, 0, hist_w, hist_h);
    dst = output(rect);

    nchannels.clear();
    nchannels.push_back(tmp);
    nchannels.push_back(tmp);
    nchannels.push_back(red);
    merge(nchannels, dst);

    rect = Rect(hist_w, hist_h, hist_w, hist_h);
    dst = output(rect);
    nchannels.clear();
    nchannels.push_back(tmp);
    nchannels.push_back(tmp);
    nchannels.push_back(r_histimage);
    merge(nchannels, dst);

    rect = Rect(hist_w * 2, 0, hist_w, hist_h);
    dst = output(rect);
    nchannels.clear();
    nchannels.push_back(tmp);
    nchannels.push_back(green);
    nchannels.push_back(tmp);
    merge(nchannels, dst);

    rect = Rect(hist_w * 2, hist_h, hist_w, hist_h);
    dst = output(rect);
    nchannels.clear();
    nchannels.push_back(tmp);
    nchannels.push_back(g_histimage);
    nchannels.push_back(tmp);
    merge(nchannels, dst);

    rect = Rect(hist_w * 3, 0, hist_w, hist_h);
    dst = output(rect);
    nchannels.clear();
    nchannels.push_back(blue);
    nchannels.push_back(tmp);
    nchannels.push_back(tmp);
    merge(nchannels, dst);

    rect = Rect(hist_w * 3, hist_h, hist_w, hist_h);
    dst = output(rect);
    nchannels.clear();
    nchannels.push_back(b_histimage);
    nchannels.push_back(tmp);
    nchannels.push_back(tmp);
    merge(nchannels, dst);

    imshow("histogram", output);
    waitKey(0);
    imwrite("data/histogram.jpg", output);
}
