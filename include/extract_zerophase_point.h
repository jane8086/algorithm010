#ifndef EXTRACT_ZEROPHASE_POINT_H
#define EXTRACT_ZEROPHASE_POINT_H
#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "tools.h"
#include <iostream>

int detect_edge_phase_vertical(Mat &relative, Mat &frame, Mat &edge_map);

int detect_edge_phase_horizontal(Mat &relative, Mat &frame, Mat &edge_map);

int correct_period_vertical(Mat &extract_point, Mat &period_number_vertical);

int correct_period_horizontal(Mat &extract_point, Mat &period_number_horizontal);

#endif // EXTRACT_ZEROPHASE_POINT_H
