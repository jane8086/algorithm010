#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
using namespace  cv;
using namespace std;

int convert_binary(vector<Mat> &graycode_images){

    //Seting contanst threshold --> Need to be modular someday...

    for(int image_i = 0; image_i < graycode_images.size(); image_i++){

        threshold(graycode_images[image_i], graycode_images[image_i], 50, 1, THRESH_BINARY);

    }



}
