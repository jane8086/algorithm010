#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "opencv2/opencv.hpp"
#include <math.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

/** @brief Converts vector of gray images into vector of binary images with
 * constant threshold
 *
 */
int convert_binary(std::vector<Mat> &graycode_images);

/** @brief Reduce moire effect of captured phase shift images vector and save it
 * to another vector
 *  @tparam diameter adjust the strength of filter, suggest between 20 and 80
 */
int reduce_moire(vector<Mat> &phase_shift, vector<Mat> &dst_phase_shift,
                 int diameter);

/** @brief Detect contour of the screen
 *  @tparam crop_amount crop the contour to avoid unwanted noise, DEFAULT
 * crop_amount=1
 */
Mat detect_screen(int &amount_pattern, int &amount_shifts, int crop_amount = 1);

int remove_noise(Mat &relative, Mat &frame);

int detect_edge_phase_vertical(Mat &relative, Mat &frame, Mat &edge_map);
int detect_edge_phase_horizontal(Mat &relative, Mat &frame, Mat &edge_map);

int correct_period_vertical(Mat &extract_point, Mat &period_number_vertical);

int correct_period_horizontal(Mat &extract_point, Mat &period_number_horizontal);

int sgn(double x);

int refraction(Point3f &k2dvector, Point3f &display_pixel_mm,
               Point3f &correct_display_pixel);


void substract_offset_black(const Mat &blackMat, vector<Mat> &taken_images);

#endif // PREPROCESSING_H
