#include "flycapture/FlyCapture2.h"
#include "headers/camera.h"
#include "headers/patterns.h"
#include "headers/phases.h"

int main(void)
{

    //1. Connect and adjust camera
//    FlyCapture2::Camera camera;
//    FlyCapture2::CameraInfo caminfo;
//    camera_connect(camera, caminfo);
//    camera_adjust(camera);
//    camera_disconnect(camera);

    //2. Create Phase and Gray code patterns
    vector<Mat> patterns;
    int monitor_height = 1080;
    int monitor_width = 1920;
    int periods = 10;
    create_patterns_all(monitor_width, monitor_height, periods, patterns, 0, patterns);


    // Show created patterns
//    namedWindow("Patterns", WINDOW_NORMAL);
//    cvSetWindowProperty("Patterns", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

//    for (int i = 0; i<static_cast<int>(patterns.size()); i++){

//        imshow("Patterns", patterns[i]);
//        waitKey(500);
//    }
//    destroyAllWindows();







    //3. Show and Capture Patterns



    //4. Unwrap Phase Maps
    Mat im1,im2,im3;

    im1 = patterns[3];
    im2 = patterns[4];
    im3 = patterns[5];
    int row_size, col_size;
    row_size = im1.rows;
    col_size = im1.cols;
    Mat relative_phases(row_size, col_size, CV_8UC1);
    calculate_relative_phase(im1,im2,im3,relative_phases);
    imshow("phase map", relative_phases);
//    imshow("phase map",relative_phases);
    waitKey(0);



//    vector<Mat> relative_phases;
//    calculate_relative_phase(im1,im2,im3,relative_phases);

//    imshow("pattern",relative_phases[1]);
//    waitKeyEx(0);

//    namedWindow("Patterns", WINDOW_NORMAL);
//    cvSetWindowProperty("Patterns", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

//    for (int i = 0; i < static_cast<int>(relative_phases.size()); i++){

//        imshow("relative_phases", relative_phases[i]);
//        waitKey(0);
//    }
////    destroyAllWindows();


//    imwrite("pha_rel.png",relative_phases[1]);



    //5. Create Point Correspondences
    return 0;

}

