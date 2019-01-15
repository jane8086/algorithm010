#ifndef TOOLS_H
#define TOOLS_H
#include "flycapture/FlyCapture2.h"
#include "include/monitor.h"
#include "opencv2/opencv.hpp"

using namespace FlyCapture2;
using namespace std;
using namespace cv;

void save_results(const int periods, const int amount_shifts,
                  const int color_patterns, const int novel_method,
                  const double avg_error, const double max_error,
                  const double distError);

int save_images(const std::vector<cv::Mat> &images);
int load_images_novel(vector<Mat> &novel_images, int &amount_shifts);

/** @brief Loads captured  phase shifting patterns from folder images
 *  @param color_method If 1, colored patterns are loaded
 *
 */
int load_images_phase(std::vector<cv::Mat> &phase_images, int &amount_shifts,
                      int color_method);

/** @brief Loads captured graycode  patterns from folder images and shadow masks
 *
 */
int load_images_gray(std::vector<cv::Mat> &gray_images, int &amount_shifts,
                     int &amount_patterns);

void saveDatayml(const vector<Point2d> &new_imagepoints,
                 const vector<Point2d> &phase_values, const string &name);

/** @brief Saves all points used for calibration into two csv files
 *
 */
int saveDatayml(vector<Point2d> image_point_calibrated,
                vector<Point3d> points_world_calibrated);

/** @brief Savesall gathered points into a data.yml file
 *
 */
int saveDatayml(vector<Point2d> image_point, vector<Point2d> points_world_pixel,
                vector<Point3d> points_world);

bool isPowerOfTwo(int x);

/** @brief Loads captured shadow masks patterns from folder images and shadow
 * masks
 *
 */
int load_image_ground(vector<Mat> &ground_image, int &amount_shifts,
                      int &amount_pattern, int period);

/** @brief Create gradient image to adjust brightness of the camera
 */
int create_gradient(Mat &gradient, Monitor &monitor);

/** @brief Create threshold image to adjust brightness of the camera
 */
int create_threshold_image(Mat &threshold_image, Monitor &monitor,
                           int &threshold_value);

void convert_to_floatpoints(const vector<Point3d> &world_points,
                            const vector<Point2d> &image_points,
                            vector<Point3f> &worldpoints_float,
                            vector<Point2f> &imagepoints_float);

Mat average_captureimages(const vector<Mat> &patterns_captured,
                          int captured_times);

#endif // TOOLS_H
