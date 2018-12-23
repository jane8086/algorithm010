#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"
#include "include/phases.h"
#include "include/monitor.h"
#include "include/preprocessing.h"
#include "include/calibration.h"
#include <QDir>
#include "opencv2/opencv.hpp"

// CLANG FORMAT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
int main(void)
{
    vector<Mat> patterns;
    Monitor monitor(SAMSUNG_CURVED);
    constexpr int periods = 64;
    constexpr int amount_shifts = 3;
    constexpr int color_patterns = 0;
    constexpr int novel_method = 0;

    //Routine to create all phase_shifting patterns
    create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,amount_shifts);

//    //3. Show and Capture Patterns
//    FlyCapture2::Camera camera;
//    vector<Mat> patterns_captured;
//    camera_routine(camera, patterns, patterns_captured);





    // detect screen
    Mat screen;

    //Calculate absolute phasemaps
    vector<Mat> absolute_phasemaps;
    vector<Mat> relative_phasemaps;
    calculate_all_phasemaps(absolute_phasemaps, relative_phasemaps,screen, amount_shifts, patterns.size(), color_patterns, novel_method);
    //calculate_absolute_phasemaps(absolute_phasemaps, screen, amount_shifts, patterns.size(), color_patterns, novel_method);


    //5. Create Point Correspondences
    vector<Point2f> image_points;
    vector<Point> points_world_pixel;
    vector<Point3f> points_world;
    //Calculate only points where relative phase equals other relative phase
    imshow("vertival_relative", relative_phasemaps[0]/360);
    imshow("hotizontal_relative",relative_phasemaps[1]/360);
    waitKey();

    calculate_realWorld_3d_coordinates(points_world, points_world_pixel, image_points, absolute_phasemaps[0], absolute_phasemaps[1],relative_phasemaps[0],relative_phasemaps[1],monitor, periods,screen);
    saveDatayml(image_points, points_world_pixel, points_world);

    //6. Calibration routine
    calibrationroutine(image_points, points_world);



    return 0;

}

