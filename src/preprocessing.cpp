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
        GaussianBlur(phase_shift[i], dst, Size(3,3),0,0);
        bilateralFilter(phase_shift[i],dst,diameter,20,20);
        dst_phase_shift.push_back(dst);
    }
    return 0;
}


Mat detect_screen(int &amount_pattern, int &amount_shifts,int crop_amount = 1)
{
    vector<Mat> ground_image;
    vector<vector<Point>> contour;

    load_image_ground(ground_image, amount_shifts, amount_pattern); //first white then black

    // detect screen by subtraction black and white images
    Mat subtract = ground_image[0] - ground_image[1];

    blur(subtract,subtract,Size(3,3)); // blur image for better result
    threshold(subtract,subtract,15,255,THRESH_BINARY);

    // find contour
    findContours(subtract,contour,RETR_LIST,CHAIN_APPROX_SIMPLE);
    if (contour.empty())
    {
        cout << "The screen is not fully shown! Please adjust camera distance" << std::endl;
        throw std::exception();
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

int remove_noise(Mat &relative, Mat &frame)
{
    if (relative.empty())
    {
        cout << "Can't load relative phase" << endl;
        return -1;
    }
    vector<vector<Point>> contour;

    Mat dst = Mat::zeros(relative.size(), CV_8U);
    relative.convertTo(dst,CV_8U);

    findContours(dst,contour,RETR_LIST,CHAIN_APPROX_TC89_L1);

    // draw contour of noise
    Mat map(relative.size(), CV_8U, Scalar(255));
    for (int i = 0; i < contour.size(); i++ )
    {
        drawContours(map,contour,i,Scalar(0,0,0),4);
    }

    threshold(map,map,40,1, THRESH_BINARY);
    bitwise_and(frame,map,frame);

    return 0;
}


int sgn(double x)
{
    if (x<0) return -1;
    if (x>0) return 1;
    return 0;
}

/** @brief Calculate correct display pixel from refraction with known transformation from camera to world
 *  @param k2dvector: transform vector from camera to world
 */

int refraction(Point3f &k2dvector, Point3f &display_pixel_mm, Point3f &correct_display_pixel_mm)
{
    double n = 1.5; // refractive index
    double d = 1; //thickness of display

    // calculate the angle between vector<camera to pixel> and display plane as flat with normal vector(0,0,1)
    Point3f k2display = -k2dvector + display_pixel_mm;
    Point3f normal_display(0,0,1); // normal vector of display

    // incident angle
    double alpha1 = abs(acos(abs(k2display.x*normal_display.x + k2display.y*normal_display.y + k2display.z*normal_display.z) / \
                             (sqrt(pow(k2display.x,2)+pow(k2display.y,2)+pow(k2display.z,2))*sqrt(pow(normal_display.x,2)+pow(normal_display.y,2)+pow(normal_display.z,2)))));

    // refractive angle
    double alpha2 = abs(asin(sin(alpha1)/n));

    double h = abs(d*(1-tan(alpha2)/tan(alpha1))); // height offset
    double delta = h*tan(alpha2); //shifted value

    // display pixel angle from Ox
    double beta = abs(acos(display_pixel_mm.x / sqrt(pow(display_pixel_mm.x,2)+pow(display_pixel_mm.y,2) + pow(display_pixel_mm.z,2))));

    // corrected display pixel
    correct_display_pixel_mm = Point3f(display_pixel_mm.x - sgn(display_pixel_mm.x)*delta*cos(beta), \
                                       display_pixel_mm.y - sgn(display_pixel_mm.y)*delta*sin(beta), display_pixel_mm.z);

    return 0;
}


