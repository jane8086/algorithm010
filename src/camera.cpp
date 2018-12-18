#include "flycapture/FlyCapture2.h"
#include <iostream>
#include "opencv2/opencv.hpp"



using namespace FlyCapture2;
using namespace std;
using namespace cv;


int camera_adjust(Camera &camera){

    Property prop;
    prop.type = BRIGHTNESS;
    prop.onOff = true;
    prop.autoManualMode = false;

    //Set gain
    Property prop_g;
    prop_g.type = GAIN;
    prop_g.autoManualMode = false;
    prop_g.absControl = true;
    prop_g.absValue = 0;

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
    moveWindow("Pattern", +2000, -20);
    setWindowProperty("Pattern", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

    int pattern_i = 0;
    string path = "images/" ;

    while(pattern_i < patterns.size()){

        imshow("Pattern", patterns[pattern_i]);
        waitKey(500);
        Image new_image;
        FlyCapture2::Error error = camera.RetrieveBuffer(&new_image);
        if (error != PGRERROR_OK) {

          std::cout << "capture error" << std::endl;
          break;
        }
        Image grayscale;
        new_image.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &grayscale);
        unsigned int rowBytes =
            (double)grayscale.GetReceivedDataSize() / (double)grayscale.GetRows();
        Mat frame = Mat(grayscale.GetRows(), grayscale.GetCols(), CV_8U,
                        grayscale.GetData(), rowBytes);

        // checking if frame is not empty and showing camera informations
        if (frame.data) {

          Mat capture_image = frame;
          ostringstream name;
          name << pattern_i + 1;
          bool saved =
              imwrite(path + "pattern_cam_im" + name.str() + ".png", capture_image);

          if (saved) {

//            cout << "pattern:  " << image_counter + 1 << "was saved" << endl;
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



int camera_adjust_gain(Camera &camera, float &gain)
{
    //Set gain
    Property prop_g;
    prop_g.type = GAIN;
    prop_g.autoManualMode = false;
    prop_g.absControl = true;
    prop_g.absValue = gain;
    FlyCapture2::Error error1 = camera.SetProperty(&prop_g);
    return 0;
}


int camera_gain_adjustment(Camera &camera, Mat &threshold_image, int &threshold_value, float brighter_percent_threshold = 0.00)
{
    CameraInfo caminfo;
    //------------------------------
    camera_connect(camera, caminfo);
    camera_adjust(camera); // set gain first to zero

    namedWindow("Adjust brightness", WINDOW_NORMAL);
    moveWindow("Adjust brightness", +2000, -20);
    setWindowProperty("Adjust brightness", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
    string path = "images/" ;


    if (brighter_percent_threshold <=0 || brighter_percent_threshold >1)
    {
        cout << " The percentage must be between 0 and 1" << endl;
        return -1;
    }

    cout << "Adjusting camera gain ... " << endl;
    float gain = 0;
    bool capturing = true;

    while (capturing)
    {
        imshow("Adjust brightness", threshold_image);
        waitKey(500);
        Image new_image;
        FlyCapture2::Error error = camera.RetrieveBuffer(&new_image);

        if (error != PGRERROR_OK) {
          std::cout << "capture error" << std::endl;
          destroyWindow("Adjust brightness");
          waitKey(1);
          return -1;
        }

        Image grayscale;
        new_image.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &grayscale);
        unsigned int rowBytes =
            (double)grayscale.GetReceivedDataSize() / (double)grayscale.GetRows();
        Mat frame = Mat(grayscale.GetRows(), grayscale.GetCols(), CV_8U,
                        grayscale.GetData(), rowBytes);

        // checking if frame is not empty and showing camera informations
        if (frame.data)
        {
            Mat capture_image = frame;
            bool saved = imwrite(path + "threshold_img.png", capture_image);
            if (saved)
            {
                // count number of pixel which has higher value than threshold
                int count_bright = 0; // brighter pixels count
                int count_dark = 0; // darker pixels count
                for (int i = 0; i < capture_image.rows; i++)
                {
                    for (int j = 0; j < capture_image.cols; j++)
                    {
                        if (capture_image.at<uchar>(i,j) > threshold_value)
                        {
                            count_bright++;
                        } else if (capture_image.at<uchar>(i,j) < (int)threshold_value*0.8) // count the number of pixel darker than 80% of threshold
                        {
                            count_dark++;
                        }
                    }
                }

                float brighter = (float)count_bright/(float)(capture_image.rows*capture_image.cols);
                float darker = (float)count_dark/(float)(capture_image.rows*capture_image.cols) ;
                cout << brighter << "% brighter and " << darker << "% darker" << endl;

                // check the threshold
                if ( brighter > brighter_percent_threshold && // if too bright and not too dark at all
                   darker <= brighter_percent_threshold + 0.1)
                {
                    cout << " Current gain: " << gain << ". Decreasing the gain..." << endl;
                    gain = gain - 0.1;
                    camera_adjust_gain(camera,gain);

                    continue;
                }
                else if ( brighter <= brighter_percent_threshold && // if the images is too dark, manually adjust the gain and try again
                          darker > brighter_percent_threshold + 0.3)
                {

                    cout << " Increase the gain and try again !" << endl;
                    imshow("Threshold image", capture_image);
                    waitKey();
                    capturing = false;
                    return -1;

//                    // increase the gain here
//                    cout << " Current gain: " << gain << ". Increasing the gain..." << endl;
//                    camera_adjust(camera, -gain);
//                    continue;
                }
                else
                {
                    cout << "The proper gain is: " << gain << endl;
                    capturing = false;

                }

            } else
            {
                cout << "could not save gradient image" << endl;
                capturing = false;
                return -1;
            }
        }
    }

    destroyWindow("Adjust brightness");
    waitKey(1);
    return 1;

}




