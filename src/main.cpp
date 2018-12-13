#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"
#include "include/phases.h"
#include "monitor.h"
#include "include/preprocessing.h"
#include <QDir>


int main(void)
{


    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    Monitor monitor(SAMSUNG_CURVED);
    int periods = 4;
    int amount_shifts = 3;
    int color_patterns = 0;
    int novel_method = 0;

    //Routine to create all phase_shifting patterns
    create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns, color_patterns, novel_method);


//    //3. Show and Capture Patterns
//    FlyCapture2::Camera camera;
//    vector<Mat> patterns_captured;
//    camera_routine(camera, patterns, patterns_captured);


    // detect screen
    Mat screen = detect_screen(periods, amount_shifts, 10);


    //Calculate absolute phasemaps
    vector<Mat> absolute_phasemaps;
    calculate_absolute_phasemaps(absolute_phasemaps, amount_shifts, patterns.size(), color_patterns, novel_method);



    //5. Create Point Correspondences
    vector<Point2f> image_points;
    vector<Point> points_world_pixel;
    vector<Point3f> points_world;
    //calculate_realWorld_3d_coordinates(points_world, points_world_pixel, image_points, patterns_absolut_phase[0], patterns_absolut_phase[1],monitor, periods);
    saveDatayml(image_points, points_world_pixel, points_world);






    return 0;

}

