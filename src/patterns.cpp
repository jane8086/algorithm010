#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "include/tools.h"

using namespace std;
using namespace cv;

#define pi 3.1415926

#define offset 122
#define amplitude 122

/*
function create_patterns_novel
input: screen_Width: resolution U
       screen_Hight: resolution V
       period_sum: sum of the periods
output: vector of mats
*/
int create_patterns_novel(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns_novel)
{
    int step_number, interval_pixel_row, interval_pixel_col, period_number;
    interval_pixel_row = (int)(screen_Hight/period_sum);
    interval_pixel_col = (int)(screen_Width/period_sum);
    float interval_angle;
    interval_angle = 2*CV_PI/(float)period_sum;

    step_number = 3;
    //offset = 122;
    //amplitude = 122;
    Mat grayim(screen_Hight, screen_Width, CV_8UC1);

    for(int k=0; k<step_number; k++)
    {
        // create vertical patterns with different initial phases
        for( int i = 0; i < grayim.rows; ++i)
            for( int j = 0; j < grayim.cols; ++j )
            {
                period_number = (int)(j/interval_pixel_col);
                grayim.at<uchar>(i,j) = offset + int(amplitude*
                                        (cos((float)period_number*interval_angle + (k-1)*2*CV_PI/3.0)));
            }

        // pushback mat to vector
        patterns_novel.push_back(grayim.clone());
    }

    for(int k=0; k<step_number; k++)
    {
        // create horizontal patterns with different initial phases
        for( int i = 0; i < grayim.rows; ++i)
            for( int j = 0; j < grayim.cols; ++j )
            {
                period_number = (int)(i/interval_pixel_row);
                grayim.at<uchar>(i,j) = offset + int(amplitude*
                                        (cos((float)period_number*interval_angle + (k-1)*2*CV_PI/3.0)));

            }

        // pushback
        patterns_novel.push_back(grayim.clone());
    }

    return 0;
}

/*
function create_patterns_phaseshift_general
input: screen_Width: resolution U
       screen_Hight: resolution V
       period_sum: sum of the periods
       image_type: 1 for creating images, which are used to determine column number,
                    other numbers for creating images, which are used to determine row number.
output: vector of mats
*/
int create_patterns_phaseshift_general(int screen_Width, int screen_Hight, int period_sum, int step_number, vector<Mat> &patterns_phaseshift)
{
    //int offset, amplitude ;
    //offset = 122;
    //amplitude = 122;
    Mat grayim(screen_Hight, screen_Width, CV_8UC1);

    for(int k=1; k<step_number+1; k++)
    {
        // create vertical patterns with different initial phases
        for( int i = 0; i < grayim.rows; ++i)
            for( int j = 0; j < grayim.cols; ++j )
            {
                grayim.at<uchar>(i,j) = offset + int(amplitude*
                                           (cos(period_sum*2*pi*j/(float)screen_Width - 2*pi*k/(float)step_number)));
            }

        // pushback mat to vector
        patterns_phaseshift.push_back(grayim.clone());
    }

    for(int k=1; k<step_number+1; k++)
    {
        // create horizontal patterns with different initial phases
        for( int i = 0; i < grayim.rows; ++i)
            for( int j = 0; j < grayim.cols; ++j )
            {
                grayim.at<uchar>(i,j) = offset + int(amplitude*
                                           (cos(period_sum*2*pi*i/float(screen_Hight) - 2*pi*k/(float)step_number)));
            }

        // pushback
        patterns_phaseshift.push_back(grayim.clone());
    }

    return 0;
}

