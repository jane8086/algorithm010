#include "flycapture/FlyCapture2.h"
#include "headers/camera.h"
#include "headers/patterns.h"

int main(void)
{

    //1. Connect and adjust camera
    FlyCapture2::Camera camera;
    FlyCapture2::CameraInfo caminfo;
    //camera_connect(camera, caminfo);
    //camera_adjust(camera);
    //camera_disconnect(camera);

    //2. Create Phase and Gray code patterns
    vector<Mat> patterns;
    int monitor_height = 1080;
    int monitor_width = 1920;
    int periods = 3
            ;
    create_patterns_all(monitor_width, monitor_height, periods, patterns, 0, patterns);


    /// Show created patterns
    namedWindow("Patterns", WINDOW_NORMAL);
    cvSetWindowProperty("Patterns", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    for (int i = 0; i<static_cast<int>(patterns.size()); i++){

        imshow("Patterns", patterns[i]);
        waitKey(500);
    }
    destroyAllWindows();







    //3. Show and Capture Patterns



    //4. Unwrap Phase Maps


    //5. Create Point Correspondences


}

