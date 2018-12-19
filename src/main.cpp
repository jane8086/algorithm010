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


    //1. Create Phase and Gray code patterns
    vector<Mat> patterns;
    Monitor monitor(SAMSUNG_CURVED);
    int periods = 4;
    int amount_shifts = 3;
    int color_patterns = 0;
    int novel_method = 0;

    //Routine to create all phase_shifting patterns
    create_patterns_all(monitor.size_x, monitor.size_y, periods, patterns,amount_shifts);

//    //3. Show and Capture Patterns
//    FlyCapture2::Camera camera;
//    vector<Mat> patterns_captured;
//    camera_routine(camera, patterns, patterns_captured);

    //4. Unwrap Phase Maps
    //vector<Mat> patterns_absolut_phase;
    //calculate_absolute_phasemaps(patterns_absolut_phase, amount_shifts, (int)patterns.size());

    /////////////////////////////////////////////////////////////////////////////////////////////  
    // test from chao zhang: get period map using novel method
    Mat period_novel;
    vector<Mat> novel_patterns;
    novel_patterns.push_back(patterns[12].clone());
    novel_patterns.push_back(patterns[13].clone());
    novel_patterns.push_back(patterns[14].clone());
    //novel_patterns.push_back(patterns[21].clone());
    //novel_patterns.push_back(patterns[22].clone());

    imshow("patterns1",novel_patterns[0]);
    waitKey();
    imshow("patterns2",novel_patterns[1]);
    waitKey();
    imshow("patterns3",novel_patterns[2]);
    waitKey();

    Mat relative_phase;
    relative_phase = calculate_relative_phase(patterns);
    period_novel = calculate_relative_phase(novel_patterns);
    //imshow("period map",period_novel);
    //waitKey();

    Mat period_map;
    Mat absolute_phase_map;
    absolute_phase_map = calculate_absolute_phase_novel(relative_phase, period_novel, periods);

    /*
    double interval;
    interval = 90.0;
    Mat period_map(1080, 1920, CV_32FC1);
    for (int row = 0; row < 1080; row++)
    {
        for (int col = 0; col < 1920; col++)
        {
            period_map.at<float>(row,col) = (double)((int)(period_novel.at<float>(row,col)/interval+0.5)); // calculate the period number
        }
    }

    Mat absolute_phase_map;
    absolute_phase_map = calculate_absolute_phase(relative_phase, period_map);

    int row_size, col_size;
    row_size = period_novel.rows;
    col_size = period_novel.cols;
    */
    for (int row = 0; row < 1080; row++ ){
        for (int col = 0; col < 1920; col++)
        {
            if((col*16) % ((int)monitor.size_x) ==0){
                cout<<absolute_phase_map.at<float>(row,col)<<" ";
            }
        }
        cout<<endl;
    }
    // test end
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // detect screen
    Mat screen;

    //Calculate absolute phasemaps
    vector<Mat> absolute_phasemaps;
    calculate_absolute_phasemaps(absolute_phasemaps, screen, amount_shifts, patterns.size(), color_patterns, novel_method);


    //5. Create Point Correspondences
    vector<Point2f> image_points;
    vector<Point> points_world_pixel;
    vector<Point3f> points_world;

    calculate_realWorld_3d_coordinates(points_world, points_world_pixel, image_points, absolute_phasemaps[0], absolute_phasemaps[1],monitor, periods,screen);
    saveDatayml(image_points, points_world_pixel, points_world);

    return 0;

}

