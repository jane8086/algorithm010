#ifndef POINT_CORRESPONDENCES_H
#define POINT_CORRESPONDENCES_H
#include "include/monitor.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

struct Point_Correspondences {
  explicit Point_Correspondences(const vector<Point2f> &image_points,
                                 const vector<Point2f> &display_points);
  vector<Point2f> points_image;
  vector<Point2f> points_display;
};

struct Line_Correspondences {
  // Line_Correspondences()
  vector<vector<Point2f>> pointlines_image;
  vector<vector<Point2f>> pointlines_display;
};

Line_Correspondences
make_line_correspondences(const Point_Correspondences &point_correspondences,
                          const Monitor &monitor, int stepsize,
                          int display_u_i);

#endif // POINT_CORRESPONDENCES_H
