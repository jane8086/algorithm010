#include "include/monitor.h"
#include "include/preprocessing.h"
#include "include/tools.h"
#include "opencv2/opencv.hpp"
#include <math.h>
#include <stdio.h>

using namespace std;
using namespace cv;

#define pi 3.1415926

/* function: novel2period, CV_32FC1  !!!!!!!!ababdoned
 * input: Mat novel, relative phase of novel that store period information.
 *        int period_num, number of periods
 *  output: Mat file, that store period number of every pixel.
 *
Mat novel2period(Mat &novel, int period_num){
    double interval;
    interval = 360.0/(double)period_num;
    int row_size, col_size;
    row_size = novel.rows;
    col_size = novel.cols;
    Mat period(row_size, col_size, CV_32FC1);
    for (int row = 0; row < row_size; row++)
    {
        for (int col = 0; col < col_size; col++ )
        {
            period.at<float>(row,col) =
(double)((int)(novel.at<float>(row,col)/interval+0.5)); // calculate the period
number
        }
    }

}
*/

Point3d transform_to_3D_point(const Point2d &display_pixel,
                              const Monitor &monitor) {

  // Transform pixel into real world point with coordinate system in middle of
  // screen
  double x_mm = display_pixel.x * monitor.pixelsize_x -
                0.5 * monitor.size_x * monitor.pixelsize_x;
  double y_mm = display_pixel.y * monitor.pixelsize_y -
                0.5 * monitor.size_y * monitor.pixelsize_y;

  // calculate new x_curve and z_curve
  double alpha = (x_mm / monitor.radiusofCurvature);
  double x_mm_curved = (sin(alpha) * monitor.radiusofCurvature);
  double z_mm_curved =
      cos(alpha) * monitor.radiusofCurvature - monitor.radiusofCurvature;
  Point3d display_pixel_curved_mm(x_mm_curved, y_mm, z_mm_curved);
  return display_pixel_curved_mm;
}

/*
 * function: calculate_relative_phase_general
 * input: im1: Mat file of the first phase
 *        im2: Mat file of the second phase
 *        im3: Mat file of the third phase
 *        &relative_phase: address of the vector of mats
 * output:vector of mats
 */
Mat calculate_relative_phase_general(vector<Mat> &patterns) {
  // Here we assume that we are showing shifted patterns
  Mat phasemap_relative(patterns[0].rows, patterns[0].cols, CV_32FC1);

  // calculate image number
  int N = patterns.size();
  double intensity_sum_sin, intensity_sum_cos, relative_phase;

  // get dimension of the image
  int row_size, col_size;
  row_size = patterns[0].rows;
  col_size = patterns[0].cols;

  int period_quarter = 90;

  for (int row = 0; row < row_size; row++) {
    for (int col = 0; col < col_size; col++) {
      intensity_sum_sin = 0;
      intensity_sum_cos = 0;
      for (int n = 1; n < N + 1; n++) {
        intensity_sum_sin += (double)patterns[n - 1].at<uchar>(row, col) *
                             sin(2 * CV_PI * (n) / (double)N);
        intensity_sum_cos += (double)patterns[n - 1].at<uchar>(row, col) *
                             cos(2 * CV_PI * (n) / (double)N);
      }

      relative_phase = atan(intensity_sum_sin / intensity_sum_cos);

      if (col == 0 && row == 0) {
        cout << patterns[0].at<uchar>(row, col) -
                    patterns[2].at<uchar>(row, col)
             << endl;
        cout << intensity_sum_sin << " " << intensity_sum_cos << " "
             << relative_phase << " ";
      }

      relative_phase = relative_phase * 2 * period_quarter / CV_PI;
      if ((intensity_sum_cos < 0)) // represent the sign of cos value
      {
        relative_phase += 2 * period_quarter; // range of angle: -90 ~ 270 grad
      }
      if (relative_phase < 0) // range of angle: 0~360 grad
      {
        relative_phase += 4 * period_quarter;
      }
      if (relative_phase > 359.5) {
        relative_phase = 0;
      }

      phasemap_relative.at<float>(row, col) = relative_phase;
    }
    cout << endl;
  }
  return phasemap_relative;
}

