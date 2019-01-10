#ifndef PHASES_H
#define PHASES_H

#include "include/monitor.h"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

/** @brief Calculates two absolut phasemaps vertical and horizontal
 *  @param a pixel resolution in width.
 *
 */
Mat calculate_absolute_phase(Mat &relative_phase, Mat &period_number);
/** @brief Calculates absolute and relative phasemaps
 *  @param a pixel resolution in width.
 *
 */

int calculate_all_phasemaps(vector<Mat> &absolute_phasemaps,
                            vector<Mat> &relative_phasemaps, Mat &screen,
                            int amount_phaseshifts, int amount_patterns,
                            int color_patterns,
                            int novel_method); // flags as ENUM!!!!!!!!!!!!
Mat calculate_relative_phase_general(vector<Mat> &patterns);
Mat calculate_absolute_phase_novel(Mat &relative_phase, Mat &novel,
                                   int period_sum);
int calculate_realWorld_3d_coordinates(vector<Point3f> &points_world,
                                       vector<Point2f> &points_world_pixel,
                                       vector<Point2f> &points_image,
                                       Mat &absolutephasemap_hor,
                                       Mat &absolutephasemap_ver,
                                       Monitor &monitor, int &periods);
Mat calculate_relative_phase(vector<Mat> &patterns);
int calculate_absolute_phasemaps(vector<Mat> &absolute_phasemaps, Mat &screen,
                                 int &amount_phaseshifts, int amount_patterns,
                                 int &color_patterns, int &novel_method);
/** @brief Transforms the display pixels into 3D coordinates in mm for
 * calibration
 *
 */
void calculate_realWorld_3d_coordinates(const vector<Point2f> &display_points,
                                        const Monitor &monitor,
                                        vector<Point3f> &points_world_mm);

/** @brief Calculates point correspondeces between the image and display pixels
 *
 */
void calculate_display_coordinates(vector<Point2f> &points_display,
                                   vector<Point2f> &points_image,
                                   Mat &absolutephasemap_hor,
                                   Mat &absolutephasemap_ver, Monitor &monitor,
                                   int periods, Mat &screen);

Mat calculate_relative_phase_general(vector<Mat> &patterns);

/** @brief Calculates point correspondeces between the image and display pixels
 * where the vertical and hoirzontal phase is the same
 * @param phase_stepsize Stepsize between 0 and 360 degree. If stepsize = 10,
 * Every point is selected where relative phase equals 0, 10, 20 ... 360
 *
 */
void calculate_display_coordinates_on_relative_phasegrid(
    vector<Point2f> &points_display, vector<Point2f> &points_image,
    Mat &absolutephasemap_hor, Mat &absolutephasemap_ver,
    const vector<Mat> &relative_phasemaps, Monitor &monitor, Mat &screen,
    int periods, const double phase_stepsize);

#endif // PHASES_H
