#ifndef CAMERA
#define CAMERA

#include "flycapture/FlyCapture2.h"

int camera_adjust(FlyCapture2::Camera &camera);
int camera_connect(FlyCapture2::Camera &camera, FlyCapture2::CameraInfo &caminfo);

#endif // CAMERA