/*
function create_patterns_phaseshift
input: screen_Width: resolution U
       screen_Hight: resolution V
       period_sum: sum of the periods
       image_type: 1 for creating images, which are used to determine column number,
                    other numbers for creating images, which are used to determine row number.
output: vector of mats
*/
int create_patterns_phaseshift(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns_phaseshift)
{
    int step_number;//, offset, amplitude ;
    step_number = 3;
    //offset = 122;
    //amplitude = 122;
    Mat grayim(screen_Hight, screen_Width, CV_8UC1);

    for(int k=0; k<step_number; k++)
    {
        // create vertical patterns with different initial phases
        for( int i = 0; i < grayim.rows; ++i)
            for( int j = 0; j < grayim.cols; ++j )
            {
                grayim.at<uchar>(i,j) = offset + int(amplitude*
                                                     (cos(period_sum*2*pi*j/float(screen_Width) + (k-1)*2*pi/3.0)));
            }

        // pushback mat to vector
        patterns_phaseshift.push_back(grayim.clone());
    }

    for(int k=0; k<step_number; k++)
    {
        // create horizontal patterns with different initial phases
        for( int i = 0; i < grayim.rows; ++i)
            for( int j = 0; j < grayim.cols; ++j )
            {
                grayim.at<uchar>(i,j) = offset + int(amplitude*
                                                     (cos(period_sum*2*pi*i/float(screen_Hight) + (k-1)*2*pi/3.0)));
            }

        // pushback
        patterns_phaseshift.push_back(grayim.clone());
    }

    return 0;
}

/*
function create_color_patterns
input: screen_Width: resolution U
       screen_Hight: resolution V
       period_sum: sum of the periods
       image_type: 1 for creating images, which are used to determine column number,
                    other numbers for creating images, which are used to determine row number.
output: one image, whose three channels have different phase shift. Order: RGB (-2pi/3 0 2p/3)
*/
int create_patterns_colorphaseshift(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns_colorphaseshift)
{
    int step_number;//, offset, amplitude ;
    step_number = 3;
    //offset = 122;
    //amplitude = 122;
    Mat colorim_hor(screen_Hight, screen_Width, CV_8UC3);
    Mat colorim_ver(screen_Hight, screen_Width, CV_8UC3);

    // create patterns with different initial phases
    for( int i = 0; i < colorim_hor.rows; ++i)
        for( int j = 0; j < colorim_hor.cols; ++j )
        {
            Vec3b pixel;
            pixel[0] = offset + int(amplitude*(cos(period_sum*2*pi*j/
                                                   float(screen_Width) + 2*pi/3.0))); //Blue
            pixel[1] = offset + int(amplitude*(cos(period_sum*2*pi*j/
                                                   float(screen_Width)))); //Green
            pixel[2] = offset + int(amplitude*(cos(period_sum*2*pi*j/
                                                   float(screen_Width) - 2*pi/3.0)));//Red
            colorim_hor.at<Vec3b>(i,j) = pixel;
        }

    // save images to files
    patterns_colorphaseshift.push_back(colorim_hor);

    // create patterns with different initial phases
    for( int i = 0; i < colorim_ver.rows; ++i)
        for( int j = 0; j < colorim_ver.cols; ++j )
        {
            Vec3b pixel;
            pixel[0] = offset + int(amplitude*(cos(period_sum*2*pi*i/
                                                   float(screen_Hight) + 2*pi/3.0))); //Blue
            pixel[1] = offset + int(amplitude*(cos(period_sum*2*pi*i/
                                                   float(screen_Hight)))); //Green
            pixel[2] = offset + int(amplitude*(cos(period_sum*2*pi*i/
                                                   float(screen_Hight) - 2*pi/3.0)));//Red
            colorim_ver.at<Vec3b>(i,j) = pixel;
        }

    // save images to files
    patterns_colorphaseshift.push_back(colorim_ver);

    return 0;

}

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
int create_patterns_graycodevertical(int screen_Width,int screen_Hight,int perdiod_sum, vector<Mat> &graycodevertical)
{

    // adjust period_sum
    perdiod_sum = log2(perdiod_sum);


    // base case
    if (perdiod_sum <= 0)
        return -1;

    //--THE CODE BELOW, CREAT A VECTOR OF GRAY CODE---
    // 'arr' will store all generated codes
    vector<string> arr;

    // start with one-bit pattern
    arr.push_back("0");
    arr.push_back("1");

    //-- Every iteration of this loop generates 2*i codes from previously

    // generated i codes.
    int i, j;

    for (i = 2; i < (1<<perdiod_sum); i = i<<1)
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
    Mat gray_pattern(screen_Hight,screen_Width,CV_8UC1);//create a blank pattern

    // convert gray code into several patterns which stored in a vector
    for (int p = 1 ; p <= perdiod_sum ; p++)         //gray_code_pattern with n period
    {
        double arrsiz;
        arrsiz = pow(2,p);
        gray_pattern =255;                //initialize Mat before use it
        for(int x = 1 ; x <= arrsiz ; x++)//
        {

            double unit_w ;
            unit_w = screen_Width / arrsiz ;
            string s;
            s = arr[x-1];
            int tem;
            tem = s[perdiod_sum-1];
            if ((tem-48)==0)
            {
                gray_pattern(Range(0, screen_Hight),Range((x-1)*unit_w, x*unit_w))=0;//fill black in pattern
            }
        }
        graycodevertical.push_back(gray_pattern.clone());
    }

    return 0;

}

