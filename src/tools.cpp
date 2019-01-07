#include "flycapture/FlyCapture2.h"
#include "include/monitor.h"
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace FlyCapture2;
using namespace std;
using namespace cv;

int patterns_lookuptable(vector<Mat> &patterns)
{
    ifstream in("images_index.txt");
    string line;

    if(in) //if the indexlist exist
    {
        while(getline(in,line))
        {
            //cout<< line << endl;
            Mat temp;
            temp = imread(line);
            patterns.push_back(temp.clone());//save exsited images into a vector
        }

    }else{
        cout<<"images do not exist"<<endl;
    }

    return 0;

}


int save_images(const std::vector<Mat> &images) {

  // Look if folder with images already exists
    string dir = "images";
    //make a folder if it doesn't exist
    if(access(dir.c_str(),0)==-1)
    {
        //cout<< "folder doesn't exist, now make it"<<endl;
        int flag = mkdir(dir.c_str(),0777);
        if (flag ==0)
        {
           //cout<<"make successfully"<<endl;
        }else{
            cout<<"make folder failed"<<endl;
        }
    }
  for (int image_i = 0; image_i < images.size(); image_i++) {

    string path = "images/pattern_" + to_string(image_i) + ".png";
    imwrite(path, images[image_i]);
  }

  //creat an indexlist to deliver the info about the imagesname
  ofstream indexfile;
  indexfile.open("images_index.txt");
  if(!indexfile.is_open())
      return 0;
  for(int image_i = 0; image_i < images.size(); image_i++){
    indexfile<<"images/pattern_" + to_string(image_i)+".png"+ "\n";
  }
  indexfile.close();

  return 0;
}

int load_images_phase_color(vector<Mat> &phase_images) {

  int amount_shifts = 3; // Can't make more shifts than three color channels!

  for (int image_i = 1; image_i < amount_shifts + 1; image_i++) {

    string image_path = "images/pattern_cam_im" + to_string(image_i) + ".png";
    Mat image = imread(image_path, IMREAD_GRAYSCALE);
    if (image.empty()) {
      cout << "Coud not read image from filesystem" << endl;
      return -1;
    }
    phase_images.push_back(image);
  }
}

int load_images_phase(vector<Mat> &phase_images, int &amount_shifts,
                      int color_method) {

  if (color_method) {
    load_images_phase_color(phase_images);
  } else {

    for (int image_i = 1; image_i < 2 * amount_shifts + 1; image_i++) {

      string image_path = "images/pattern_cam_im" + to_string(image_i) + ".png";
      Mat image = imread(image_path, IMREAD_GRAYSCALE);
      if (image.empty()) {
        cout << "Coud not read image from filesystem" << endl;
        return -1;
      }
      phase_images.push_back(image);
    }
  }
  return 0;
}

int load_images_gray(vector<Mat> &gray_images, int &amount_shifts,
                     int &amount_patterns) {

  for (int image_i = amount_shifts * 2 + 1; image_i < amount_patterns - 1;
       image_i++) { // last two images are shadow masks

    string image_path = "images/pattern_cam_im" + to_string(image_i) + ".png";
    Mat image = imread(image_path, IMREAD_GRAYSCALE);
    if (image.empty()) {
      cout << "Coud not read image from filesystem" << endl;
      return -1;
    }
    gray_images.push_back(image);
  }

  return 0;
}

int save_image_points_to_csv(const vector<Point2d> &points_2d,
                             const string &filename) {

  ofstream fs1;
  fs1.open(filename);
  fs1 << "u_image,v_image\n";

  // iterate throuugh whole vector
  for (int point_i = 0; point_i < points_2d.size(); point_i++) {

    fs1 << to_string(points_2d[point_i].x) + "," +
               to_string(points_2d[point_i].y) + "\n";
  }

  fs1.close();
}

int save_new_phasevalues_to_csv(vector<Point2d> points_2d, string filename) {

  ofstream fs1;
  fs1.open(filename);
  fs1 << "phasevalue_hor,phasevalue_ver\n";

  // iterate through whole vector
  for (int point_i = 0; point_i < points_2d.size(); point_i++) {

    fs1 << to_string(points_2d[point_i].x) + "," +
               to_string(points_2d[point_i].y) + "\n";
  }

  fs1.close();
}

int save_display_points_to_csv(vector<Point2d> points_2d, string filename) {

  ofstream fs1;
  fs1.open(filename);
  fs1 << "u_display,v_display\n";

  // iterate through whole vector
  for (int point_i = 0; point_i < points_2d.size(); point_i++) {

    fs1 << to_string(points_2d[point_i].x) + "," +
               to_string(points_2d[point_i].y) + "\n";
  }

  fs1.close();
}

int save_points_to_csv(vector<Point3d> points_3d, string filename) {

  ofstream fs1;
  fs1.open(filename);
  fs1 << "x_mm,y_mm,z_mm\n";

  // iterate throuugh whole vector
  for (int point_i = 0; point_i < points_3d.size(); point_i++) {

    fs1 << to_string(points_3d[point_i].x) + "," +
               to_string(points_3d[point_i].y) + "," +
               to_string(points_3d[point_i].z) + "\n";
  }

  fs1.close();
}

int saveDatayml(const vector<Point2d> &image_point_calibrated,
                const vector<Point2d> &phase_values) {

  save_image_points_to_csv(image_point_calibrated, "new_imagepoints.csv");
  save_new_phasevalues_to_csv(phase_values, "new_phasevalues.csv");
}

