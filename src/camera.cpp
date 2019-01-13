#include "flycapture/FlyCapture2.h"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace FlyCapture2;
using namespace std;
using namespace cv;

int camera_adjust(Camera &camera) {

  Property prop;
  prop.type = BRIGHTNESS;
  prop.onOff = true;
  prop.autoManualMode = false;

  // Set gain
  Property prop_g;
  prop_g.type = GAIN;
  prop_g.autoManualMode = false;
  prop_g.absControl = true;
  prop_g.absValue = 0;

  FlyCapture2::Error error1 = camera.SetProperty(&prop);
  FlyCapture2::Error error2 = camera.SetProperty(&prop_g);
  return 0;
}

int camera_connect(Camera &camera, CameraInfo &caminfo) {

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

  // std::cout << camInfo.sensorResolution << " " << camInfo.modelName << " "
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

int camera_disconnect(Camera &camera) {

  camera.Disconnect();
  if (camera.IsConnected()) {
    cout << "Problems while disconnecting camera" << endl;
    return -1;
  }
  return 0;
}

int camera_capture(Camera &camera, vector<cv::Mat> &patterns,
                   vector<Mat> &patterns_captured, int captured_times) {

  if (!patterns.size()) {
    cout << "Pattern is empty!" << endl;
    return -1;
  }

  // Create Frame for displaying Pictures
  namedWindow("Pattern", WINDOW_NORMAL);
  moveWindow("Pattern", +2000, -20);
  setWindowProperty("Pattern", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

  int pattern_i = 0;
  string path = "images/";

 // int captured_num = patterns.size() * captured_times;
  //captured_num : total times to capture
  //captured_times : how many times to capture a single pattern

  while (pattern_i < patterns.size()) {
    imshow("Pattern", patterns[pattern_i]);
    waitKey(500 * captured_times); //increasing pattern display time
    Image new_image;
    FlyCapture2::Error error = camera.RetrieveBuffer(&new_image);
    if (error != PGRERROR_OK) {
      std::cout << "capture error" << std::endl;
      break;
    }

    int captured_i = 0;
    while(captured_i < captured_times)  //capture a sigle pattern captured_times times
    {
        //Image new_image;
        Image grayscale;
        new_image.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &grayscale);
        unsigned int rowBytes =
            (double)grayscale.GetReceivedDataSize() / (double)grayscale.GetRows();
        Mat frame = Mat(grayscale.GetRows(), grayscale.GetCols(), CV_8U,
                        grayscale.GetData(), rowBytes);

        // checking if frame is not empty and showing camera informations
        if (frame.data) {

          Mat capture_image = frame;
          ostringstream name,subname;
          name << pattern_i + 1;
          subname << captured_i + 1;
          bool saved =
              imwrite(path + "pattern_cam_im" + name.str() + "_" +subname.str() +".png", capture_image);

          if (saved) {

            //cout << "pattern:  " << image_counter + 1 << "was saved" << endl;

          } else {
            cout << "could not save image: " << pattern_i + 1 << "_" << captured_i +1 << endl;
            return -1;
          }
        }
        captured_i++;
    }
    pattern_i++;
  }

  destroyWindow("Pattern");
  waitKey(1);
  return 1;
}

int camera_routine(Camera &camera, vector<Mat> &patterns,
                   vector<Mat> &patterns_captured,int captured_times) {

  // Information not used yet-----------
  CameraInfo caminfo;
  //------------------------------
  camera_connect(camera, caminfo);
  camera_adjust(camera);
  camera_capture(camera, patterns, patterns_captured, captured_times);
  camera_disconnect(camera);

  return 0;
}