// monitor width andscreen_Widthnd perioscreen_Widthrizontal version
int create_patterns_graycodehorizontal(int screen_Width,int screen_Hight,int period_sum, vector<Mat> &patterns_graycode_horizontal)
{
    // adjust period
    period_sum = log2(period_sum);

    // base case
    if (period_sum <= 0)
    {
        cout << "Period number must be greater zero" << endl;
        return -1;
    }

    //--THE CODE BELOW, CREAT A VECTOR OF GRAY CODE---
    // 'arr' will store all generated codes
    vector<string> arr;

    // start with one-bit pattern
    arr.push_back("0");
    arr.push_back("1");

    //-- Every iteration of this loop generates 2*i codes from previously
    // generated i codes.
    int i, j;

    for (i = 2; i < (1<<period_sum); i = i<<1)
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
    Mat gray_pattern(screen_Hight,screen_Width,CV_8UC1);//create a blank pattern

    // convert gray code into several patterns which stored in a vector
    for (int p = 1 ; p <= period_sum ; p++)         //gray_code_pattern with n period
    {
        double arrsiz;
        arrsiz = pow(2,p);
        gray_pattern =255;                //initialize Mat before use it
        for(int x = 1 ; x <= arrsiz ; x++)
        {

            double unit_h ;
            unit_h = screen_Hight / arrsiz ;
            string s;
            s = arr[x-1];
            int tem;
            tem = s[period_sum-1];
            if ((tem-48)==0)
            {
                gray_pattern(Range((x-1)*unit_h, x*unit_h),Range(0,screen_Width))=0;//fill black in pattern
            }
         }
        patterns_graycode_horizontal.push_back(gray_pattern.clone());
    }

    return 0;

}

int create_patterns_offset(int screen_Width, int screen_Hight, vector<Mat> &output ){

    Mat allwhite(screen_Hight, screen_Width, CV_8UC1, Scalar(255));
    Mat allblack(screen_Hight, screen_Width, CV_8UC1, Scalar(0));
    output.push_back(allwhite);
    output.push_back(allblack);
    return 0;


}

int create_patterns_all(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns,int amount_shifts, int color_pattern ,int novel_method){

    if(!isPowerOfTwo(period_sum)){
        cout << "Period number must be power of two !" << endl;
        return -1;
    }

    if(color_pattern){

        create_patterns_colorphaseshift(screen_Width, screen_Hight, period_sum, patterns);
    }else{

        if(create_patterns_phaseshift_general(screen_Width, screen_Hight, period_sum, amount_shifts, patterns))
            return -1;
    }

    if(novel_method){
        if(create_patterns_novel(screen_Width, screen_Hight, period_sum, patterns))
            return -1;
    }else{

        if(create_patterns_graycodehorizontal(screen_Width, screen_Hight, period_sum, patterns))
            return -1;
        if(create_patterns_graycodevertical(screen_Width, screen_Hight, period_sum, patterns))
            return -1;
    }

    if(create_patterns_offset(screen_Width, screen_Hight, patterns))
        return -1;

    return 0;

}



