#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"

int main(void)
{


    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    int monitor_height = 1080;
    int monitor_width = 1920;
    int periods = 3;
    create_patterns_all(monitor_width, monitor_height, periods, patterns, 0, patterns);

    //2. Capture Images
    FlyCapture2::Camera camera;
    vector<Mat> patterns_captured;
    camera_routine(camera, patterns, patterns_captured);
    save_images(patterns_captured);


    //3. Show and Capture Patterns


    //4. Unwrap Phase Maps


    //5. Create Point Correspondences


}

