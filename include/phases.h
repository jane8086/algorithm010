#ifndef PHASES_H
#define PHASES_H

#include "opencv2/opencv.hpp"
#include "include/monitor.h"
using namespace cv;
using namespace std;

/** @brief Calculates two absolut phasemaps vertical and horizontal
 *  @param a pixel resolution in width.
 *
 */
Mat calculate_absolute_phase(Mat &relative_phase, Mat &period_number);
Mat calculate_relative_phase_general(vector<Mat> &patterns);
Mat calculate_absolute_phase_novel(Mat &relative_phase, Mat &novel, int period_sum);
int calculate_absolute_phasemaps(vector<Mat> &phaseMaps_absolut, int &amount_shifts, int amount_patterns);
int calculate_realWorld_3d_coordinates(vector<Point3f> &points_world, vector<Point> &points_world_pixel, vector<Point2f> &points_image, Mat &absolutephasemap_hor, Mat &absolutephasemap_ver, Monitor &monitor, int &periods);
Mat calculate_relative_phase(vector<Mat> &patterns);

#endif // PHASES_H