/*
 * function: calculate_relative_phase
 * input: im1: Mat file of the first phase
 *        im2: Mat file of the second phase
 *        im3: Mat file of the third phase
 *        &relative_phase: address of the vector of mats
 * output:vector of mats
 */
Mat calculate_relative_phase(vector<Mat> &patterns) {

  // Here we assume that we are showing shifted patterns
  Mat phasemap_relative(patterns[0].rows, patterns[0].cols, CV_32FC1);

  // get dimension of the image
  int row_size, col_size;
  row_size = patterns[0].rows;
  col_size = patterns[0].cols;

  int period_quarter = 90;
  for (int col = 0; col < col_size; col++) {
    for (int row = 0; row < row_size; row++) {

      double intensity_1, intensity_2, intensity_3;
      float relative_phase;

      intensity_1 = static_cast<double>(patterns[0].at<uchar>(row, col));
      intensity_2 = static_cast<double>(patterns[1].at<uchar>(row, col));
      intensity_3 = static_cast<double>(patterns[2].at<uchar>(row, col));

      relative_phase = atan(sqrt(3.0) * (intensity_1 - intensity_3) /
                            (2 * intensity_2 - intensity_1 - intensity_3));
      relative_phase = relative_phase * 2 * period_quarter / CV_PI;
      if ((2 * intensity_2 - intensity_1 - intensity_3) <
          0) // represent the sign of cos value
      {
        relative_phase += 2 * period_quarter; // range of angle: -90 ~ 270 grad
      }
      if (relative_phase < 0) // range of angle: 0~360 grad
      {
        relative_phase += 4 * period_quarter;
      }
      if (relative_phase > 359.5) {
        relative_phase = 0;
      }
      phasemap_relative.at<float>(row, col) = relative_phase;
    }
  }
  return phasemap_relative;
}

/*
 * function: calculate_absolute_phase_novel
 * input: relative_phase: Mat file of relative phase
 *        period_number: Mat file of period number
 *        range: range of a period, e.g. 360 (grad)
 *        &absolute_phase: address of the vector of mats
 * output: vector of mats
 */
Mat calculate_absolute_phase_novel(Mat &relative_phase, Mat &novel,
                                   int period_sum) {
  int row_num, col_num;
  row_num = relative_phase.rows;
  col_num = relative_phase.cols;
  Mat phase_abs(row_num, col_num, CV_32FC1);
  int range = 360;
  double interval = 360.0 / (double)period_sum;

  for (int row = 0; row < row_num; row++) {
    for (int col = 0; col < col_num; col++) {
      double period = (double)((int)(novel.at<float>(row, col) / interval +
                                     0.5)); // calculate the period number
      float absolute_period =
          relative_phase.at<float>(row, col) + period * range;
      phase_abs.at<float>(row, col) = absolute_period;
    }
  }
  return phase_abs;
}

/*
 * function: calculate_absolute_phase
 * input: relative_phase: Mat file of relative phase
 *        period_number: Mat file of period number
 *        range: range of a period, e.g. 360 (grad)
 *        &absolute_phase: address of the vector of mats
 * output: vector of mats
 */
Mat calculate_absolute_phase(Mat &relative_phase, Mat &period_number) {
  int row_num, col_num;
  row_num = relative_phase.rows;
  col_num = relative_phase.cols;
  Mat phase_abs(row_num, col_num, CV_32FC1);
  int range = 360;

  for (int row = 0; row < row_num; row++) {
    for (int col = 0; col < col_num; col++) {
      float period = period_number.at<uchar>(row, col);
      float relative_value = relative_phase.at<float>(row, col);
      float absolute_period = relative_value + period * range;
      phase_abs.at<float>(row, col) = absolute_period;
    }
  }
  return phase_abs;
}

