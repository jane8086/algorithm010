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
Mat calculate_relative_phase(vector<Mat> patterns, Mat &relative_phases)
{

    // Here we assume that we are showing shifted patterns
    Mat phasemap_relative;


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

int load_phaspatterns(vector<Mat> &phase_images, int amount_shifts){




}
