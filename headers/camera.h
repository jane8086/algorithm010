#ifndef CAMERA
#define CAMERA

#include "flycapture/FlyCapture2.h"

int camera_adjust(FlyCapture2::Camera &camera);

/** @brief Connects the Blackfly S to the program.
 *
 */
int camera_connect(FlyCapture2::Camera &camera, FlyCapture2::CameraInfo &caminfo);
int camera_disconnect(FlyCapture2::Camera &camera);

#endif // CAMERA

