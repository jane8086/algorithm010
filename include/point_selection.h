#ifndef POINT_SELECTION_H
#define POINT_SELECTION_H

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void paper_phasemap_intersection(const vector<Mat> &absolute_phasemaps,
                                 vector<Point2d> &new_imagepoints,
                                 vector<Point2d> &new_average_phasevalues);
void smooth_phasemap_results(const vector<Point2d> &new_imagepoints,
                             const vector<Point2d> phase_values,
                             vector<Point2d> &new_imagepoints_smooth,
                             vector<Point2d> &phase_values_smooth);
#endif // POINT_SELECTION_H
