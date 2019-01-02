#ifndef LINES_RECTIFICATION_H
#define LINES_RECTIFICATION_H

#include "include/monitor.h"
#include "include/point_correspondeces.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

double calculate_distortionParameter(Point_Correspondences &pc,
                                   const Monitor &monitor);
void rectify_all_image_points(const vector<Point2f> &image_points, vector<Point2f> &rectified_image_points, const double distCoef);

#endif // LINES_RECTIFICATION_H