Mat calculate_period_Mat_graycode(vector<Mat> &graycodeimages) {

  // Here we assume that we are showing shifted patterns
  Mat period_Mat(graycodeimages[0].rows, graycodeimages[0].cols, CV_8U);
  int amount_images = static_cast<int>(graycodeimages.size());

  // We also assume that this ufnction gets a vector of binary images
  int gray_value[graycodeimages.size()];

  for (int col_i = 0; col_i < graycodeimages[0].cols; col_i++) {

    for (int row_i = 0; row_i < graycodeimages[0].rows; row_i++) {

      // Get binary value
      gray_value[0] =
          graycodeimages[0].at<uchar>(row_i, col_i); // Get first value

      for (int image_i = 1; image_i < amount_images; image_i++) {

        gray_value[image_i] = gray_value[image_i - 1] ^
                              graycodeimages[image_i].at<uchar>(row_i, col_i);
      }

      // Convert binay to integer
      int period_number = 0;

      for (int j = 0; j < amount_images; j++) {

        period_number += (gray_value[j]) * pow(2, (amount_images - j - 1));
      }

      // Assign value to Mat
      period_Mat.at<uchar>(row_i, col_i) = period_number;
    }
  }

  return period_Mat;
}

int calculate_periodnumber_graycode(vector<Mat> &period_number_Mats,
                                    int &amount_phaseshifts,
                                    int &amount_patterns) {

  int periods = pow(2, (amount_patterns - 2 * amount_phaseshifts - 2) / 2);

  // Calculate absolute phasemaps
  vector<Mat> patterns_graycode_captured;
  load_images_gray(patterns_graycode_captured, amount_phaseshifts,
                   amount_patterns);

  // Do some preporocseeing here:
  convert_binary(patterns_graycode_captured);

  // create subvector graycode patterns
  vector<Mat>::const_iterator first_gray = patterns_graycode_captured.begin();
  vector<Mat>::const_iterator last_gray = patterns_graycode_captured.end();

  vector<Mat> gray_patterns_vertical(
      first_gray,
      first_gray + log2(periods)); // ststic for period and amount of shifts
  vector<Mat> gray_patterns_horizontal(
      first_gray + log2(periods),
      last_gray); // static for period and amount of shifts

  // Calculate period number horizontal and vertical
  Mat periodnumber_horizontal =
      calculate_period_Mat_graycode(gray_patterns_vertical);
  Mat periodnumber_vertical =
      calculate_period_Mat_graycode(gray_patterns_horizontal);

  period_number_Mats.push_back(periodnumber_horizontal);
  period_number_Mats.push_back(periodnumber_vertical);

  return 0;
}

int calculate_all_phasemaps(vector<Mat> &absolute_phasemaps,
                            vector<Mat> &relative_phasemaps, Mat &screen,
                            int amount_phaseshifts, int amount_patterns,
                            int color_patterns, int novel_method) {

  // Load phase images from folder
  vector<Mat> patterns_phase_captured;
  load_images_phase(patterns_phase_captured, amount_phaseshifts,
                    color_patterns);

  // reduce moire effect by using bilateral filter
  // vector<Mat> patterns_phase_filtered;
  // reduce_moire(patterns_phase_captured, patterns_phase_filtered, 10);

  // Detect the screen and throw out all the other points
  screen = detect_screen(amount_patterns, amount_phaseshifts, 10);

  /*
      if(amount_phaseshifts != 3){
          cout <<"Can't calculate relative phase yet! " << endl;
          return -1;
      }
  */

  // create subvector phase shift patterns
  vector<Mat>::const_iterator first = patterns_phase_captured.begin();
  vector<Mat>::const_iterator last = patterns_phase_captured.end();
  vector<Mat> phase_patterns_vertical(first, first + amount_phaseshifts);
  vector<Mat> phase_patterns_horizontal(first + amount_phaseshifts, last);

  // Calculate both relative phasemaps
  Mat relative_phasemap_horizontal;
  Mat relative_phasemap_vertical;

  if (color_patterns) {
    // Calculate relative_phase based on color patterns here....
  } else {

    relative_phasemap_vertical =
        calculate_relative_phase(phase_patterns_vertical);
    relative_phasemap_horizontal =
        calculate_relative_phase(phase_patterns_horizontal);

    // Just look at ROI of screen
    relative_phasemap_vertical = relative_phasemap_vertical.mul(screen);
    relative_phasemap_horizontal = relative_phasemap_horizontal.mul(screen);
  }

  // Calculate Period Number Mats
  vector<Mat> period_number_mats;

  if (novel_method) {

    // Calculate the period number here
  } else {

    calculate_periodnumber_graycode(period_number_mats, amount_phaseshifts,
                                    amount_patterns);
  }

  Mat absolutephase_vertical = calculate_absolute_phase(
      relative_phasemap_vertical, period_number_mats[1]);
  Mat absolutephase_horizontal = calculate_absolute_phase(
      relative_phasemap_horizontal, period_number_mats[0]);

  absolute_phasemaps.push_back(absolutephase_horizontal);
  absolute_phasemaps.push_back(absolutephase_vertical);
  relative_phasemaps.push_back(relative_phasemap_horizontal);
  relative_phasemaps.push_back(relative_phasemap_vertical);

  return 0;
}

