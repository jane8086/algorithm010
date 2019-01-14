#include "include/monitor.h"
#include "include/point_correspondeces.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Point_Correspondences::Point_Correspondences(
    const vector<Point2d> &image_points, const vector<Point2d> &display_points)
    : points_image(image_points), points_display(display_points) {}

Line_Correspondences
make_line_correspondences(const Point_Correspondences &point_correspondences,
                          const Monitor &monitor, int stepsize,
                          int display_u_start_index) {
  assert(stepsize > 0.);

  // for each step select displaypoints in y direction with corresponding image
  // points

  auto display_u_index = display_u_start_index;
  Line_Correspondences line_correspondences;
  while (display_u_index < monitor.size_x) {

    vector<Point2d> line_image_i;
    vector<Point2d> line_display_i;
    for (auto point_i = 0; point_i < point_correspondences.points_image.size();
         ++point_i) {

      double distance_to_line = abs(
          display_u_index - point_correspondences.points_display[point_i].x);
      constexpr double tolerance = 0.2;

      if (distance_to_line < tolerance) {
        line_image_i.push_back(point_correspondences.points_image[point_i]);
        line_display_i.push_back(point_correspondences.points_display[point_i]);
      }
    }
    constexpr int minimum_points_per_line = 200;
    if (line_image_i.size() > minimum_points_per_line) {
      line_correspondences.pointlines_image.push_back(line_image_i);
      line_correspondences.pointlines_display.push_back(line_display_i);
    }
    display_u_index += stepsize;
  }
  return line_correspondences;
}
