#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "tools.h"
#include <iostream>

using namespace  cv;
using namespace std;


int convert_binary(vector<Mat> &graycode_images){

    //Seting contanst threshold --> Need to be modular someday...

    for (int image_i = 0; image_i < graycode_images.size(); image_i++)
    {
        threshold(graycode_images[image_i], graycode_images[image_i], 40, 1, THRESH_BINARY);
    }

}


int reduce_moire(vector<Mat> &phase_shift, vector<Mat> &dst_phase_shift,int diameter=10)
{
    if (( diameter <= 0) || (diameter <10))
    {
        cout << "Invalid value of diameter. Suggested: 10->80" << endl;
        return -1;
    }

    if (!dst_phase_shift.empty())
    {
        cout << "Destination vector must be empty" << endl;
        return -1;
    }

    for (int i = 0; i < phase_shift.size(); i++)
    {
        Mat dst = phase_shift[i].clone();
        bilateralFilter(phase_shift[i],dst,diameter,50,50);
        dst_phase_shift.push_back(dst);
    }
    return 0;
}


Mat detect_screen(int &period, int &amount_shifts,int crop_amount = 1)
{
    vector<Mat> ground_image;
    vector<vector<Point>> contour;

    load_image_ground(ground_image, amount_shifts, period); //first white then black

    // detect screen by subtraction black and white images
    Mat subtract = ground_image[0] - ground_image[1];
    blur(subtract,subtract,Size(3,3)); // blur image for better result
    threshold(subtract,subtract,20,255,THRESH_BINARY);

    // find contour
    findContours(subtract,contour,RETR_LIST,CHAIN_APPROX_SIMPLE);
    if (contour.empty())
    {
        cout << "The screen is not fully shown! Please adjust camera distance" << std::endl;
    }

    // find the largest contour (screen)
    int max_area, index = 0;
    for (int i=0; i<contour.size();i++)
    {
        double area = contourArea(contour[i],false);
        if (area > max_area)
        {
            max_area = area;
            index = i;
        }
    }

    // draw contour
    Mat frame = Mat::zeros(subtract.size(),CV_8U);
    drawContours(frame,contour,index,Scalar(255,255,255),CV_FILLED);

    // crop contour
    drawContours(frame,contour,index,Scalar(0,0,0),crop_amount);

    // convert binary
    threshold(frame,frame,40,1, THRESH_BINARY);

    return frame;
}





















