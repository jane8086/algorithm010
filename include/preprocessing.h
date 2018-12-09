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

int reduce_moire(vector<Mat> &phase_shift, vector<Mat> &dst_phase_shift,int diameter);

#endif // PREPROCESSING_H
