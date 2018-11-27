#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int save_images(std::vector<Mat> &images){

    string path = "/images/";


    //Look if folder with images already exists
    for(int image_i = 0; image_i < images.size(); image_i++){

        imwrite(path + "picture" + to_string(image_i), images[image_i]);

    }
}
