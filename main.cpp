///Users/jieanyan/Desktop/cpp_test/opencv3_test/opencv3_test.xcodeproj
//  main.cpp
//  opencv3_test
//
//  Created by jiean yan on 14.11.18.
//  Copyright © 2018 jiean yan. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/structured_light.hpp>

using namespace std;
using namespace cv;
void generateGrayarr(int n);
void generateGrayarr_horizontal(int monitor_w,int monitor_h,int n);
void mode_choose(int monitor_w,int monitor_h,int n,bool mode);
/*
 creat a gray pattern
 */

// monitor width and height and period n -->horizontal mode
void generateGrayarr_vertical(int monitor_w,int monitor_h,int n)
{
    // base case
    if (n <= 0)
        return;
    
    // 'arr' will store all generated codes
    vector<string> arr;
    
    // start with one-bit pattern
    arr.push_back("0");
    arr.push_back("1");
    
    //-- Every iteration of this loop generates 2*i codes from previously
    // generated i codes.
    int i, j;
    
    for (i = 2; i < (1<<n); i = i<<1)
    {
        // Enter the prviously generated codes again in arr[] in reverse
        // order. Nor arr[] has double number of codes.
        for (j = i-1 ; j >= 0 ; j--)
            arr.push_back(arr[j]);
        // append 0 to the first half
        for (j = 0 ; j < i ; j++)
            arr[j] = "0" + arr[j];
        
        // append 1 to the second half
        for (j = i ; j < 2*i ; j++)
            arr[j] = "1" + arr[j];
    }
    //--THE CODE ABOVE, CREAT A VECTOR OF GRAY CODE
    
    
    //--THE CODE BELOW, CONVERT GRAY CODE TO PATTERN
    Mat gray_pattern(monitor_w,monitor_h,CV_8UC1);//create a blank pattern
    gray_pattern = 255;//initialize pattern
    int unit_w = monitor_w / n; //width unit
    int n_2 = pow(2,n); //count
    int unit_h = monitor_h/ n_2; // height unit
    
    // convert gray code into  a pattern image
    for (int k = 0 ; k < arr.size() ; k++ )
    {
        string s = arr[k];
        
        for(int p= 0; p < n; p++)
        {
            int tem = s[p];
            if ((tem-48)== 0 )
            {
                gray_pattern(Range(p*unit_w,(p+1)*unit_w),Range(k*unit_h,(k+1)*unit_h))= 0;
            }
            
        }
    }
    
    //show graycode pattern
    imwrite("gray.jpg",gray_pattern);
    namedWindow("gray");
    imshow("gray", gray_pattern);
    waitKey(0);
}



// monitor width and height and period n -->vertical version
void generateGrayarr_horizontal(int monitor_w,int monitor_h,int n)
{
    // base case
    if (n <= 0)
        return;
    
    //--THE CODE BELOW, CREAT A VECTOR OF GRAY CODE---
    // 'arr' will store all generated codes
    vector<string> arr;

    // start with one-bit pattern
    arr.push_back("0");
    arr.push_back("1");
    
    //-- Every iteration of this loop generates 2*i codes from previously
    // generated i codes.
    int i, j;
    
    for (i = 2; i < (1<<n); i = i<<1)
    {
        // Enter the prviously generated codes again in arr[] in reverse
        // order. Nor arr[] has double number of codes.
        for (j = i-1 ; j >= 0 ; j--)
            arr.push_back(arr[j]);
        // append 0 to the first half
        for (j = 0 ; j < i ; j++)
            arr[j] = "0" + arr[j];
        
        // append 1 to the second half
        for (j = i ; j < 2*i ; j++)
            arr[j] = "1" + arr[j];
    }
    //--THE CODE ABOVE, CREAT A VECTOR OF GRAY CODE------
    
    //--THE CODE BELOW, CONVERT GRAY CODE TO PATTERN
    Mat gray_pattern(monitor_w,monitor_h,CV_8UC1);//create a blank pattern
    gray_pattern = 255;//initialize pattern
    int unit_h = monitor_h / n; // height unit
    int n_2 = pow(2,n); //count
    int unit_w = monitor_w / n_2; //width unit
    
    // convert gray code into  a pattern image
    for (int k = 0 ; k < arr.size() ; k++ )
    {
        string s = arr[k];
        
        for(int p= 0; p < n; p++)
        {
            int tem = s[p];
            if ((tem-48)== 0 )
                {
                    gray_pattern(Range(k*unit_w,(k+1)*unit_w),Range(p*unit_h,(p+1)*unit_h))= 0;
                }
        
        }
    }
    
    
    //show graycode pattern
    imwrite("gray.jpg",gray_pattern);
    namedWindow("gray");
    imshow("gray", gray_pattern);
    waitKey(0);
}

//mode 1: vertical pattern
//mode 0: horizontal pattern
void mode_choose(int monitor_w,int monitor_h,int n,bool mode)
{
    if (mode == 1) {
        generateGrayarr_vertical(monitor_w, monitor_h,n);
    } else {
        generateGrayarr_horizontal(monitor_w, monitor_h, n);
    }
}


int main()
{
    int monitor_w=80;
    int monitor_h=160;
    int n=4;
    bool mode=1;
    mode_choose( monitor_w, monitor_h, n,  mode);
    return 0;
}

