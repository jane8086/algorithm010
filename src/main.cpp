#include "flycapture/FlyCapture2.h"
#include "include/calibration.h"
#include "include/camera.h"
#include "include/lines_rectification.h"
#include "include/monitor.h"
#include "include/patterns.h"
#include "include/phases.h"
#include "include/point_correspondeces.hpp"
#include "include/point_selection.h"
#include "include/preprocessing.h"
#include "include/tools.h"
#include "opencv2/opencv.hpp"
#include <QDir>

int main(void) {

  vector<Mat> patterns;
  Monitor monitor(SAMSUNG_CURVED);
  constexpr int periods = 4;
  constexpr int amount_shifts = 4;
  constexpr int color_patterns = 0;
  constexpr int novel_method = 0;

  // 1. Routine to create all phase_shifting patterns
  create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,
                      amount_shifts, color_patterns, novel_method);

  //    //3. Show and Capture Patterns
  //    FlyCapture2::Camera camera;
  //    vector<Mat> patterns_captured;
  //    camera_routine(camera, patterns, patterns_captured);

  // 2. detect screen
  Mat screen;

  // 3. Calculate absolute phasemaps
  vector<Mat> absolute_phasemaps;
  vector<Mat> relative_phasemaps;
  calculate_all_phasemaps(absolute_phasemaps, relative_phasemaps, screen,
                          amount_shifts, patterns.size(), color_patterns,
                          novel_method, periods);

  // 4. Choose points based on paper
  double max_error = 0.1;
  double min_max_error = 5e-6;
  double avg_error = 0;
  for (double interval = 5.0; max_error >= min_max_error;
       max_error = max_error / interval) {

    vector<Point2d> new_image_points;
    vector<Point2d> new_absolute_phasevalues;

    paper_phasemap_intersection(absolute_phasemaps, new_image_points,
                                new_absolute_phasevalues, max_error, avg_error);

    vector<Point2d> new_image_points_smooth(new_image_points.size());
    vector<Point2d> new_absolute_phasevalues_smoothed(
        new_absolute_phasevalues.size());
    if (new_image_points.size() == 0)
      break;
    saveDatayml(new_image_points, new_absolute_phasevalues,
                to_string(max_error));
    cout << "max_error = " << max_error << "  avg_error: " << avg_error << endl;
  }

  // 4. Calculate Point Correspondences
  // vector<Point2f> image_points;
  // vector<Point2f> points_display;
  //  calculate_display_coordinates(points_display,
  //      image_points, absolute_phasemaps[0], absolute_phasemaps[1], monitor,
  //      periods, screen);

  //  // Test gridpoint calculation
  //  double stepsize = 280;
  //  calculate_display_coordinates_on_relative_phasegrid(
  //      points_display, image_points, absolute_phasemaps[0],
  //      absolute_phasemaps[1], relative_phasemaps, monitor, screen, periods,
  //      stepsize);
  //  vector<Point3f> points_world(image_points.size());
  //  calculate_realWorld_3d_coordinates(points_display, monitor, points_world);
  //  saveDatayml(image_points, points_display, points_world);

  //  // 6. Calculate Distortion parameters
  //  Point_Correspondences pc_input(image_points, points_display);
  //  double distCoeff =  calculate_distortionParameter(pc_input, monitor);
  //  cout << distCoeff << endl;
  //  vector<Point2f> rectified_image_points(image_points.size());
  //  //7. Rectify Points
  //  rectify_all_image_points(image_points, rectified_image_points, distCoeff);

  //  //9. Calculate their Real world position
  //  vector<Point3f> points_world(image_points.size());
  //  calculate_realWorld_3d_coordinates(points_display, monitor, points_world);
  //  saveDatayml(rectified_image_points, points_display, points_world);

  // 7. Calibration routine
  //  calibrationroutine(image_points, points_world);

  return 0;
}
