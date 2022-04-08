/**
 * @file mouse.cpp
 * @author ogres.roar (ogres.roar@gmail.com)
 * @brief Concise Computer Vision: An Introductioninto Theory and Algorithms  Exercise 1.1 4
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 * @details 根据鼠标指针位置, 展示11x11的窗口以及方差均值等信息
 *
 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void onMouse(int event, int x, int y, int flags, void *param)
{
    cout << "event: " << event << " flags: " << flags
         << " x: " << x << " y: " << y << endl;

    // (*(Mat *)param).at<Vec3b>(y, x) = Vec3b(255, 255, 255);

    Mat img;
    (*(Mat *)param).copyTo(img);

    Rect rect = Rect(max(x - 6, 0), max(y - 6, 0), min(13, img.cols - x), min(13, img.rows - y));
    Mat dst = img(rect);

    // 求dst的均值
    Scalar mean, stddev;

    meanStdDev(dst, mean, stddev);

    if (x - 6 >= 0)
    {
        for (int i = max(0, y - 6); i <= min(img.rows - 1, y + 6); i++)
        {
            img.at<Vec3b>(i, x - 6) = Vec3b(255, 255, 255);
        }
    }

    if (x + 6 < img.cols)
    {
        for (int i = max(0, y - 6); i <= min(img.rows - 1, y + 6); i++)
        {
            img.at<Vec3b>(i, x + 6) = Vec3b(255, 255, 255);
        }
    }

    if (y - 6 >= 0)
    {
        for (int i = max(0, x - 6); i <= min(img.cols - 1, x + 6); i++)
        {
            img.at<Vec3b>(y - 6, i) = Vec3b(255, 255, 255);
        }
    }

    if (y + 6 < img.rows)
    {
        for (int i = max(0, x - 6); i <= min(img.cols - 1, x + 6); i++)
        {
            img.at<Vec3b>(y + 6, i) = Vec3b(255, 255, 255);
        }
    }

    Vec3b p = img.at<Vec3b>(y, x);
    putText(img, "(" + to_string(p.val[0]) + ", " + to_string(p.val[1]) + ", " + to_string(p.val[2]) + ")", Point(x, y - 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
    putText(img, to_string((p.val[0] + p.val[1] + p.val[2]) / 3), Point(x, y + 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
    putText(img, "mean: " + to_string(mean.val[0]) + ", " + to_string(mean.val[1]) + ", " + to_string(mean.val[2]), Point(x, y + 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
    putText(img, "stddev: " + to_string(stddev.val[0]) + ", " + to_string(stddev.val[1]) + ", " + to_string(stddev.val[2]), Point(x, y + 60), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
    imshow("Original", img);
}

int main()
{
    Mat img = imread("data/10.png", IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    imshow("Original", img);
    setMouseCallback("Original", onMouse, &img);
    waitKey(0);

    return 0;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}