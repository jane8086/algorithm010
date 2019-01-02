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
#include "opencv2/opencv.hpp"
#include <QDir>

int main(void) {
  vector<Mat> patterns;
  Monitor monitor(SAMSUNG_CURVED);
  constexpr int periods = 64;
  constexpr int amount_shifts = 3;
  constexpr int color_patterns = 0;
  constexpr int novel_method = 0;

  // Routine to create all phase_shifting patterns
  create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,
                      amount_shifts);

  //    //3. Show and Capture Patterns
  //    FlyCapture2::Camera camera;
  //    vector<Mat> patterns_captured;
  //    camera_routine(camera, patterns, patterns_captured);

  // detect screen
  Mat screen;

  // Calculate absolute phasemaps
  vector<Mat> absolute_phasemaps;
  vector<Mat> relative_phasemaps;
  calculate_all_phasemaps(absolute_phasemaps, relative_phasemaps, screen,
                          amount_shifts, patterns.size(), color_patterns,
                          novel_method);
  // calculate_absolute_phasemaps(absolute_phasemaps, screen, amount_shifts,
  // patterns.size(), color_patterns, novel_method);

  // 5. Calculate Point Correspondences
  vector<Point2f> image_points;
  vector<Point2f> points_display;
  calculate_display_coordinates(points_display,
      image_points, absolute_phasemaps[0], absolute_phasemaps[1], monitor, periods, screen);

  // 6. Calculate Distortion parameters
  Point_Correspondences pc_input(image_points, points_display);
  double distCoeff =  calculate_distortionParameter(pc_input, monitor);
  cout << distCoeff << endl;
  vector<Point2f> rectified_image_points(image_points.size());
  //7. Rectify Points
  rectify_all_image_points(image_points, rectified_image_points, distCoeff);
  //8. Choose only intersection Point_Correspondences

  //9. Calculate their Real world position
  vector<Point3f> points_world(image_points.size());
  calculate_realWorld_3d_coordinates(points_display, monitor, points_world);


  // 7. Calibration routine
  calibrationroutine(rectified_image_points, points_world);

  return 0;
}
