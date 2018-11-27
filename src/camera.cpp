#include "flycapture/FlyCapture2.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include "include/camera.h"



using namespace FlyCapture2;
using namespace std;
using namespace cv;


int camera_adjust(Camera &camera){

    Property prop;
    prop.type = BRIGHTNESS;
    prop.onOff = true;
    prop.autoManualMode = false;
    Property prop_g;
    prop_g.type = GAIN;
    prop_g.autoManualMode = false;
    FlyCapture2::Error error1 = camera.SetProperty(&prop);
    FlyCapture2::Error error2 = camera.SetProperty(&prop_g);
    return 0;

}


int camera_connect(Camera &camera, CameraInfo &caminfo){

    FlyCapture2::Error error;
    error = camera.Connect(0);
    if (error != PGRERROR_OK) {

        cout << "Could not connect to  camera" << endl;
        return false;
    }

    // Get the camera info and print it out
    error = camera.GetCameraInfo(&caminfo);
    if (error != PGRERROR_OK) {
        cout << "Failed to get camera info from camera" << std::endl;
        return false;
    }

    //std::cout << camInfo.sensorResolution << " " << camInfo.modelName << " "
    //          << camInfo.serialNumber << std::endl;

    error = camera.StartCapture();

    if (error == PGRERROR_ISOCH_BANDWIDTH_EXCEEDED) {

        std::cout << "Bandwidth exceeded" << std::endl;
        return false;
    } else if (error != PGRERROR_OK) {

        std::cout << "Failed to start image capture" << std::endl;
        return false;
    }

    return true;
}


int camera_disconnect(Camera &camera){

    camera.Disconnect();
    if(camera.IsConnected()){
        cout << "Problems while disconnecting camera" << endl;
        return -1;
    }
    return 0;
}


int camera_capture(Camera &camera, vector<cv::Mat> &patterns, vector<Mat> &patterns_captured){

    if(!patterns.size()){
        cout << "Pattern is empty!" << endl;
        return -1;
    }

    //Create Frame for displaying Pictures
    namedWindow("Pattern", WINDOW_NORMAL);
    moveWindow("Pattern", 1024 + 316, -20);
    setWindowProperty("Pattern", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

    for(int pattern_i = 0; pattern_i < patterns.size(); pattern_i++){

        imshow("Pattern", patterns[pattern_i]);
        waitKey(100);
        Image new_image;
        FlyCapture2::Error error = camera.RetrieveBuffer(&new_image);
        if (error != PGRERROR_OK) {

          std::cout << "capture error" << std::endl;
          continue;
        }
        Image grayscale;
        new_image.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &grayscale);
        unsigned int rowBytes =
            (double)grayscale.GetReceivedDataSize() / (double)grayscale.GetRows();
        Mat frame = Mat(grayscale.GetRows(), grayscale.GetCols(), CV_8U,
                        grayscale.GetData(), rowBytes);

        // checking if frame is not empty and showing camera informations
        if (frame.data) {

          patterns_captured.push_back(frame);
          pattern_i++;

          } else {
        cout << "Could not save pattern" << pattern_i + 1 << endl;
            return -1;
          }
    }

    destroyWindow("Pattern");
    waitKey(1);
    return 1;
  }


int camera_routine(Camera & camera, vector<Mat> &patterns, vector<Mat> &patterns_captured){

    // Information not used yet-----------
    CameraInfo caminfo;
    //------------------------------
    camera_connect(camera, caminfo);
    camera_adjust(camera);
    camera_capture(camera, patterns, patterns_captured);
    camera_disconnect(camera);

    return 0;

}
