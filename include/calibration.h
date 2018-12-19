#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "opencv2/opencv.hpp"

int calibrationroutine(std::vector<cv::Point2f> &camera_points, std::vector<cv::Point3f> &world_points);

enum PointSubset {
       Random_500     = 0x00000000, //!< 500 random points are chosen as subset
       Random_1000    = 0x00000001, //!< 1000 random points are chosen as subset
       Random_5000    = 0x00000002, //!< 5000 random points are chosen as subset
       Random_10000    = 0x00000003, //!< 10000 random points are chosen as subset
       Random_50000    = 0x00000004, //!< 50000 random points are chosen as subset
    };

#endif // CALIBRATION_H
