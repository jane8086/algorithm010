#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "include/tools.h"
#include "include/preprocessing.h"

using namespace std;
using namespace cv;

#define pi 3.1415926

/*
 * function: calculate_relative_phase
 * input: im1: Mat file of the first phase
 *        im2: Mat file of the second phase
 *        im3: Mat file of the third phase
 *        &relative_phase: address of the vector of mats
 * output:vector of mats
 */
Mat calculate_relative_phase(vector<Mat> &patterns)
{

    // Here we assume that we are showing shifted patterns
    Mat phasemap_relative(patterns[0].rows, patterns[0].cols, CV_8U);


    // get dimension of the image
    int row_size, col_size;
    row_size = patterns[0].rows;
    col_size = patterns[0].cols;

    int period_quarter =64;
    for (int col = 0; col < col_size; col++)
    {
        for (int row = 0; row < row_size; row++ )
        {

            double intensity_1, intensity_2, intensity_3, relative_phase;

            intensity_1 = static_cast<double>(patterns[0].at<uchar>(row,col));
            intensity_2 = static_cast<double>(patterns[1].at<uchar>(row,col));
            intensity_3 = static_cast<double>(patterns[2].at<uchar>(row,col));

            relative_phase = atan(sqrt(3.0)*(intensity_1-intensity_3)/(2*intensity_2-intensity_1-intensity_3));

            relative_phase = relative_phase*2*period_quarter/CV_PI;
            if((2*intensity_2 - intensity_1 - intensity_3) < 0)  // represent the sign of cos value
            {
                relative_phase += 2*period_quarter; //range of angle: -90 ~ 270 grad
            }
            if (relative_phase < 0)         //range of angle: 0~360 grad
            {
                relative_phase += 4*period_quarter;
            }
            phasemap_relative.at<uchar>(row,col) = relative_phase;
        }
    }
    return phasemap_relative;

}

/*
 * function: calculate_absolute_phase
 * input: relative_phase: Mat file of relative phase
 *        period_number: Mat file of period number
 *        range: range of a period, e.g. 360 (grad)
 *        &absolute_phase: address of the vector of mats
 * output: vector of mats
 */
Mat calculate_absolute_phase(Mat &relative_phase, Mat &period_number, int range)
{
    int row_num, col_num;
    row_num = relative_phase.rows;
    col_num = relative_phase.cols;
    Mat phase_abs(row_num, col_num, CV_16UC1);


    for(int row = 0; row < row_num; ++row)
    {
        for(int col = 0; col < col_num; ++col)
        {
            int absolute_period = relative_phase.at<uchar>(row,col) + period_number.at<uchar>(row,col)* range;

            phase_abs.at<uchar>(row,col) = absolute_period;
        }
    }
    return phase_abs;
}

Mat calculate_period_Mat(vector<Mat> &graycodeimages){


    // Here we assume that we are showing shifted patterns
    Mat period_Mat(graycodeimages[0].rows, graycodeimages[0].cols, CV_8U);
    int amount_images = graycodeimages.size();

    // We also assume that this ufnction gets a vector of binary images
    int gray_value[graycodeimages.size()];

    for(int col_i = 0; col_i < graycodeimages[0].cols; col_i ++){

        for(int row_i = 0; row_i < graycodeimages[0].rows; row_i ++){

            //Get binary value
            gray_value[0] = graycodeimages[0].at<uchar>(row_i, col_i); // Get first value

            for( int image_i = 1; image_i < amount_images; image_i++){

                gray_value[image_i] = gray_value[image_i-1]^graycodeimages[image_i].at<uchar>(row_i, col_i);

            }

            //Convert binay to integer
            int period_number = 0;

            for(int j=0; j<amount_images; j++){

                period_number += (gray_value[j])*pow(2,(amount_images-j-1));

            }


            //Assign value to Mat
            period_Mat.at<uchar>(row_i, col_i) = period_number;

        }
    }

    return period_Mat;

}

int calculate_absolute_phasemaps(vector<Mat> &phaseMaps_absolut, int &amount_shifts, int amount_patterns){

    //Load images from folder
    vector<Mat> patterns_phase_captured;
    load_images_phase(patterns_phase_captured, amount_shifts);

    //Maybe do some preprocessing here
    //....


    if(amount_shifts != 3){
        cout <<"Can't calculate relative phase yet! " << endl;
        return -1;
    }

    //create subvector phase shift patterns
    vector<Mat>::const_iterator first = patterns_phase_captured.begin();
    vector<Mat>::const_iterator last = patterns_phase_captured.end();
    vector<Mat> phase_patterns_vertical(first, first+amount_shifts);
    vector<Mat> phase_patterns_horizontal(first+amount_shifts, last);

    //Calculate both relative phasemaps
    Mat relative_phasemap_vertical = calculate_relative_phase(phase_patterns_vertical);
    Mat relative_phasemap_horizontal = calculate_relative_phase(phase_patterns_horizontal);


    ///Calculate absolute phasemaps
    vector<Mat> patterns_graycode_captured;
    load_images_gray(patterns_graycode_captured, amount_shifts, amount_patterns);

    //Do some preporocseeing here:
    convert_binary(patterns_graycode_captured);

    //create subvector graycode patterns
    vector<Mat>::const_iterator first_gray = patterns_graycode_captured.begin();
    vector<Mat>::const_iterator last_gray = patterns_graycode_captured.end();
    vector<Mat> gray_patterns_vertical(first_gray, first_gray+amount_shifts);
    vector<Mat> gray_patterns_horizontal(first_gray+amount_shifts, last_gray);

    //Calculate period number horizontal and vertical
    Mat periodnumber_vertical = calculate_period_Mat(gray_patterns_vertical);
    Mat periodnumber_horizontal = calculate_period_Mat(gray_patterns_horizontal);


    //Calculate absolute phasemap
    Mat absolutephayse_vertical = calculate_absolute_phase(relative_phasemap_vertical, periodnumber_vertical, 360);
    imshow("Absolute Phase", absolutephayse_vertical);
    waitKey();



    //Maybe do some preprocessing here aswell
    //--> Convert images into binary images...




}



