/**
 * @file measure.cpp
 * @author ogres.roar (ogres.roar@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 * @details
 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<float> measure1(VideoCapture video)
{
    vector<float> result;
    Mat frame;
    Scalar m;
    while (true)
    {
        video >> frame;
        if (frame.empty())
        {
            break;
        }
        m = mean(frame);
        result.push_back(m.val[0]);
    }
    return result;
}

vector<float> measure2(VideoCapture video)
{
    vector<float> result;
    Mat frame;
    Scalar m;
    while (true)
    {
        video >> frame;
        if (frame.empty())
        {
            break;
        }
        m = mean(frame);
        result.push_back((m.val[0] + m.val[1] + m.val[2]) * 1.0 / 3);
    }
    return result;
}

vector<float> measure3(VideoCapture video)
{
    vector<float> result;
    Mat frame;
    Scalar m, v;
    while (true)
    {
        video >> frame;
        if (frame.empty())
        {
            break;
        }
        meanStdDev(frame, m, v);
        result.push_back(v.val[0]);
    }
    return result;
}

float distance(vector<float> a, vector<float> b)
{
    float result = 0;
    for (int i = 0; i < a.size(); i++)
    {
        result += abs(a[i] - b[i]);
    }
    return sqrt(result);
}

int main()
{
    VideoCapture video;
    video.open("data/knight.mp4");

    // 视频是否打开
    if (!video.isOpened())
    {
        cout << "cant read data/knight.mp4" << endl;
        return -1;
    }

    vector<float> m1 = measure1(video);
    vector<float> nm1;
    float m1mean = 0, m1std = 0;

    for (auto v : m1)
    {
        m1mean += v;
        m1std += v * v;
    }
    m1mean /= m1.size();
    m1std = sqrt(m1std / m1.size() - m1mean * m1mean);

    for (auto v : m1)
    {
        nm1.push_back((v - m1mean) / m1std);
    }

    video.release();
    video.open("data/knight.mp4");

    // 视频是否打开
    if (!video.isOpened())
    {
        cout << "cant read data/knight.mp4" << endl;
        return -1;
    }
    vector<float> m2 = measure2(video);
    float m2mean = 0, m2std = 0;
    vector<float> nm2;

    for (auto v : m2)
    {
        m2mean += v;
        m2std += v * v;
    }
    m2mean = m2mean / m2.size();
    m2std = sqrt(m2std / m2.size() - m2mean * m2mean);

    for (auto v : m2)
    {
        nm2.push_back((v - m2mean) / m2std);
    }

    video.release();
    video.open("data/knight.mp4");

    // 视频是否打开
    if (!video.isOpened())
    {
        cout << "cant read data/knight.mp4" << endl;
        return -1;
    }
    vector<float> m3 = measure3(video), nm3;
    float m3mean = 0, m3std = 0;

    for (auto v : m3)
    {
        m3mean += v;
        m3std += v * v;
    }
    m3mean = m3mean / m3.size();
    m3std = sqrt(m3std / m3.size() - m3mean * m3mean);

    for (auto v : m3)
    {
        nm3.push_back((v - m3mean) / m3std);
    }

    cout << "nm1~nm2: " << distance(nm1, nm2) << endl;
    cout << "nm1~nm3: " << distance(nm1, nm3) << endl;
    cout << "nm2~nm3: " << distance(nm2, nm3) << endl;

    return 0;
}