int calculate_absolute_phasemaps(vector<Mat> &absolute_phasemaps,
                                 int amount_phaseshifts, int amount_patterns,
                                 int color_patterns, int novel_method) {

  // Load phase images from folder
  vector<Mat> patterns_phase_captured;
  load_images_phase(patterns_phase_captured, amount_phaseshifts,
                    color_patterns);

  // reduce moire effect by using bilateral filter
  vector<Mat> patterns_phase_filtered;
  reduce_moire(patterns_phase_captured, patterns_phase_filtered, 10);

  /*
      if(amount_phaseshifts != 3){
          cout <<"Can't calculate relative phase yet! " << endl;
          return -1;
      }
  */

  // create subvector phase shift patterns
  vector<Mat>::const_iterator first = patterns_phase_filtered.begin();
  vector<Mat>::const_iterator last = patterns_phase_filtered.end();
  vector<Mat> phase_patterns_vertical(first, first + amount_phaseshifts);
  vector<Mat> phase_patterns_horizontal(first + amount_phaseshifts, last);

  // Calculate both relative phasemaps
  Mat relative_phasemap_horizontal;
  Mat relative_phasemap_vertical;

  if (color_patterns) {
    // Calculate relative_phase based on color patterns here....
  } else {

    relative_phasemap_vertical =
        calculate_relative_phase(phase_patterns_vertical);
    relative_phasemap_horizontal =
        calculate_relative_phase(phase_patterns_horizontal);
  }

  // Calculate Period Number Mats
  vector<Mat> period_number_mats;

  if (novel_method) {

    // Calculate the period number here
  } else {

    calculate_periodnumber_graycode(period_number_mats, amount_phaseshifts,
                                    amount_patterns);
  }

  Mat absolutephase_vertical = calculate_absolute_phase(
      relative_phasemap_vertical, period_number_mats[1]);
  Mat absolutephase_horizontal = calculate_absolute_phase(
      relative_phasemap_horizontal, period_number_mats[0]);

  absolute_phasemaps.push_back(absolutephase_horizontal);
  absolute_phasemaps.push_back(absolutephase_vertical);

  return 0;
}

void calculate_realWorld_3d_coordinates(const vector<Point2d> &display_points,
                                        const Monitor &monitor,
                                        vector<Point3d> &points_world_mm) {

  for (unsigned long point_i = 0; point_i < display_points.size(); ++point_i) {

    points_world_mm[point_i] =
        transform_to_3D_point(display_points[point_i], monitor);
  }
}

bool same_relative_phasevalues(
    const vector<Mat> &relative_phasemaps, const Point2d &point,
    const double phase_tolerance_horizontal_vertical) {

  double phase_deviation_horizontal_vertical =
      abs(relative_phasemaps[0].at<float>(point) -
          relative_phasemaps[1].at<float>(point));

  if (phase_deviation_horizontal_vertical <=
      phase_tolerance_horizontal_vertical) {

    return true;
  } else {
    return false;
  }
}

bool lies_on_phasegrid(const vector<Mat> &relative_phasemaps,
                       const Point2f &point, const double phase_stepszise,
                       Monitor &monitor, int periods) {

  double horizontal_phaseresolution_display =
      360.0 / (monitor.size_x / periods);

  double horizontal_phase_tolerance = 1;

  for (auto horizontal_phase_i = 50; (horizontal_phase_i / 360) <= 1;
       horizontal_phase_i += phase_stepszise) {

    double horizontal_phase_deviation =
        abs(relative_phasemaps[1].at<float>(point) - horizontal_phase_i);
    if (horizontal_phase_deviation <= horizontal_phase_tolerance) {

      double phase_tolerance_horizontal_vertical = 5;
      return same_relative_phasevalues(relative_phasemaps, point,
                                       phase_tolerance_horizontal_vertical);
    }
  }
  return false;
}

