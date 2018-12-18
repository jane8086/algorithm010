#ifndef CAMERA
#define CAMERA

#include "flycapture/FlyCapture2.h"
#include "opencv2/opencv.hpp"


/** @brief Connects, adjusts camera and captures patterns.
 *
 */
int camera_routine(FlyCapture2::Camera & camera, std::vector<cv::Mat> &patterns, std::vector<cv::Mat> &patterns_captured);



/** @brief Adjust gain of camera: lower the gain if too bright, increase the gain if to dark
 *  @tparam brighter_percent_threshold : (%) the percentage of pixels, which have different values with threshold
 *                             DEFAULT = 0.00 : none of pixel has higher value than threshold
 */

int camera_gain_adjustment(FlyCapture2::Camera &camera, cv::Mat &threshold_image, int &threshold_value, float &brighter_percent_threshold);

//int camera_brightness_adjust(Camera &camera, Mat &gradient, float white_threshold);


#endif // CAMERA

