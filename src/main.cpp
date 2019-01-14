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
  constexpr int periods = 16;
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

  imshow("rela", relative_phasemaps[1]/360);
  waitKey();
  imshow("absolute", absolute_phasemaps[1]/(360*periods));
  waitKey();

  // 4. Choose points based on paper
  double max_error = 0.1;
  double min_max_error = 0.1;
  double avg_error = 0;
  vector<Point2d> new_image_points;
  vector<Point2d> absolute_phasemap_values;
  for (double interval = 5.0; max_error >= min_max_error;
       max_error = max_error / interval) {

    vector<Point2d> new_image_points_calculate;
    vector<Point2d> new_absolute_phasevalues_calculate;

    paper_phasemap_intersection(absolute_phasemaps, new_image_points_calculate,
                                new_absolute_phasevalues_calculate, max_error,
                                avg_error);
    new_image_points = new_image_points_calculate;
    absolute_phasemap_values = new_image_points_calculate;

    if (new_image_points_calculate.size() == 0)
      break;
    saveDatayml(new_image_points_calculate, new_absolute_phasevalues_calculate,
                to_string(max_error));
  }

  // 5. Calculate Display points
  vector<Point2d> wrong_image_points;
  vector<Point2d> points_display;
  calculate_display_coordinates(new_image_points, absolute_phasemap_values,
                                wrong_image_points, points_display, monitor,
                                periods);
  // 7. Calculate Distortion parameters
  Point_Correspondences pc_input(new_image_points, points_display);
  double distCoeff = calculate_distortionParameter(pc_input, monitor);
  cout << distCoeff << endl;

  // 8. Rectify Points
  //vector<Point2d> rectified_image_points(new_image_points.size());
  //rectify_all_image_points(new_image_points, rectified_image_points, distCoeff);

  // 6. Calculate their Real world position
  vector<Point3d> points_world(new_image_points.size());
  calculate_realWorld_3d_coordinates(points_display, monitor, points_world);

  // 7. Convert to Point3f and Point2f so we can calbrate with it
  vector<Point3f> calib_worldpoints(points_world.size());
  vector<Point2f> calib_imagepoints(points_world.size());
  convert_to_floatpoints(points_world, new_image_points, calib_worldpoints, calib_imagepoints);

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
  double repo_error = 0.0;
  calibrationroutine(calib_imagepoints, calib_worldpoints, repo_error);

  // Save results
  save_results(periods, amount_shifts, color_patterns, novel_method, avg_error,
               max_error * 5, repo_error);
  return 0;
}
