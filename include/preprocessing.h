#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace  cv;



/** @brief Converts vector of gray images into vector of binary images with constant threshold
 *
 */
int convert_binary(std::vector<Mat> &graycode_images);


/** @brief Reduce moire effect of captured phase shift images vector and save it to another vector
 *  @tparam diameter adjust the strength of filter, suggest between 20 and 80
 */
int reduce_moire(vector<Mat> &phase_shift, vector<Mat> &dst_phase_shift,int diameter);


/** @brief Detect contour of the screen
 *  @tparam crop_amount crop the contour to avoid unwanted noise, DEFAULT crop_amount=1
 */
Mat detect_screen(int &period, int &amount_shifts,int crop_amount);



#endif // PREPROCESSING_H
