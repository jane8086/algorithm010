#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

bool have_same_phasevalue(const Point2f &phase_values,
                          const double max_phase_difference) {

  if (abs(phase_values.x - phase_values.y) < max_phase_difference)
    return true;
  return false;
}

void smooth_phasemap_results(const vector<Point2d> &new_imagepoints,
                             const vector<Point2d> phase_values,
                             vector<Point2d> &new_imagepoints_smooth,
                             vector<Point2d> &phase_values_smooth) {

  // We could just get rid of points which phase values are not nearly the same
  for (unsigned long point_i = 0; point_i < new_imagepoints.size(); ++point_i) {

    bool neighbourhood_is_smooth;
    bool conditions = false;

    if (conditions) {

      new_imagepoints_smooth[point_i] = new_imagepoints[point_i];
      phase_values_smooth[point_i] = phase_values[point_i];
    }

    // Resize vectors
    new_imagepoints_smooth.shrink_to_fit();
    phase_values_smooth.shrink_to_fit();
  }
}

double
phase_average_from_neighbours(const vector<Point2f> &neighbourhood_points,
                              const Mat &phasemap) {

  double phase_sum = 0;

  for (const auto &point : neighbourhood_points) {
    phase_sum += phasemap.at<float>(point);
  }

  assert(neighbourhood_points.size() > 0);
  // auto avg_phase_sum = (phase_sum / neighbourhood_points.size());
  vector<float> phasemapvalues = {phasemap.at<float>(neighbourhood_points[0]),
                                  phasemap.at<float>(neighbourhood_points[1]),
                                  phasemap.at<float>(neighbourhood_points[2]),
                                  phasemap.at<float>(neighbourhood_points[3])};

  return phase_sum / (float)neighbourhood_points.size();
}

bool intersection(const Point2d o1, const Point2d p1, const Point2d o2,
                  const Point2d p2, Point2d &r) {
  Point2d x = o2 - o1;
  Point2d d1 = p1 - o1;
  Point2d d2 = p2 - o2;

  float cross = d1.x * d2.y - d1.y * d2.x;
  if (abs(cross) < /*EPS*/ 1e-8)
    return false;

  double t1 = (x.x * d2.y - x.y * d2.x) / cross;
  r = o1 + d1 * t1;
  return true;
}

bool line_line_intersection(Point2d o1, Point2d v1, Point2d o2, Point2d v2,
                            Point2d &r) {
  Point2d x = o2 - o1;
  Point2d d1 = v1;
  Point2d d2 = v2;

  double cross = d1.x * d2.y - d1.y * d2.x;
  if (abs(cross) < /*EPS*/ 1e-16)
    return false;

  double t1 = (x.x * d2.y - x.y * d2.x) / cross;
  r = o1 + d1 * t1;
  return true;
}

void calculate_phase_intersection_lines(const Mat &phasemap,
                                        const vector<Point2f> &four_neighbours,
                                        Point2d &p0_2d, Point2d &vector_2d,
                                        double &rms) {

  // Create Average Plane in Phase Direction
  double phase_average =
      phase_average_from_neighbours(four_neighbours, phasemap);

  // Create Equation System
  cv::Mat matX(four_neighbours.size(), 3, CV_32FC1);
  cv::Mat matZ(four_neighbours.size(), 1, CV_32FC1);
  cv::Mat res;

  for (size_t i = 0, end = four_neighbours.size(); i < end; ++i) {
    matX.at<float>(i, 0) = four_neighbours[i].x;
    matX.at<float>(i, 1) = four_neighbours[i].y;
    matX.at<float>(i, 2) = phasemap.at<float>(four_neighbours[i]);
    matZ.at<float>(i, 0) = 1;
  }

  // Solve equation
  solve(matX, matZ, res, CV_SVD);
  double A = res.at<float>(0, 0);
  double B = res.at<float>(0, 1);
  double C = res.at<float>(0, 2);

  // Calculate RMS
  assert(abs(C) > 0.0);
  Point3d normal_vector_plane(A, B, C);
  Point3d point_on_plane(0, 0, 1 / C);
  double square_distances = 0;
  for (const auto &point : four_neighbours) {

    double distance = abs(A * (double)point.x + B * (double)point.y +
                          C * (double)phasemap.at<float>(point) - 1.0) /
                      norm(normal_vector_plane);
    square_distances += pow(distance, 2);
  }

  assert(four_neighbours.size() > 0);
  rms = sqrt((square_distances) / four_neighbours.size());

  // Calculate Cross product with average plane
  Mat plane_a = (Mat_<double>(3, 1) << A, B, C);
  Mat plane_b = (Mat_<double>(3, 1) << 0, 0, phase_average);
  Mat cross = plane_a.cross(plane_b);

  // Get Equation in Parameterform and set x to zero
  vector<double> Plane_A = {B, C, 1};
  vector<double> Plane_B = {0, 1, phase_average};

  // Compute Equation Systen
  Mat matX2 =
      (Mat_<double>(2, 2) << Plane_A[0], Plane_A[1], Plane_B[0], Plane_B[1]);
  Mat matZ2 = (Mat_<double>(2, 1) << Plane_A[2], Plane_B[2]);
  Mat res2 = (Mat_<double>(2, 1) << 0, 0);
  solve(matX2, matZ2, res2);

  // This is line:
  Point3d p0(0, res2.at<double>(0), res2.at<double>(1));
  Point3d vector(cross.at<double>(0), cross.at<double>(1), cross.at<double>(2));

  // This is line in 2d
  p0_2d.x = 0;
  p0_2d.y = res2.at<double>(0);
  vector_2d.x = cross.at<double>(0);
  vector_2d.y = cross.at<double>(1);

  //
}

