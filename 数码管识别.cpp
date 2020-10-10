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
    
    namedWindow("不忘初心", 1);
    imshow("不忘初心", g_srcImage);

    Mat hsv;

    int RedL = 230;
    int RedH = 255;
    int GreenL = 0;
    int GreenH = 200;
    int BlueL = 0;
    int BlueH = 200;

    inRange(g_srcImage, Scalar(BlueL, GreenL, RedL), Scalar(BlueH, GreenH, RedH), hsv);
    namedWindow( "二值化", WINDOW_AUTOSIZE );
    imshow("二值化", hsv);

    Mat element=getStructuringElement(MORPH_RECT,Size(5,5));//获取核
    dilate(hsv,hsv,element); //膨胀
    dilate(hsv,hsv,element);
    namedWindow("膨胀一波", WINDOW_AUTOSIZE);
    imshow("膨胀一波",hsv);

    waitKey(0);
    return 0;
}
// sudo  g++ 数码管识别.cpp -o 数码管识别 `pkg-config --cflags --libs opencv`