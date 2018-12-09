#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
using namespace  cv;
using namespace std;

int convert_binary(vector<Mat> &graycode_images){

    //Seting contanst threshold --> Need to be modular someday...

    for(int image_i = 0; image_i < graycode_images.size(); image_i++){

        threshold(graycode_images[image_i], graycode_images[image_i], 40, 1, THRESH_BINARY);

    }

}

int reduce_moire(vector<Mat> &phase_shift, vector<Mat> &dst_phase_shift,int diameter)
{
    if (( diameter <= 0) || (diameter <=20))
    {
        cout << "Invalid value of diameter. Suggested: 20->80" << endl;
        return -1;
    }
    if (!dst_phase_shift.empty())
    {
        cout << "Destination vector must be empty" << endl;
        return -1;
    }

    for (int i = 0; i < phase_shift.size(); i++)
    {
        Mat dst = phase_shift[i].clone();
        bilateralFilter(phase_shift[i],dst,diameter,50,50);
        dst_phase_shift.push_back(dst);
    }
    return 0;
}
