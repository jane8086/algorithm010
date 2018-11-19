#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/structured_light.hpp>

using namespace std;
using namespace cv;
void generateGrayarr_horizontal(int monitor_w,int monitor_h,int n);
void generateGrayarr_vertical(int monitor_w,int monitor_h,int n);
void creat_grayCode_patterns(int monitor_w,int monitor_h,int n,bool mode);


/*
 function creat_grayCode_patterns
 input: monitor_w: resolution U
        monitor_h: resolution V
        n: sum of the periods
        image_mode: 1 for creating horizontal images,
                    0 for creating vertical images.
 output: n gray_code images with different period
 */


// monitor width and height and period n -->vertical mode
void generateGrayarr_vertical(int monitor_w,int monitor_h,int n)
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
    //--THE CODE ABOVE, CREAT A VECTOR OF GRAY CODE
    
    //--THE CODE BELOW, CONVERT GRAY CODE TO PATTERNS
    vector<Mat> gray_patterns;
    Mat gray_pattern(monitor_w,monitor_h,CV_8UC1);//create a blank pattern
    
    // convert gray code into several patterns which stored in a vector
    for (int p = 1 ; p <= n ; p++)         //gray_code_pattern with n period
    {
        int arrsiz;
        arrsiz = pow(2,p);
        gray_pattern =255;                //initialize Mat before use it
        for(int x = 1 ; x <= arrsiz ; x++)//
        {
            
            int unit_h ;
            unit_h = monitor_h / arrsiz ;
            string s;
            s = arr[x-1];
            int tem;
            tem = s[n-1];
            if ((tem-48)==0)
            {
                gray_pattern(Range(0, monitor_w),Range((x-1)*unit_h, x*unit_h))=0;//fill black in pattern
            }
        }
        gray_patterns.push_back(gray_pattern.clone());
    }
    
    
    //show graycode pattern
    for(int x = 0; x<n ; x++)
    {
        string picture = "vertical_gray_code_pattern_with" + to_string(x) + " period.jpg";
        string windowname = "vertical_gray"+to_string(x);
        imwrite(picture,gray_patterns[x]);
        namedWindow(windowname);
        imshow(windowname , gray_patterns[x]);
    }
    waitKey(0);
    
}

// monitor width and height and period n -->horizontal version
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
    
    
    //--THE CODE BELOW, CONVERT GRAY CODE TO PATTERNS
    vector<Mat> gray_patterns;                   //creat a vector to save gray_patterns
    
    Mat gray_pattern(monitor_w,monitor_h,CV_8UC1);//create a blank pattern
    
    // convert gray code into several patterns which stored in a vector
    for (int p = 1 ; p <= n ; p++)         //gray_code_pattern with n period
    {
        int arrsiz;
        arrsiz = pow(2,p);
        gray_pattern =255;                //initialize Mat before use it
        for(int x = 1 ; x <= arrsiz ; x++)
        {
            
            int unit_w ;
            unit_w = monitor_w / arrsiz ;
            string s;
            s = arr[x-1];
            int tem;
            tem = s[n-1];
            if ((tem-48)==0)
            {
                gray_pattern(Range((x-1)*unit_w, x*unit_w),Range(0,monitor_h))=0;//fill black in pattern
            }
         }
        gray_patterns.push_back(gray_pattern.clone());
    }
    
    
    //show graycode pattern
    for(int x = 0; x<n ; x++)
    {
        string picture = "horizontal_gray_code_pattern_with" + to_string(x) + " period.jpg";
        string windowname = "horizontal_gray"+to_string(x);
        imwrite(picture,gray_patterns[x]);
        namedWindow(windowname);
        imshow(windowname , gray_patterns[x]);
    }
    waitKey(0);
    

}

//mode 0: vertical pattern
//mode 1: horizontal pattern
void creat_grayCode_patterns(int monitor_w,int monitor_h,int n,bool mode)
{
    if (mode == 0) {
        generateGrayarr_vertical(monitor_w, monitor_h,n);
    } else {
        generateGrayarr_horizontal(monitor_w, monitor_h, n);
    }
}


int main()
{
    creat_grayCode_patterns(160,160,4,1);
    return 0;
}
