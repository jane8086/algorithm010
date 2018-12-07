#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"
#include "include/phases.h"
#include "monitor.h"


int main(void)
{

    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    Monitor monitor(SAMSUNG_CURVED);
    int periods = 4;
    int amount_shifts = 3;
    create_patterns_all(monitor.size_x, monitor.size_y, periods, 0, patterns);

//    //3. Show and Capture Patterns
//    FlyCapture2::Camera camera;
//    vector<Mat> patterns_captured;
//    camera_routine(camera, patterns, patterns_captured);

    //4. Unwrap Phase Maps
    vector<Mat> patterns_absolut_phase;
    calculate_absolute_phasemaps(patterns_absolut_phase, amount_shifts, (int)patterns.size());





    //5. Create Point Correspondences
    vector<Point2f> image_points;
    vector<Point> points_world_pixel;
    vector<Point3f> points_world;
    calculate_realWorld_3d_coordinates(points_world, points_world_pixel, image_points, patterns_absolut_phase[0], patterns_absolut_phase[1],monitor, periods);
    saveDatayml(image_points, points_world_pixel, points_world);






    return 0;

}