//  Calculate 360/phase intervall =
// Check if phase value is one of those calculated phases
// Check if points lie on the same relative phase

void calculate_display_coordinates_on_relative_phasegrid(
    vector<Point2f> &points_display, vector<Point2f> &points_image,
    Mat &absolutephasemap_hor, Mat &absolutephasemap_ver,
    const vector<Mat> &relative_phasemaps, Monitor &monitor, Mat &screen,
    int periods, const double phase_stepsize) {

  // Iterate through every point in Mat
  for (int row_i = 0; row_i < absolutephasemap_hor.rows; row_i++) {

    for (int column_i = 0; column_i < absolutephasemap_hor.cols; column_i++) {

      if (screen.at<uchar>(row_i, column_i) != 0) {

        // Current pointr in image
        Point2f imagepoint_i(column_i, row_i);

        if (lies_on_phasegrid(relative_phasemaps, imagepoint_i, phase_stepsize,
                              monitor, periods)) {

          // Calculate phases into pixel coorindates
          Point2f display_pixel;
          display_pixel.x =
              absolutephasemap_ver.at<float>(imagepoint_i) *
              ((float)monitor.size_x / (2 * (float)periods * 180));
          display_pixel.y =
              absolutephasemap_hor.at<float>(imagepoint_i) *
              ((float)monitor.size_y / (2 * (float)periods * 180));

          // When x or y are zero kick these pixels
          if ((display_pixel.x != 0) || (display_pixel.y != 0)) {

            // Pushback pixel position
            points_display.push_back(display_pixel);
            points_image.push_back(imagepoint_i);
          }
        }
      }
    }
  }
}

void calculate_display_coordinates(const vector<Point2d> &points_image,
                                   const vector<Point2d> &phasemaps,
                                   vector<Point2d> &points_image_wrong,
                                   vector<Point2d> &points_display,
                                   Monitor &monitor, int periods) {

  // Iterate through every point in Mat
  for (unsigned long imagepoint_i = 0; imagepoint_i < points_image.size();
       ++imagepoint_i) {

    // Calculate phases into pixel coorindates
    Point2d display_pixel;
    display_pixel.x = phasemaps[imagepoint_i].x *
                      ((double)monitor.size_x / (2 * (double)periods * 180));
    display_pixel.y = phasemaps[imagepoint_i].y *
                      ((double)monitor.size_y / (2 * (double)periods * 180));

    // When x or y are zero kick these pixels
    if ((display_pixel.x < 0) || (display_pixel.y < 0) ||
        display_pixel.x > monitor.size_x || display_pixel.y > monitor.size_y) {

      points_image_wrong.push_back(phasemaps[imagepoint_i]);
    }

    // Pushback pixel position
    points_display.push_back(display_pixel);
  }
}

void calculate_display_coordinates(vector<Point2f> &points_display,
                                   vector<Point2f> &points_image,
                                   Mat &absolutephasemap_hor,
                                   Mat &absolutephasemap_ver, Monitor &monitor,
                                   int periods, Mat &screen) {

  // Iterate through every point in Mat
  for (int row_i = 0; row_i < absolutephasemap_hor.rows; row_i++) {

    for (int column_i = 0; column_i < absolutephasemap_hor.cols; column_i++) {

      if (screen.at<uchar>(row_i, column_i) != 0) {

        // Current point in image
        Point2f imagepoint_i(column_i, row_i);

        // Calculate phases into pixel coorindates
        Point2f display_pixel;
        display_pixel.x = absolutephasemap_ver.at<float>(imagepoint_i) *
                          ((float)monitor.size_x / (2 * (float)periods * 180));
        display_pixel.y = absolutephasemap_hor.at<float>(imagepoint_i) *
                          ((float)monitor.size_y / (2 * (float)periods * 180));

        // When x or y are zero kick these pixels
        if ((display_pixel.x != 0) || (display_pixel.y != 0)) {

          // Pushback pixel position
          points_display.push_back(display_pixel);
          points_image.push_back(imagepoint_i);
        }
      }
    }
  }
}
