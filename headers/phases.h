#ifndef PHASES_H
#define PHASES_H

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

/** @brief Calculates two absolut phasemaps vertical and horizontal
 *
 */
int calculate_absolute_phasemaps(vector<Mat> &phaseMaps_absolut, int &amount_shifts, int amount_patterns);
#endif // PHASES_H
