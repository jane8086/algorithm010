#include "include/monitor.h"
#include "include/point_correspondeces.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

double costvalue(const vector<vector<Point2f>> &camera_pointlines,
                 const vector<Vec4d> &approx_lines) {

  if (camera_pointlines.size() != approx_lines.size()) {

    cout << "camera_lines and approimated_lines must have the same size!";
    return -1;
  }

  // calculate cumulated distance
  double distance = 0;
  for (int i = 0; i < (int)approx_lines.size(); i++) {

    Point2f p0(approx_lines[i][2], approx_lines[i][3]);
    Point2f v(approx_lines[i][0], approx_lines[i][1]);

    for (int j = 0; j < (int)camera_pointlines[i].size(); j++) {
      // min distance between line and point cv::norm((p0-A)-((p0-A).dot(n))*n)
      distance += cv::norm((p0 - camera_pointlines[i][j]) -
                           ((p0 - camera_pointlines[i][j]).dot(v)) * v);
    }
  }

  return distance;
}

vector<Vec4d> fitLines(const vector<vector<Point2f>> &pointlines_c) {

  vector<Vec4d> straight_lines(pointlines_c.size());

  for (int i = 0; i < (int)pointlines_c.size(); i++) {
    fitLine(pointlines_c[i], straight_lines[i], CV_DIST_L2, 0, 0.01, 0.01);
  }

  return straight_lines;
}

Point2f distort_point(const Point2f &undistorted_point,
                      const Point2f &dist_center, const double d) {

  double r = cv::norm(undistorted_point - dist_center);

  double x_u =
      dist_center.x + (undistorted_point.x - dist_center.x) / (1 + d * r * r);
  double y_u =
      dist_center.y + (undistorted_point.y - dist_center.y) / (1 + d * r * r);

  Point2f distorted(x_u, y_u);
  return distorted;
}

void rectify_all_image_points(const vector<Point2f> &image_points,
                              vector<Point2f> &rectified_image_points,
                              const double distCoef) {

  assert(image_points.size() > 0);

  for (unsigned long point_i = 0; point_i < image_points.size(); ++point_i) {

    Point2f rectified_point =
        distort_point(image_points[point_i], Point(644, 483), distCoef);
    rectified_image_points[point_i] = rectified_point;
  }
}

vector<vector<Point2f>>
distortLinePointsdM(const Point2f &dist_center,
                    const vector<vector<Point2f>> &camera_pointlines,
                    double distortioncoeff) {

  vector<vector<Point2f>> undist_camera_pointlines(camera_pointlines.size());

  for (unsigned long i = 0; i < camera_pointlines.size(); ++i) {

    for (unsigned long j = 0; j < camera_pointlines[i].size(); ++j) {

      Point2f distorted =
          distort_point(camera_pointlines[i][j], dist_center, distortioncoeff);
      undist_camera_pointlines[i].push_back(distorted);
    }
  }

  return undist_camera_pointlines;
}

double calculate_distortionParameter(Point_Correspondences &pc,
                                     const Monitor &monitor) {
  constexpr int stepsize = 10;
  constexpr int display_u_i = 0;
  auto line_correspondences =
      make_line_correspondences(pc, monitor, stepsize, display_u_i);

  vector<Vec4d> fitted_lines(line_correspondences.pointlines_image.size());
  vector<vector<Point2f>> distorted_imagepoints =
      line_correspondences.pointlines_image;
  vector<double> distances;
  int i = 0;

  constexpr double magic_value = -0.000005;
  for (double distCoeff_i = 0; distCoeff_i > magic_value;
       distCoeff_i -= 0.000000001, i++) {

    distorted_imagepoints =
        distortLinePointsdM(Point2f(644.0, 483.0),
                            line_correspondences.pointlines_image, distCoeff_i);
    fitted_lines = fitLines(distorted_imagepoints);
    distances.push_back(costvalue(distorted_imagepoints, fitted_lines));
    if (i > 1 && distances[i] > distances[i - 1]) {

      return distCoeff_i;
    }
  }
}
