#ifndef TOOLS_H
#define TOOLS_H

#include "opencv2/opencv.hpp"

int save_images(std::vector<cv::Mat> &images);
/** @brief Loads captured graycode phase shifting patterns from folder
 *
 */
int load_images(std::vector<cv::Mat> &phase_images, int amount_shifts);

#endif // TOOLS_H
