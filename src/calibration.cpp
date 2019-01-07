#include "include/calibration.h"
#include "include/tools.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int chose_random(const vector<Point2f> &camera_points,
                 const vector<Point3f> &world_points,
                 vector<vector<Point2f>> &camera,
                 vector<vector<Point3f>> &world, int amount) {

  int interval = camera_points.size();
  int random = 0;
  srand(time(NULL));
  for (int point_i = 0; point_i < amount; point_i++) {

    random = rand() % interval;
    world[0].push_back(world_points[random]);
    camera[0].push_back(camera_points[random]);
  }

  return 0;
}

int create_points_subset(const vector<Point2f> &camera_points,
                         const vector<Point3f> &world_points,
                         vector<vector<Point2f>> &camera,
                         vector<vector<Point3f>> &world, PointSubset method) {
  switch (method) {
  case PointSubset::Random_500:
    chose_random(camera_points, world_points, camera, world, 500);
    break;
  case PointSubset::Random_1000:
    chose_random(camera_points, world_points, camera, world, 1000);
    break;
  case PointSubset::Random_5000:
    chose_random(camera_points, world_points, camera, world, 5000);
    break;
  case PointSubset::Random_10000:
    chose_random(camera_points, world_points, camera, world, 10000);
    break;

  case PointSubset::Random_50000:
    chose_random(camera_points, world_points, camera, world, 50000);
    break;
  }

  return 0;
}

int calibrationroutine(vector<Point2f> &camera_points,
                       vector<Point3f> &world_points) {

  // Get format for calibration method
  vector<vector<Point2f>> camera(1);
  vector<vector<Point3f>> world(1);
  camera[0] = camera_points;
  world[0] = world_points;

  // Calibrate with fisheye functions
  vector<Mat> rvec;
  vector<Mat> tvec;
  Mat K = (Mat1f(3, 3) << 800.0, 0.0, 644.0, 0., 600.0, 482.0, 0.0, 0.0, 1.0);
  Mat D = Mat::zeros(4, 1, CV_32F);
  Mat distimage = imread("images/pattern_cam_im1.png",
                         IMREAD_GRAYSCALE); // Load first image
  int flag = 0;
  //        flag |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
  //        flag |= cv::fisheye::CALIB_CHECK_COND;
  //        flag |= cv::fisheye::CALIB_FIX_SKEW;
  // calibrate camera
  double reprojectionerror =
      calibrateCamera(world, camera, distimage.size(), K, D, rvec, tvec,
                      CV_CALIB_USE_INTRINSIC_GUESS);
  //---
  cout << "Camera Matrix:" << endl;
  cout << K << endl;
  cout << "distCoefs: " << endl;
  cout << D << endl;
  cout << "ReprojectionError= " << reprojectionerror << endl;
  //--

  // Save used points
  // saveDatayml(camera[0], world[0]);

  // Mat optimal_cameraMatrix = getOptimalNewCameraMatrix(cameraMatrix,
  // distCoeffs, white_screen.size(), 0, Size());

  // save values into yaml
  //---
  // cout << "parameters get saved into the params folder in path" << endl;
  //---

  // Rectify image
  //         Mat rectified_image;
  //         cv::fisheye::undistortImage(distimage,rectified_image,cameraMatrix,distCoeffs);

  //         imshow("Rectified", rectified_image);
  //         waitKey();

  Mat map1, map2, rview;
  Mat I = Mat::eye(3, 3, CV_8U);
  // initUndistortRectifyMap(opt_cameraMatrix, distCoeffs, Mat(), Mat(),
  // distimage.size(), CV_16SC2, map1, map2);  remap(distimage, rview, map1,
  // map2, INTER_LINEAR);

  return 0;
}
