// File Name: 数码管识别.cpp
// Author: BigBigYu
// Created Time: Tue 06 Oct 2020 06:59:38 AM PDT

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    Mat g_srcImage;
    if ( argc != 2 ){
        cout << "Please input the path of the picture" << endl;
        return -1;
    }
    g_srcImage = imread( argv[1], 1);

    // 获取图片的高和宽
    //int w = g_srcImage.cols;
    //int h = g_srcImage.rows;
    //resize(g_srcImage, g_srcImage, Size(250, 250*h/w));
    
    namedWindow("嘻嘻嘻", 1);
    imshow("嘻嘻嘻", g_srcImage);

    Mat hsv;
    cvtColor( g_srcImage, g_srcImage, COLOR_BGR2HSV );
    // 转换为hsv空间
    //
    // 设置hsv的上下限
    int iLowH = 59;
    int iHighH = 255;
    int iLowS = 159;
    int iHighS = 255;
    int iLowV = 190;
    int iHighV = 255;

    // 分离通道
    vector<Mat> hsvSplit;
    split(g_srcImage, hsvSplit);

    inRange(g_srcImage, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), hsv);
    namedWindow( "哈哈哈", WINDOW_AUTOSIZE );
    imshow("哈哈哈", hsv);
    waitKey(0);
    return 0;
}
