#ifndef TOOLS_H
#define TOOLS_H
#include "opencv2/opencv.hpp"
#include "include/monitor.h"
#include "flycapture/FlyCapture2.h"

using namespace std;
using namespace cv;


int save_images(std::vector<cv::Mat> &images);


/** @brief Loads captured  phase shifting patterns from folder images
 *  @param color_method If 1, colored patterns are loaded
 *
 */
int load_images_phase(std::vector<cv::Mat> &phase_images, int &amount_shifts, int color_method);


/** @brief Loads captured graycode  patterns from folder images and shadow masks
 *
 */
int load_images_gray(std::vector<cv::Mat> &gray_images, int &amount_shifts, int &amount_patterns);

/** @brief Savesall gathered points into a data.yml file
 *
 */
int saveDatayml(vector<Point2f> image_point, vector<Point> points_world_pixel, vector<Point3f> points_world);

bool isPowerOfTwo (int x);


/** @brief Loads captured shadow masks patterns from folder images and shadow masks
 *
 */
int load_image_ground(vector<Mat> &ground_image, int &amount_shifts, int &amount_pattern);

/** @brief Create gradient image to adjust brightness of the camera
 */
int create_gradient(Mat &gradient, Monitor monitor);

/** @brief Adjust brightness of camera
 */
int camera_brightness_adjust(Camera &camera, Mat &gradient, float white_threshold);

#endif // TOOLS_H

