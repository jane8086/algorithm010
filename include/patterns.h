#ifndef PATTERNS_H
#define PATTERNS_H

#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

int create_patterns_novel(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns_novel);
int create_patterns_phaseshift_general(int screen_Width, int screen_Hight, int period_sum, int step_number, vector<Mat> &patterns_phaseshift);
int create_patterns_phaseshift(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns_phaseshift);
int create_patterns_colorphaseshift(int screen_Width, int screen_Hight, int period_sum, vector<Mat> &patterns_colorphaseshift);
int create_patterns_graycodevertical(int screen_Width,int screen_Hight,int n, vector<Mat> &graycodevertical);
int create_patterns_graycodehorizontal(int screen_Width,int screen_Hight,int period_sum, vector<Mat> &patterns_graycode_horizontal);
int create_patterns_all(int screen_Width, int screen_Hight, int period_sum, int pattern_type, vector<Mat> &patterns);
#endif // PATTERNS_H