int saveDatayml(vector<Point2d> image_point, vector<Point2d> points_world_pixel,
                vector<Point3d> points_world) {

  save_image_points_to_csv(image_point, "imagepoints.csv");
  save_display_points_to_csv(points_world_pixel, "displaypoints_pixel.csv");
  save_points_to_csv(points_world, "displaypoints_world_mm.csv");
}

int saveDatayml(vector<Point2d> image_point_calibrated,
                vector<Point3d> points_world_calibrated) {

  save_image_points_to_csv(image_point_calibrated,
                           "imagepoints_calibrated.csv");
  save_points_to_csv(points_world_calibrated,
                     "displaypoints_world_mm_calibrated.csv");
}

bool isPowerOfTwo(int x) {
  /* First x in the below expression is for the case when x is 0 */
  return x && (!(x & (x - 1)));
}

int load_image_ground(vector<Mat> &ground_image, int &amount_shifts,
                      int &amount_pattern) {
  int period = pow(2, (amount_pattern - 2 * amount_shifts - 2) / 2);

  for (int image_i = amount_shifts * 2 + 2 * log2(period) + 1;
       image_i < amount_shifts * 2 + 2 * log2(period) + 3; image_i++) {

    string image_path = "images/pattern_cam_im" + to_string(image_i) + ".png";
    Mat image = imread(image_path, IMREAD_GRAYSCALE);

    if (image.empty()) {
      cout << "Coud not read ground truth image from filesystem" << endl;
      return -1;
    }
    ground_image.push_back(image);
  }
  return 0;
}

// create gradient image to adjust brightness
int create_gradient(Mat &gradient, Monitor &monitor) {
  gradient = Mat(monitor.size_y, monitor.size_x, CV_32F, Scalar(0));
  for (int r = 0; r < gradient.cols; r++) {
    gradient.col(r) = 1 / monitor.size_x * r;
  }

  int count = 0;
  for (int i = 0; i < gradient.rows; i++) {
    for (int j = 0; j < gradient.cols; j++) {
      if (gradient.at<uchar>(i, j) == 1) {
        count++;
      }
    }
  }
  float white = (float)count / (float)(gradient.rows * gradient.cols);
  cout << white << endl;
  imshow("Gradient", gradient);
  waitKey();

  return 0;
}

// create monoton-color threshold image to adjust camera's gain
int create_threshold_image(Mat &threshold_image, Monitor &monitor,
                           int &threshold_value) {
  if (threshold_value < 100) {
    cout << " The threshold image should be brighter. Suggested: 100 -> 254)"
         << endl;
    return -1;
  } else if (threshold_value > 255) {
    cout << " Wrong threshold value. Suggested: 200 -> 254)" << endl;
    return -1;
  }
  threshold_image =
      Mat(monitor.size_y, monitor.size_x, CV_8UC1, Scalar(threshold_value));
  //    imshow("Threshold", threshold_image);
  //    waitKey();
  return 1;
}

void planeTesting(void) {

  // Point generation
  Point3f P1(0, 0, 100);
  Point3f P2(0, 1, 200);
  Point3f P3(1, 0, 100);
  Point3f P4(1, 1, 200);

  vector<Point3f> points{P1, P2, P3, P4};

  // Create Equation System
  CvMat *res = cvCreateMat(3, 1, CV_32FC1);
  CvMat *matX = cvCreateMat(4, 3, CV_32FC1);
  CvMat *matZ = cvCreateMat(4, 1, CV_32FC1);

  // Matrix generation
  for (auto point_i = 0; point_i < points.size(); ++point_i) {

    cvmSet(matX, point_i, 0, points[point_i].x);
    cvmSet(matX, point_i, 1, points[point_i].y);
    cvmSet(matX, point_i, 2, points[point_i].z);
    cvmSet(matZ, point_i, 0, 1);
  }

  // Solve equation
  cvSolve(matX, matZ, res, CV_SVD);
  double A = cvmGet(res, 0, 0);
  double B = cvmGet(res, 1, 0);
  double C = cvmGet(res, 2, 0);
  double average = (P1.z + P2.z + P3.z + P4.z) / 4.0;

  // Calculate Cross product with average plane
  Mat plane_a = (Mat_<double>(3, 1) << A, B, C);
  Mat plane_b = (Mat_<double>(3, 1) << 0, 0, 1);
  Mat cross = plane_a.cross(plane_b);

  // Get Equation in Parameterform and set x to zero
  vector<double> Plane_A = {B, C, 1};
  vector<double> Plane_B = {0, 1, average};

  // Compute Equation Systen
  Mat matX2 =
      (Mat_<double>(2, 2) << Plane_A[0], Plane_A[1], Plane_B[0], Plane_B[1]);
  Mat matZ2 = (Mat_<double>(2, 1) << Plane_A[2], Plane_B[2]);
  Mat res2 = (Mat_<double>(2, 1) << 0, 0);
  solve(matX2, matZ2, res2);

  // This is line:
  Point3d p0(0, res2.at<double>(0), res2.at<double>(1));
  Point3d vector(cross.at<double>(0), cross.at<double>(1), cross.at<double>(2));

  // This is line in 2d
  Point2d p0_2d(0, res2.at<double>(0));
  Point2d vector_2d(cross.at<double>(0), cross.at<double>(1));
}
