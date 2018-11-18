#include <stdio.h>
#include <math.h>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

#define pi 3.1415926

/*
function create_gray_patterns
input: screen_Width: resolution U
       screen_Hight: resolution V
       period_sum: sum of the periods
       image_type: 1 for creating images, which are used to determine column number,
                    other numbers for creating images, which are used to determine row number.
output: three images with different phase shift
*/
int create_gray_patterns(int screen_Width, int screen_Hight, int period_sum, int image_type)
{
    int step_number, offset, amplitude ;
    step_number = 3;
    offset = 122;
    amplitude = 122;
    Mat grayim(screen_Hight, screen_Width, CV_8UC1);

    if(image_type == 1)
    {
        for(int k=0; k<step_number; k++)
        {
            // create patterns with different initial phases
            for( int i = 0; i < grayim.rows; ++i)
                for( int j = 0; j < grayim.cols; ++j )
                {
                    grayim.at<uchar>(i,j) = offset + int(amplitude*
                                (sin(period_sum*2*pi*j/float(screen_Width) + (k-1)*2*pi/3.0)));
                }

            // save images to files
            string name;
            name = "grayim_column_"+to_string(k+1)+".png";
            imwrite(name, grayim);
        }
    }
    else
    {
        for(int k=0; k<step_number; k++)
        {
            // create patterns with different initial phases
            for( int i = 0; i < grayim.rows; ++i)
                for( int j = 0; j < grayim.cols; ++j )
                {
                    grayim.at<uchar>(i,j) = offset + int(amplitude*
                                (sin(period_sum*2*pi*i/float(screen_Hight) + (k-1)*2*pi/3.0)));
                }

            // save images to files
            string name;
            name = "grayim_row_"+to_string(k+1)+".png";
            imwrite(name, grayim);
        }
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
int create_color_patterns(int screen_Width, int screen_Hight, int period_sum, int image_type)
{
    int step_number, offset, amplitude ;
    step_number = 3;
    offset = 122;
    amplitude = 122;
    Mat colorim(screen_Hight, screen_Width, CV_8UC3);

    if(image_type == 1)
    {
        // create patterns with different initial phases
        for( int i = 0; i < colorim.rows; ++i)
            for( int j = 0; j < colorim.cols; ++j )
            {
                Vec3b pixel;
                pixel[0] = offset + int(amplitude*(sin(period_sum*2*pi*j/
                                                       float(screen_Width) + 2*pi/3.0))); //Blue
                pixel[1] = offset + int(amplitude*(sin(period_sum*2*pi*j/
                                                       float(screen_Width)))); //Green
                pixel[2] = offset + int(amplitude*(sin(period_sum*2*pi*j/
                                                       float(screen_Width) - 2*pi/3.0)));//Red
                colorim.at<Vec3b>(i,j) = pixel;
            }

        // save images to files
        imwrite("colorim_column.png", colorim);
    }
    else
    {
        // create patterns with different initial phases
        for( int i = 0; i < colorim.rows; ++i)
            for( int j = 0; j < colorim.cols; ++j )
            {
                Vec3b pixel;
                pixel[0] = offset + int(amplitude*(sin(period_sum*2*pi*i/
                                                       float(screen_Hight) + 2*pi/3.0))); //Blue
                pixel[1] = offset + int(amplitude*(sin(period_sum*2*pi*i/
                                                       float(screen_Hight)))); //Green
                pixel[2] = offset + int(amplitude*(sin(period_sum*2*pi*i/
                                                       float(screen_Hight) - 2*pi/3.0)));//Red
                colorim.at<Vec3b>(i,j) = pixel;
            }

        // save images to files
        imwrite("colorim_row.png", colorim);
    }

    return 0;

}
