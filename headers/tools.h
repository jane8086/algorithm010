#ifndef TOOLS_H
#define TOOLS_H

#include "opencv2/opencv.hpp"

int save_images(std::vector<cv::Mat> &images);
/** @brief Loads captured  phase shifting patterns from folder images
 *
 */
int load_images_phase(std::vector<cv::Mat> &phase_images, int &amount_shifts);
/** @brief Loads captured graycode  patterns from folder images and shadow masks
 *
 */
int load_images_gray(std::vector<cv::Mat> &gray_images, int &amount_shifts, int &amount_patterns);

#endif // TOOLS_H
