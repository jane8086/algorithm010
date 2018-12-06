#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int save_images(std::vector<Mat> &images){


    //Look if folder with images already exists
    for(int image_i = 0; image_i < images.size(); image_i++){

        string path = "images/pattern_" + to_string(image_i)+".png";
        imwrite(path, images[image_i]);

    }
    return 0;
}

int load_images_phase(vector<Mat> &phase_images, int &amount_shifts){

    for(int image_i = 1; image_i < 2*amount_shifts+1; image_i++){

        string image_path ="images/pattern_cam_im" + to_string(image_i) + ".png";
        Mat image = imread(image_path, IMREAD_GRAYSCALE);
        if(image.empty()){
            cout << "Coud not read image from filesystem" << endl;
            return -1;
        }
        phase_images.push_back(image);



    }

    return 0;

}

int load_images_gray(vector<Mat> &gray_images, int &amount_shifts, int &amount_patterns){

    for(int image_i = amount_shifts*2+1; image_i < amount_patterns-1; image_i++){ // last two images are shadow masks

        string image_path ="images/pattern_cam_im" + to_string(image_i) + ".png";
        Mat image = imread(image_path, IMREAD_GRAYSCALE);
        if(image.empty()){
            cout << "Coud not read image from filesystem" << endl;
            return -1;
        }
        gray_images.push_back(image);



    }

    return 0;


}
