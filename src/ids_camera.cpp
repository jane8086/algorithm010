#include <iostream>
#include <stddef.h>
#include <stdio.h>

#include "opencv2/opencv.hpp"
#include "ueye.h"
#include <ueye_deprecated.h>

using namespace std;
using namespace cv;

void initializeCameraInterface(HIDS &hCam_internal) {

  SENSORINFO sInfo;

  // Open cam and see if it was succesfull
  INT nRet = is_InitCamera(&hCam_internal, NULL);
  if (nRet == IS_SUCCESS) {
    cout << "Camera initialized!" << endl;
  }

  // You can query information about the sensor type used in the camera
  is_GetSensorInfo(hCam_internal, &sInfo);

  // Need to find out the memory size of the pixel and the colour mode
  int nColorMode;
  int nBitsPerPixel = 24;

  if (sInfo.nColorMode == IS_COLORMODE_BAYER) {
    // For color camera models use RGB24 mode
    nColorMode = IS_CM_BGR8_PACKED;
    nBitsPerPixel = 24;
  } else if (sInfo.nColorMode == IS_COLORMODE_CBYCRY) {
    // For CBYCRY camera models use RGB32 mode
    nColorMode = IS_CM_BGRA8_PACKED;
    nBitsPerPixel = 32;
  } else {
    // For monochrome camera models use Y8 mode
    nColorMode = IS_CM_MONO8;
    nBitsPerPixel = 24;
  }

  //
  double enable = 1;
  double disable = 0;
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_GAIN, &enable, 0);
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_WHITEBALANCE, &enable,
                      0);
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_FRAMERATE, &disable, 0);
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_SHUTTER, &disable, 0);
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_SENSOR_GAIN, &enable,
                      0);
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_SENSOR_WHITEBALANCE,
                      &enable, 0);
  is_SetAutoParameter(hCam_internal, IS_SET_ENABLE_AUTO_SENSOR_SHUTTER,
                      &disable, 0);

  double FPS, NEWFPS;
  FPS = 15;
  double fps;
  is_SetFrameRate(hCam_internal, FPS, &NEWFPS);

  double parameter = 50;
  int error = is_Exposure(hCam_internal, IS_EXPOSURE_CMD_SET_EXPOSURE,
                          (void *)&parameter, sizeof(parameter));
  if (error != IS_SUCCESS) {
  }

  error = is_Exposure(hCam_internal, IS_EXPOSURE_CMD_GET_EXPOSURE,
                      (void *)&parameter, sizeof(parameter));

  UINT uiCaps = 0;

  nRet = is_Focus(hCam_internal, FDT_CMD_GET_CAPABILITIES, &uiCaps,
                  sizeof(uiCaps));

  if (nRet == IS_SUCCESS && (uiCaps & FOC_CAP_AUTOFOCUS_SUPPORTED)) {
    nRet = is_Focus(hCam_internal, FOC_CMD_SET_DISABLE_AUTOFOCUS, NULL, 0);
  }

  nRet = is_SetGamma(hCam_internal, 600);

  // Store image in camera memory --> option to chose data capture method
  // Then access that memory to retrieve the data
  INT displayMode = IS_SET_DM_DIB;
  nRet = is_SetDisplayMode(hCam_internal, displayMode);
}

// Capture a frame and push it in a OpenCV mat element
Mat getFrame(HIDS *hCam, int width, int height, cv::Mat &mat) {
  // Allocate memory for image
  char *pMem = NULL;
  int memID = 0;
  is_AllocImageMem(*hCam, width, height, 8, &pMem, &memID);

  // Activate the image memory for storing the frame captured
  // Grabbing the image
  // Getting the data of the frame and push it in a Mat element
  is_SetImageMem(*hCam, pMem, memID);
  is_FreezeVideo(*hCam, IS_WAIT);

  VOID *pMem_b;
  int retInt = is_GetImageMem(*hCam, &pMem_b);
  if (retInt != IS_SUCCESS) {
    cout << "Image data could not be read from memory!" << endl;
  }
  memcpy(mat.ptr(), pMem_b, mat.cols * mat.rows);

  return mat;
}

void take_picture_ids() {

  // ---------------------------------------------------------------------------------------------------------------
  // START BY CONFIGURING THE INTERFACE WITH THE UEYE CAMERA
  // ---------------------------------------------------------------------------------------------------------------

  // Camera initialisation
  // Index 0 means taking the first camera available
  HIDS hCam = 0;
  initializeCameraInterface(hCam);

  // ---------------------------------------------------------------------------------------------------------------
  // CAPTURE DATA AND PROCESS
  // ---------------------------------------------------------------------------------------------------------------

  while (true) {
    // Create an image and grab a frame
    Mat current_image(1000, 1000, CV_8UC1);
    getFrame(&hCam, 1000, 1000, current_image);

    // PERFORM YOUR OPENCV PROCESSING HERE!
    // Visualise the data
    imshow("test_interface", current_image);

    // Check if we need to stop processing
    if ((int)waitKey(10) >= 0) {
      break;
    }
  }

  // Release the camera again
  is_ExitCamera(hCam);
}
