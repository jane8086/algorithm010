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
    Mat phasemap_relative(patterns[0].rows, patterns[0].cols, CV_32FC1);


    // get dimension of the image
    int row_size, col_size;
    row_size = patterns[0].rows;
    col_size = patterns[0].cols;

    int period_quarter =90;
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
            phasemap_relative.at<float>(row,col) = relative_phase;
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
Mat calculate_absolute_phase(Mat &relative_phase, Mat &period_number)
{
    int row_num, col_num;
    row_num = relative_phase.rows;
    col_num = relative_phase.cols;
    Mat phase_abs(row_num, col_num, CV_32FC1);
    int range = 360;


    for(int row = 0; row < row_num; row++)
    {
        for(int col = 0; col < col_num; col++)
        {
            float period = period_number.at<uchar>(row, col);
            float absolute_period = relative_phase.at<float>(row,col) + period*range;
            phase_abs.at<float>(row,col) = absolute_period;
        }
    }
    return phase_abs;
}

Mat calculate_period_Mat(vector<Mat> &graycodeimages){


    // Here we assume that we are showing shifted patterns
    Mat period_Mat(graycodeimages[0].rows, graycodeimages[0].cols, CV_8U);
    int amount_images = static_cast<int>(graycodeimages.size());

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

int calculate_absolute_phasemaps(vector<Mat> &phaseMaps_absolut, int &amount_phaseshifts, int amount_patterns){

    //Load images from folder
    vector<Mat> patterns_phase_captured;
    load_images_phase(patterns_phase_captured, amount_phaseshifts);

    //Maybe do some preprocessing here
    //....


    if(amount_phaseshifts != 3){
        cout <<"Can't calculate relative phase yet! " << endl;
        return -1;
    }

    //create subvector phase shift patterns
    vector<Mat>::const_iterator first = patterns_phase_captured.begin();
    vector<Mat>::const_iterator last = patterns_phase_captured.end();
    vector<Mat> phase_patterns_vertical(first, first+amount_phaseshifts);
    vector<Mat> phase_patterns_horizontal(first+amount_phaseshifts, last);

    //Calculate both relative phasemaps
    Mat relative_phasemap_vertical = calculate_relative_phase(phase_patterns_vertical);
    Mat relative_phasemap_horizontal = calculate_relative_phase(phase_patterns_horizontal);


    ///Calculate absolute phasemaps
    vector<Mat> patterns_graycode_captured;
    load_images_gray(patterns_graycode_captured, amount_phaseshifts, amount_patterns);

    //Do some preporocseeing here:
    convert_binary(patterns_graycode_captured);

    //create subvector graycode patterns
    vector<Mat>::const_iterator first_gray = patterns_graycode_captured.begin();
    vector<Mat>::const_iterator last_gray = patterns_graycode_captured.end();
    vector<Mat> gray_patterns_vertical(first_gray, first_gray+2); //ststic for period and amount of shifts
    vector<Mat> gray_patterns_horizontal(first_gray+2, last_gray);//static for period and amount of shifts

    //Calculate period number horizontal and vertical
    Mat periodnumber_horizontal = calculate_period_Mat(gray_patterns_vertical);
    Mat periodnumber_vertical = calculate_period_Mat(gray_patterns_horizontal);


    //Calculate absolute phasemap
    Mat absolutephase_vertical = calculate_absolute_phase(relative_phasemap_vertical, periodnumber_vertical);
    Mat absolutephase_horizontal = calculate_absolute_phase(relative_phasemap_horizontal, periodnumber_horizontal);
    imshow("absolutephase_horizontal", absolutephase_horizontal/(4*360)); // normalized picture
    imshow("absolutephase_vertical", absolutephase_vertical/(4*360));

    waitKey();

    //Normalize data for imshow





    //Maybe do some preprocessing here aswell
    //--> Convert images into binary images...




}



