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
    // get dimension of the image
    int row_num, col_num;
    row_num = im1.rows;
    col_num = im1.cols;

    // definition of Mat file
    int period_quarter = 64;    //represent pi/2, choose 64 for convenience of displaying as gray image
    Mat phase_rel(row_num, 3*col_num, CV_8UC1);

    //calculate the relative phase and  save in Mat: phase_rel
    for(int row = 0; row < row_num; row++)
    {
        for(int col = 0; col < 3*col_num; col++)
        {
            double intensity_1, intensity_2, intensity_3;
            // read the intensity value of three Mats
            intensity_1 = (double)im1.at<uchar>(row,col);
            intensity_2 = (double)im2.at<uchar>(row,col);
            intensity_3 = (double)im3.at<uchar>(row,col);

            // calculate tangent value of every pixel
            double phase_tangent, phase_relative;
            phase_tangent = sqrt(3.0)*(intensity_1 - intensity_3)/(2*intensity_2 - intensity_1 - intensity_3);

            // calculate the arc tangent value of every pixel
            phase_relative = atan(phase_tangent); // range of angle here: -pi/2 ~ pi/2

            // save the angle as interger, attention here: period_quarter represent pi/2, and it can be change.
            int phase_relative_int;
            // modify the calculated phase value to the range: 0~360 grad
            phase_relative_int = (int)(phase_relative*2*period_quarter/pi); // range of angle here: -90~90 grad
            if((2*intensity_2 - intensity_1 - intensity_3) < 0)  // represent the sign of cos value
            {
                phase_relative_int += 2*period_quarter; //range of angle: -90 ~ 270 grad
            }
            if (phase_relative_int < 0)         //range of angle: 0~360 grad
            {
                phase_relative_int += 4*period_quarter;
            }

            phase_rel.at<uchar>(row, col) = phase_relative_int;

        }
    }

    /* Because the dimension of the phase_rel is row_num x 3*col_num, its column number should be cut to 1/3,
     * as following codes.
    */
    Mat phase_relative(row_num, col_num, CV_8UC1);
    for(int row = 0; row < row_num; row++)
    {
        for(int col = 0; col < col_num; col++)
        {
            phase_relative.at<uchar>(row,col) = phase_rel.at<uchar>(row,3*col); //range of angle: 0 ~ 360
        }
    }

    imwrite("relativePhase.png",phase_relative);
    relative_phase.push_back(phase_relative.clone());

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
