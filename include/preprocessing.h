#ifndef PREPROCESSING_H
#define PREPROCESSING_H
#include "opencv2/opencv.hpp"
using namespace  cv;
/** @brief Converts vector of gray images into vector of binary images with constant threshold
 *
 */
int convert_binary(std::vector<Mat> &graycode_images);

#endif // PREPROCESSING_H
