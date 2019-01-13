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
#include <unistd.h> //test if folder exist

int main(void) {

  vector<Mat> patterns;
  Monitor monitor(SAMSUNG_CURVED);
  constexpr int periods = 64;
  constexpr int amount_shifts = 3;
  constexpr int color_patterns = 0;
  constexpr int novel_method = 0;
  constexpr int captured_times = 5;

  //1. create all phase_shifting patterns only one time
    string dir = "images";
    if(access(dir.c_str(),0)==0)  //if the patterns are already existed, then get them from lookuotable directly
    {
        patterns_lookuptable(patterns);
    }else{                       //if the patterns are not created yet, then create them
        create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,amount_shifts);
        save_images(patterns);


    }



  //    //3. Show and Capture Patterns
      FlyCapture2::Camera camera;
      vector<Mat> patterns_captured;
      vector<Mat> average_images;
      camera_routine(camera, patterns, patterns_captured,captured_times);

      average_captureimages(patterns_captured,captured_times, average_images);

  // 2. detect screen
  Mat screen;

  // 3. Calculate absolute phasemaps
  vector<Mat> absolute_phasemaps;
  vector<Mat> relative_phasemaps;
  calculate_all_phasemaps(absolute_phasemaps, relative_phasemaps, screen,
                          amount_shifts, patterns.size(), color_patterns,
                          novel_method);

  // 4. Choose points based on paper
  vector<Point2d> new_image_points;
  vector<Point2d> new_absoulte_phasevalues;
  paper_phasemap_intersection(absolute_phasemaps, new_image_points,
                              new_absoulte_phasevalues);
  saveDatayml(new_image_points, new_absoulte_phasevalues);
  imshow("phasmap_hor", absolute_phasemaps[0] / (periods * 360.0));
  imshow("phasemap_ver", absolute_phasemaps[1] / (periods * 360.0));
  waitKey();
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
