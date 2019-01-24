#include "flycapture/FlyCapture2.h"
#include "include/calibration.h"
#include "include/camera.h"
#include "include/lines_rectification.h"
#include "include/monitor.h"
#include "include/patterns.h"
#include "include/phases.h"
#include "include/point_correspondeces.hpp"
#include "include/preprocessing.h"
#include "include/tools.h"
#include "include/extract_zerophase_point.h"
#include "opencv2/opencv.hpp"
#include <QDir>

int main(void) {

  vector<Mat> patterns;
  Monitor monitor(SAMSUNG_CURVED);
  constexpr int periods = 16;
  constexpr int amount_shifts = 3;
  constexpr int color_patterns = 0;
  constexpr int novel_method = 0;

  // Routine to create all phase_shifting patterns
  create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,
                      amount_shifts);
    substract_offset_black(patterns.back(),patterns);
  //    //3. Show and Capture Patterns
  //    FlyCapture2::Camera camera;
  //    vector<Mat> patterns_captured;
  //    camera_routine(camera, patterns, patterns_captured);

  // detect screen
  Mat screen;
  Mat extract_point;
  // Calculate absolute phasemaps
//  vector<Mat> absolute_phasemaps;
  vector<Mat> relative_phasemaps;
  vector<Mat> period_number_mats;

  extract_zerophasemap(screen,extract_point,period_number_mats,amount_shifts,patterns.size(),color_patterns,novel_method);

//  calculate_all_phasemaps(absolute_phasemaps, relative_phasemaps, screen,
//                          amount_shifts, patterns.size(), color_patterns,
//                          novel_method);
  // calculate_absolute_phasemaps(absolute_phasemaps, screen, amount_shifts,
  // patterns.size(), color_patterns, novel_method);

  // 5. Calculate Point Correspondences
  vector<Point2f> image_points;
  vector<Point2f> points_display;

  calculate_display_coordinates(points_display,
      image_points,period_number_mats,monitor,periods,extract_point);

  // 6. Calculate Distortion parameters
  Point_Correspondences pc_input(image_points, points_display);
    double distCoeff = calculate_distortionParameter(pc_input, monitor);
      cout << endl << "Distortion coefficient: " << distCoeff << endl;
//  double distCoeff =  calculate_distortionParameter(pc_input, monitor);
  vector<Point2f> rectified_image_points(image_points.size());

  rectify_all_image_points(image_points, rectified_image_points, distCoeff);

  distCoeff = -8.7e-8;
  cout << "Distortion coefficient: " << distCoeff << endl;

  //7. Rectify Points
    rectify_all_image_points(image_points, rectified_image_points, distCoeff);
  Mat rec_im = Mat(extract_point.rows, extract_point.cols, CV_8U, Scalar(0));
  for (int i=0; i < rectified_image_points.size(); i ++)
  {
      int row = round(rectified_image_points[i].y);
      int col = round(rectified_image_points[i].x);
      rec_im.at<uchar>(row,col) = 1;
  }
  imshow("recim", rec_im*255);
  waitKey();
  //8. Choose only intersection Point_Correspondences

  //9. Calculate their Real world position
  vector<Point3f> points_world(image_points.size());

  calculate_realWorld_3d_coordinates(points_display, monitor, points_world);
//  saveDatayml(image_points, points_display, points_world);
  saveDatayml(rectified_image_points, points_display, points_world);

//  // 7. Calibration routine
  calibrationroutine(rectified_image_points, points_world,0.0);
//  calibrationroutine(image_points, points_world,0.0);
  return 0;
}


