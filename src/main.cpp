#include "flycapture/FlyCapture2.h"
#include "include/camera.h"
#include "include/patterns.h"
#include "include/tools.h"
#include "include/phases.h"
#include <QDir>


int main(void)
{
    QDir::setCurrent("/home/tae/phase_shifting");

    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    int monitor_height = 1080;
    int monitor_width = 1920;
    int periods = 4;
    int amount_shifts = 3;
    if(create_patterns_all(monitor_width, monitor_height, periods, 0, patterns))
        return -1;


//    //3. Show and Capture Patterns
//    FlyCapture2::Camera camera;
//    vector<Mat> patterns_captured;
//    camera_routine(camera, patterns, patterns_captured);


    //4. Unwrap Phase Maps
    vector<Mat> patterns_absolut_phase;
    calculate_absolute_phasemaps(patterns_absolut_phase, amount_shifts, (int)patterns.size());

    //5. Create Point Correspondences
    return 0;

}

