#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include "flycapture/FlyCapture2.h"
#include "include/monitor.h"

using namespace FlyCapture2;
using namespace std;
using namespace cv;

int save_images(std::vector<Mat> &images){


    //Look if folder with images already exists
    for(int image_i = 0; image_i < images.size(); image_i++){

        string path = "images/pattern_" + to_string(image_i)+".png";
        imwrite(path, images[image_i]);

    }
    return 0;
}


int load_images_phase_color(vector<Mat> &phase_images){

    int amount_shifts = 3; // Can't make more shifts than three color channels!

    for( int image_i = 1; image_i < amount_shifts+1; image_i++){

        string image_path ="images/pattern_cam_im" + to_string(image_i) + ".png";
        Mat image = imread(image_path, IMREAD_GRAYSCALE);
        if(image.empty()){
            cout << "Coud not read image from filesystem" << endl;
            return -1;
        }
        phase_images.push_back(image);

    }
}


int load_images_phase(vector<Mat> &phase_images, int &amount_shifts, int color_method){

    if(color_method){
        load_images_phase_color(phase_images);
    }else{

    for(int image_i = 1; image_i < 2*amount_shifts+1; image_i++){

        string image_path ="images/pattern_cam_im" + to_string(image_i) + ".png";
        Mat image = imread(image_path, IMREAD_GRAYSCALE);
        if(image.empty()){
            cout << "Coud not read image from filesystem" << endl;
            return -1;
        }
        phase_images.push_back(image);
    }
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


int save_points_to_csv(vector<Point2f> points_2d, string filename){

    ofstream fs1;
    fs1.open(filename);
    fs1 << "x,y, \n";

    //iterate throuugh whole vector
    for(int point_i=0; point_i<points_2d.size(); point_i++){

        fs1 << to_string(points_2d[point_i].x) + "," + to_string(points_2d[point_i].y) + "\n";

    }

    fs1.close();

}


int save_points_to_csv(vector<Point> points_2d, string filename){

    ofstream fs1;
    fs1.open(filename);
    fs1 << "x,y, \n";

    //iterate throuugh whole vector
    for(int point_i=0; point_i<points_2d.size(); point_i++){

        fs1 << to_string(points_2d[point_i].x) + "," + to_string(points_2d[point_i].y) + "\n";

    }

    fs1.close();

}


int save_points_to_csv(vector<Point3f> points_3d, string filename){

    ofstream fs1;
    fs1.open(filename);
    fs1 << "x,y, \n";

    //iterate throuugh whole vector
    for(int point_i=0; point_i<points_3d.size(); point_i++){

        fs1 << to_string(points_3d[point_i].x) + "," + to_string(points_3d[point_i].y) + "," + to_string(points_3d[point_i].z) + "\n";

    }

    fs1.close();

}


int saveDatayml(vector<Point2f> image_point, vector<Point> points_world_pixel, vector<Point3f> points_world){

    save_points_to_csv(image_point, "imagepoints.csv");
    save_points_to_csv(points_world_pixel, "displaypoints_pixel.csv");
    save_points_to_csv(points_world, "displaypoints_world_mm.csv");
}


bool isPowerOfTwo (int x)
{
  /* First x in the below expression is for the case when x is 0 */
  return x && (!(x&(x-1)));
}


int load_image_ground(vector<Mat> &ground_image, int &amount_shifts, int &amount_pattern)
{
    int period = pow(2,(amount_pattern - 2*amount_shifts-2)/2);

    for(int image_i = amount_shifts*2+2*log2(period)+1; image_i < amount_shifts*2+2*log2(period)+3; image_i++)
    {

        string image_path ="images/pattern_cam_im" + to_string(image_i) + ".png";
        Mat image = imread(image_path, IMREAD_GRAYSCALE);

        if(image.empty())
        {
            cout << "Coud not read ground truth image from filesystem" << endl;
            return -1;
        }
        ground_image.push_back(image);
    }
    return 0;
}


// create gradient image to adjust brightness
int create_gradient(Mat &gradient, Monitor &monitor)
{
    gradient = Mat(monitor.size_y, monitor.size_x, CV_32F, Scalar(0));
    for (int r = 0; r < gradient.cols; r++)
    {
        gradient.col(r) = 1/monitor.size_x*r;
    }

    int count = 0;
    for (int i = 0; i < gradient.rows; i++)
    {
        for (int j = 0; j < gradient.cols; j++)
        {
            if (gradient.at<uchar>(i,j) == 1)
            {
                count++;
            }
        }
    }
    float white = (float)count/(float)(gradient.rows*gradient.cols);
    cout << white << endl;
    imshow("Gradient", gradient);
    waitKey();

    return 0;
}


// create monoton-color threshold image to adjust camera's gain
int create_threshold_image(Mat &threshold_image, Monitor &monitor, int &threshold_value)
{
    if (threshold_value < 100)
    {
        cout << " The threshold image should be brighter. Suggested: 100 -> 254)" << endl;
        return -1;
    } else if (threshold_value > 255)
    {
        cout << " Wrong threshold value. Suggested: 200 -> 254)" << endl;
        return -1;
    }
    threshold_image = Mat(monitor.size_y, monitor.size_x, CV_8UC1, Scalar(threshold_value));
//    imshow("Threshold", threshold_image);
//    waitKey();
    return 1;
}


