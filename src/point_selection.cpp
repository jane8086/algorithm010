#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

double
phase_average_from_neighbours(const vector<Point2f> &neighbourhood_points,
                              const Mat &phasemap) {

  double phase_sum = 0;

  for (const auto &point : neighbourhood_points) {
    phase_sum += phasemap.at<float>(point);
  }

  if (phase_sum == 0) {

    return 0;
  }

  return (phase_sum / neighbourhood_points.size());
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

bool line_line_intersection(Point2d o1, Point2d p1, Point2d o2, Point2d p2,
                            Point2d &r) {
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

void calculate_phase_intersection_lines(const Mat &phasemap,
                                        const vector<Point2f> &four_neighbours,
                                        Point2d &p0_2d, Point2d &vector_2d) {

  // Create Average Plane in Phase Direction
  double phase_average =
      phase_average_from_neighbours(four_neighbours, phasemap);

  // Create Equation System
  CvMat *res = cvCreateMat(3, 1, CV_32FC1);
  CvMat *matX = cvCreateMat(4, 3, CV_32FC1);
  CvMat *matZ = cvCreateMat(4, 1, CV_32FC1);

  // Matrix generation
  for (auto point_i = 0; point_i < four_neighbours.size(); ++point_i) {

    cvmSet(matX, point_i, 0, four_neighbours[point_i].x);
    cvmSet(matX, point_i, 1, four_neighbours[point_i].y);
    cvmSet(matX, point_i, 2, phasemap.at<double>(four_neighbours[point_i]));
    cvmSet(matZ, point_i, 0, 1);
  }

  // Solve equation
  cvSolve(matX, matZ, res, CV_SVD);
  double A = cvmGet(res, 0, 0);
  double B = cvmGet(res, 1, 0);
  double C = cvmGet(res, 2, 0);

  // Calculate Cross product with average plane
  Mat plane_a = (Mat_<double>(3, 1) << A, B, C);
  Mat plane_b = (Mat_<double>(3, 1) << 0, 0, 1);
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
}

bool points_are_relative_phase_neighbours(const Mat &relative_phasemap,
                                          vector<Point2f> neighbours) {

  double tolerance = 30;

  vector<double> phase_differences(4);
  phase_differences[0] = relative_phasemap.at<float>(neighbours[0]) -
                         relative_phasemap.at<float>(neighbours[1]);
  phase_differences[1] = relative_phasemap.at<float>(neighbours[0]) -
                         relative_phasemap.at<float>(neighbours[2]);
  phase_differences[2] = relative_phasemap.at<float>(neighbours[2]) -
                         relative_phasemap.at<float>(neighbours[3]);
  phase_differences[3] = relative_phasemap.at<float>(neighbours[1]) -
                         relative_phasemap.at<float>(neighbours[3]);

  for (int i = 0; i < 4; i++) {

    if (phase_differences[i] > tolerance)

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
                                 vector<Point2d> &new_average_phasevalues) {

  // Find four neighbours where phase is in one period(iterate through whole
  // mat)
  for (auto row_i = 500; row_i < absolute_phasemaps[0].rows; row_i += 2) {

    for (auto column_i = 500; column_i < absolute_phasemaps[0].cols;
         column_i += 2) {

      vector<Point2f> four_neighbours =
          choose_four_neighbouring_imagepoints(column_i, row_i);

      if (points_are_relative_phase_neighbours(absolute_phasemaps[0],
                                               four_neighbours)) {

        if (points_are_relative_phase_neighbours(absolute_phasemaps[1],
                                                 four_neighbours)) {

          // Do paper calculations
          Point2d p0_horizontalphase, v0_horizontalphase, p0_verticalphase,
              v0_verticalphase, new_imagepoint, new_phasevalues;

          // Calculate average phase and intersect four neighbour plane with
          // average plane
          calculate_phase_intersection_lines(
              absolute_phasemaps[0], four_neighbours, p0_horizontalphase,
              v0_horizontalphase);
          calculate_phase_intersection_lines(absolute_phasemaps[1],
                                             four_neighbours, p0_verticalphase,
                                             v0_verticalphase);
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
              have_intersection) {

            new_phasevalues.x = phase_average_from_neighbours(
                four_neighbours, absolute_phasemaps[0]);
            new_phasevalues.y = phase_average_from_neighbours(
                four_neighbours, absolute_phasemaps[1]);
            new_imagepoints.push_back(new_imagepoint);
            new_average_phasevalues.push_back(new_phasevalues);
          }
        }
      }
    }
  }
}
