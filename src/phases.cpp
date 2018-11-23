#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"

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
int calculate_relative_phase(Mat im1, Mat im2, Mat im3, vector<Mat> &relative_phase)
{
    int row_num, col_num;
    row_num = im1.rows;
    col_num = im1.cols;
    Mat phase_rel(row_num, col_num, CV_16UC1);
    for(int row = 0; row < row_num; ++row)
    {
        for(int col = 0; col < col_num; ++col)
        {
            double intensity_1, intensity_2, intensity_3;
            // read the intensity value of three Mats
            intensity_1 = (double)im1.at<uchar>(row,col);
            intensity_2 = (double)im2.at<uchar>(row,col);
            intensity_3 = (double)im3.at<uchar>(row,col);
            double phase_tangent, phase_relative;
            phase_tangent = sqrt(3.0)*(intensity_1 - intensity_3)/(2*intensity_2 - intensity_1 - intensity_3);
            phase_relative = atan(phase_tangent); // range of angle here: -pi/2 ~ pi/2

            if((2*intensity_2 - intensity_1 - intensity_3) < 0)  // represent the sign of cos value
            {
                phase_relative += pi; //range of angle: -pi/2 ~ 3*pi/2
            }

            phase_relative += pi/2.0; // range of angle here: 0~2*pi
            phase_rel.at<uchar>(row,col) = (int)(phase_relative*180/pi); //range of angle: 0 ~ 360
        }
    }
    relative_phase.push_back(phase_rel.clone());

    return 0;
}

/*
 * function: calculate_absolute_phase
 * input: relative_phase: Mat file of relative phase
 *        period_number: Mat file of period number
 *        range: range of a period, e.g. 360 (grad)
 *        &absolute_phase: address of the vector of mats
 * output: vector of mats
 */
int calculate_absolute_phase(Mat relative_phase, Mat period_number, int range, vector<Mat> &absolute_phase)
{
    int row_num, col_num;
    Mat phase_abs(row_num, col_num, CV_16UC1);
    row_num = relative_phase.rows;
    col_num = relative_phase.cols;
    for(int row = 0; row < row_num; ++row)
    {
        for(int col = 0; col < col_num; ++col)
        {
            phase_abs.at<uchar>(row,col) = relative_phase.at<uchar>(row,col) +
                                                period_number.at<uchar>(row,col) * range;
        }
    }
    absolute_phase.push_back(phase_abs.clone());

    return 0;
}
