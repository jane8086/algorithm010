#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"
#include "include/phases.h"


int main(void)
{

    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    int monitor_height = 1080;
    int monitor_width = 1920;
    int periods = 4;
    int amount_shifts = 3;
    create_patterns_all(monitor_width, monitor_height, periods, patterns, 0, patterns);

    for(int i = 0; i <patterns.size(); i++){

        imshow("Patterns", patterns[i]);
        waitKey();
    }


    //3. Show and Capture Patterns
    //FlyCapture2::Camera camera;
    //vector<Mat> patterns_captured;
    //camera_routine(camera, patterns, patterns_captured);


    //4. Unwrap Phase Maps
    vector<Mat> patterns_absolut_phase;
    calculate_absolute_phasemaps(patterns_absolut_phase, amount_shifts, (int)patterns.size());

    //5. Create Point Correspondences
    return 0;

}

