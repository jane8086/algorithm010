#ifndef PHASES_H
#define PHASES_H

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

int calculate_relative_phase(Mat im1, Mat im2, Mat im3, Mat &relative_phase);
int calculate_absolute_phase(Mat relative_phase, Mat period_number, int range, vector<Mat> &absolute_phase);

#endif // PHASES_H
