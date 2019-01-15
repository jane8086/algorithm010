#include "flycapture/FlyCapture2.h"
#include "include/tools.h"
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
  prop_g.absValue = 2.408;

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
                   vector<Mat> &patterns_captured, const bool take_average) {

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

  while (pattern_i < patterns.size()) {

    imshow("Pattern", patterns[pattern_i]);
    waitKey(500);
    Image new_image;
    int amount_pictures_average = 10;
    vector<Mat> average_frames(amount_pictures_average);
    Mat frame;
    if (take_average) {

      for (auto picture_i = 0; picture_i < amount_pictures_average;
           ++picture_i) {

        FlyCapture2::Error error = camera.RetrieveBuffer(&new_image);
        if (error != PGRERROR_OK) {

          std::cout << "capture error" << std::endl;
          break;
        }
        Image grayscale;
        new_image.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &grayscale);
        unsigned int rowBytes = (double)grayscale.GetReceivedDataSize() /
                                (double)grayscale.GetRows();
        average_frames[picture_i] =
            Mat(grayscale.GetRows(), grayscale.GetCols(), CV_8U,
                grayscale.GetData(), rowBytes);
      }

      frame = average_captureimages(average_frames, amount_pictures_average);

    } else {
      FlyCapture2::Error error = camera.RetrieveBuffer(&new_image);
      if (error != PGRERROR_OK) {

        std::cout << "capture error" << std::endl;
        break;
      }
      Image grayscale;
      new_image.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &grayscale);
      unsigned int rowBytes =
          (double)grayscale.GetReceivedDataSize() / (double)grayscale.GetRows();
      frame = Mat(grayscale.GetRows(), grayscale.GetCols(), CV_8U,
                  grayscale.GetData(), rowBytes);
    }

    // checking if frame is not empty and showing camera informations
    if (frame.data) {

      Mat capture_image = frame;
      ostringstream name;
      name << pattern_i + 1;
      bool saved =
          imwrite(path + "pattern_cam_im" + name.str() + ".png", capture_image);

      if (saved) {

        // cout << "pattern:  " << image_counter + 1 << "was saved" << endl;
        pattern_i++;
      } else {
        cout << "could not save image: " << pattern_i + 1 << endl;
        return -1;
      }
    }
  }

  destroyWindow("Pattern");
  waitKey(1);
  return 1;
}

int camera_routine(Camera &camera, vector<Mat> &patterns,
                   vector<Mat> &patterns_captured, const bool take_average) {

  // Information not used yet-----------
  CameraInfo caminfo;
  //------------------------------
  camera_connect(camera, caminfo);
  camera_adjust(camera);
  camera_capture(camera, patterns, patterns_captured, take_average);
  camera_disconnect(camera);

  return 0;
}
