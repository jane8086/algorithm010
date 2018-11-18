#include "flycapture/FlyCapture2.h"
#include <iostream>


using namespace FlyCapture2;
using namespace std;

int camera_adjust(Camera &camera){

    Property prop;
    prop.type = BRIGHTNESS;
    prop.onOff = true;
    prop.autoManualMode = false;
    Property prop_g;
    prop_g.type = GAIN;
    prop_g.autoManualMode = false;
    Error error1 = camera.SetProperty(&prop);
    Error error2 = camera.SetProperty(&prop_g);
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
