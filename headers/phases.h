#ifndef PHASES_H
#define PHASES_H

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

/** @brief Calculates the raltive phase map from vector of three phase shifted patterns
 *
 */
Mat calculate_relative_phasemap(vector<Mat> &patterns);
int calculate_absolute_phase(Mat relative_phase, Mat period_number, int range, vector<Mat> &absolute_phase);
/** @brief Loads captured graycode phase shifting patterns from folder
 *
 */
int load_phaspatterns(vector<Mat> &phase_images, int amount_shifts);

#endif // PHASES_H
