#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "opencv2/opencv.hpp"

int calibrationroutine(std::vector<cv::Point2f> &camera_points,
                       std::vector<cv::Point3f> &world_points,
                       double const error);

enum class PointSubset {
  Random_500,   //!< 500 random points are chosen as subset
  Random_1000,  //!< 1000 random points are chosen as subset
  Random_5000,  //!< 5000 random points are chosen as subset
  Random_10000, //!< 10000 random points are chosen as subset
  Random_50000, //!< 50000 random points are chosen as subset
};

#endif // CALIBRATION_H
