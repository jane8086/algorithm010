#ifndef CAMERA
#define CAMERA

#include "flycapture/FlyCapture2.h"
#include "opencv2/opencv.hpp"

/** @brief Connects, adjusts camera and captures patterns.
 *
 */
int camera_routine(FlyCapture2::Camera &camera, std::vector<cv::Mat> &patterns,
                   std::vector<cv::Mat> &patterns_captured);

#endif // CAMERA