bool are_points_relative_phase_neighbours(const Mat &relative_phasemap,
                                          vector<Point2f> neighbours) {
  // TODO see if phase_jump can be interpolated properly as well
  constexpr double max_phase_differemce = 200;

  vector<double> phase_differences(4);
  phase_differences[0] = relative_phasemap.at<float>(neighbours[0]) -
                         relative_phasemap.at<float>(neighbours[1]);
  phase_differences[1] = relative_phasemap.at<float>(neighbours[0]) -
                         relative_phasemap.at<float>(neighbours[2]);
  phase_differences[2] = relative_phasemap.at<float>(neighbours[2]) -
                         relative_phasemap.at<float>(neighbours[3]);
  phase_differences[3] = relative_phasemap.at<float>(neighbours[1]) -
                         relative_phasemap.at<float>(neighbours[3]);

  for (const auto &phase_difference : phase_differences) {
    if (abs(phase_difference) > max_phase_differemce)
      return false;
  }

  return true;
}

vector<Point2f> choose_four_neighbouring_imagepoints(const int column_i,
                                                     const int row_i) {

  vector<Point2f> neighbouring_image_pixels(4);
  Point2f upperleft(column_i, row_i);
  Point2f upper_right(column_i + 1, row_i);
  Point2f lower_left(column_i, row_i + 1);
  Point2f lower_right(column_i + 1, row_i + 1);
  neighbouring_image_pixels[0] = upperleft;
  neighbouring_image_pixels[1] = upper_right;
  neighbouring_image_pixels[2] = lower_left;
  neighbouring_image_pixels[3] = lower_right;
  return neighbouring_image_pixels;
}

void paper_phasemap_intersection(const vector<Mat> &absolute_phasemaps,
                                 vector<Point2d> &new_imagepoints,
                                 vector<Point2d> &new_average_phasevalues,
                                 const double max_rms, double &avg_rms) {

  double cumulated_rms = 0;

  // Find four neighbours where phase is in one period(iterate through whole
  // mat)
  for (auto row_i = 0; row_i < absolute_phasemaps[0].rows; ++row_i) {

    for (auto column_i = 0; column_i < absolute_phasemaps[0].cols; ++column_i) {

      if ((absolute_phasemaps[0].at<float>(row_i, column_i) > 0) &&
          (absolute_phasemaps[1].at<float>(row_i, column_i) > 0)) {

        vector<Point2f> four_neighbours =
            choose_four_neighbouring_imagepoints(column_i, row_i);
        double rms_phase_hor = 0;
        double rms_phase_ver = 0;

        if (are_points_relative_phase_neighbours(absolute_phasemaps[0],
                                                 four_neighbours) &&
            are_points_relative_phase_neighbours(absolute_phasemaps[1],
                                                 four_neighbours)) {

          // Do paper calculations
          Point2d p0_horizontalphase, v0_horizontalphase, p0_verticalphase,
              v0_verticalphase, new_imagepoint, new_phasevalues;

          // Calculate average phase and intersect four neighbour plane with
          // average plane
          calculate_phase_intersection_lines(
              absolute_phasemaps[0], four_neighbours, p0_horizontalphase,
              v0_horizontalphase, rms_phase_hor);
          calculate_phase_intersection_lines(absolute_phasemaps[1],
                                             four_neighbours, p0_verticalphase,
                                             v0_verticalphase, rms_phase_ver);
          bool have_intersection = line_line_intersection(
              p0_horizontalphase, v0_horizontalphase, p0_verticalphase,
              v0_verticalphase, new_imagepoint);

          Point2f average_phasevalues(
              phase_average_from_neighbours(four_neighbours,
                                            absolute_phasemaps[0]),
              phase_average_from_neighbours(four_neighbours,
                                            absolute_phasemaps[1]));

          // If image point scoordinate smaller 0, kick it
          if (((new_imagepoint.x >= 0) && (new_imagepoint.y >= 0)) &&
              have_intersection && (rms_phase_hor < max_rms) &&
              (rms_phase_ver < max_rms)) {

            new_phasevalues.x = phase_average_from_neighbours(
                four_neighbours, absolute_phasemaps[0]);
            new_phasevalues.y = phase_average_from_neighbours(
                four_neighbours, absolute_phasemaps[1]);
            new_imagepoints.push_back(new_imagepoint);
            new_average_phasevalues.push_back(new_phasevalues);
            cumulated_rms += (rms_phase_hor + rms_phase_ver);
          }
        }
      }
    }
  }
  if ((new_imagepoints.size() == 0))
    avg_rms = 0;
  avg_rms = cumulated_rms / ((double)new_imagepoints.size() * 2);
}
