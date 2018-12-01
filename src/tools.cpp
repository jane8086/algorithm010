#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int save_images(std::vector<Mat> &images){


    //Look if folder with images already exists
    for(int image_i = 0; image_i < images.size(); image_i++){

        string path = "images/" + to_string(image_i)+".png";
        imwrite(path, images[image_i]);

    }
    return 0;
}

int load_images(vector<Mat> &phase_images, int &amount_shifts){

    for(int image_i = 0; image_i < amount_shifts; image_i++){

        string



    }




}
