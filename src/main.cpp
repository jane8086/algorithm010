#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"
#include "include/phases.h"
#include "include/monitor.h"
#include "include/preprocessing.h"
#include <QDir>


int main(void)
{

//    QDir::setCurrent("/home/tae/TaeBuntu/PSA2018/phase_shifting");
    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    Monitor monitor(SAMSUNG_CURVED);
    int periods = 16;
    int amount_shifts = 3;
    int color_patterns = 0;
    int novel_method = 0;


    //Routine to create all phase_shifting patterns
    create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,amount_shifts);

// Update 18/12/2018 ---------------------------------------------- Testing camera gain adjustment --------------------------------------
//    2. Adjust gain of the camera
    FlyCapture2::Camera camera;
    Mat threshold_img;
    int threshold_value = 200; // color of testing image
    float brighter_percentage_threshold = 0; // percent of captured pixel color > threshold_value
    create_threshold_image(threshold_img,monitor, threshold_value);
    camera_gain_adjustment(camera,threshold_img,threshold_value,brighter_percentage_threshold);
// --------------------------------------------------------------------------------------------------------------------------------------


//    //3. Show and Capture Patterns
//    FlyCapture2::Camera camera;
//    vector<Mat> patterns_captured;
//    camera_routine(camera, patterns, patterns_captured);


    // detect screen
//    Mat screen;

//    //Calculate absolute phasemaps
//    vector<Mat> absolute_phasemaps;
//    calculate_absolute_phasemaps(absolute_phasemaps, screen, amount_shifts, patterns.size(), color_patterns, novel_method);


//    //5. Create Point Correspondences
//    vector<Point2f> image_points;
//    vector<Point> points_world_pixel;
//    vector<Point3f> points_world;
//    calculate_realWorld_3d_coordinates(points_world, points_world_pixel, image_points, absolute_phasemaps[0], absolute_phasemaps[1],monitor, periods,screen);
//    saveDatayml(image_points, points_world_pixel, points_world);






    return 0;

}

