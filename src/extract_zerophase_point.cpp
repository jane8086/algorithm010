#include <stdio.h>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "tools.h"
#include <iostream>

//int find_minimal_phase_edge(Mat &dst, int row, int col,bool vertical)
//{
//    if (vertical) {
//        int minus = col;
//        int plus = col;
//        for (int i=1;i<2;i++) {
//            if (((int)dst.at<uchar>(row,col-i) < (int)dst.at<uchar>(row,minus))) {
//                minus = col-i;
//            }
//            if (((int)dst.at<uchar>(row,col+i) < (int)dst.at<uchar>(row,plus))) {
//                plus = col+i;
//            }
//        }
//        if (minus == col && plus == col)
//        {
//            return col;
//        }
//        if ((int)dst.at<uchar>(row,minus) <= (int)dst.at<uchar>(row,plus)) {
//            return minus;
//        }
//        else{
//            return plus;
//        }
//    }
//}

int detect_edge_phase_vertical(Mat &relative, Mat &frame, Mat &edge_map)
{
    if (relative.empty())
    {
        cout << "Can't load relative phase" << endl;
        return -1;
    }

    vector<vector<Point>> contour;

    // convert relative phase and reduce noise
    Mat dst = Mat::zeros(relative.size(), CV_8U);
    relative.convertTo(dst,CV_8U);
    GaussianBlur(dst,dst,Size(3,3),0,0, BORDER_REPLICATE);
    Mat thres(dst.rows,dst.cols,CV_8U,Scalar(10));
    dst = dst + thres;
    imshow("Phase", dst);
    waitKey();

    Mat detect_edge = dst.clone();

    // Canny edge detection
    int edgeThresh = 1;
    int lowThreshold = 255;
    int maxlowThreshold =300;
    int kernel_size = 3;
    Canny(dst,detect_edge,lowThreshold,maxlowThreshold, kernel_size);
    threshold(detect_edge,detect_edge,40,1,THRESH_BINARY);
    bitwise_and(detect_edge,frame,detect_edge);
    imshow("Ori Edge",detect_edge*255);
    waitKey();
//    Mat old_edge = detect_edge.clone();
    for (int i = 0; i < detect_edge.rows; i++) {
        for (int j = 0; j < detect_edge.cols; j++) {
            if (detect_edge.at<uchar>(i,j) == 1) {
                // dummy test
//                detect_edge.at<uchar>(i,j-1) = 0;
//                detect_edge.at<uchar>(i,j-1) = 0;
//                detect_edge.at<uchar>(i,j-2) = 0;
//                detect_edge.at<uchar>(i,j-2) = 0;
                if ((int)dst.at<char>(i,j) > 60) {
//                    cout << (int)dst.at<uchar>(i,j) << "     ";
//                    int min = find_minimal_phase_edge(dst,i,j,true);
//                    cout << "min"<< abs(min-j) << endl;
//                    if (min != j) {
//                        detect_edge.at<uchar>(i,j)=0;
//                        detect_edge.at<uchar>(i,min)=1;
//                        cout << (int)dst.at<uchar>(i,min) << endl;
//                    }
                    int n = j;
                    while (n > j + 5)
                    {
                        if (dst.at<uchar>(i,n) < 10)
                        {
                            detect_edge.at<uchar>(i,n) =1;
                            detect_edge.at<uchar>(i,j) =0;
                            break;
                        }
                        else
                        {
                            n--;
                        }
                    }
                }
            }
        }
    }
    imshow("New Edge", detect_edge*255);
    waitKey();
//    for (int i = 0; i < detect_edge.rows; i++) {
//        for (int j = 0; j < detect_edge.cols; j++) {
//            if (detect_edge.at<uchar>(i,j) != old_edge.at<uchar>(i,j)) {
//                cout << "row" << i << "col" << j << endl;
//            }
//        }
//    }
//     imshow("Wrongpoint", old_edge*255);
//    Mat houghline = Mat(dst.rows, dst.cols, CV_8U, Scalar(0));
//    vector<Vec4i> lines;
//    HoughLinesP( detect_edge, lines, 1, CV_PI/180, 1, 1, 5 );
//    for( size_t i = 0; i < lines.size(); i++ )
//    {
//        line( houghline, Point(lines[i][0], lines[i][1]),
//            Point(lines[i][2], lines[i][3]), Scalar(255),1,4);
//    }
//    namedWindow( "Detected Lines", 1 );
//    imshow( "Detected Lines", houghline);

//    waitKey(0);

//    edge_map = houghline.clone();

    edge_map = detect_edge.clone();
    return 0;
}

int detect_edge_phase_horizontal(Mat &relative, Mat &frame, Mat &edge_map)
{
    if (relative.empty())
    {
        cout << "Can't load relative phase" << endl;
        return -1;
    }

    vector<vector<Point>> contour;

    // convert relative phase and reduce noise
    Mat dst = Mat::zeros(relative.size(), CV_8U);
    relative.convertTo(dst,CV_8U);
    GaussianBlur(dst,dst,Size(3,3),0,0, BORDER_REPLICATE);
    Mat thres(dst.rows,dst.cols,CV_8U,Scalar(0));
    dst = dst + thres;
    imshow("Phase", dst);
    waitKey();

    Mat detect_edge = dst.clone();

    // Canny edge detection
    int edgeThresh = 1;
    int lowThreshold = 255;
    int maxlowThreshold = 300;
    int kernel_size = 3;
    Canny(dst,detect_edge,lowThreshold,maxlowThreshold, kernel_size);
    threshold(detect_edge,detect_edge,40,1,THRESH_BINARY);
    bitwise_and(detect_edge,frame,detect_edge);
    for (int i = 0; i < detect_edge.rows; i++)
    {
        for (int j = 0; j < detect_edge.cols; j++)
        {
            if (detect_edge.at<uchar>(i,j) == 1)
            {
                if (dst.at<char>(i,j) > 50)
                {
                    int n = i;
                    while (n > i -5)
                    {
                        if (dst.at<uchar>(n,j) < 10)
                        {
                            detect_edge.at<uchar>(n,j) =1;
                            detect_edge.at<uchar>(i,j) =0;
                            break;
                        }
                        else
                        {
                            n--;
                        }
                    }
                }
            }
        }
    }
    imshow("Edge", detect_edge*255);
    waitKey();
//    Mat houghline = Mat(dst.rows, dst.cols, CV_8U, Scalar(0));
//    vector<Vec4i> lines;
//    HoughLinesP( detect_edge, lines, 1, CV_PI/180, 1, 1, 5 );
//    for( size_t i = 0; i < lines.size(); i++ )
//    {
//        line( houghline, Point(lines[i][0], lines[i][1]),
//            Point(lines[i][2], lines[i][3]), Scalar(255),1,4);
//    }
//    namedWindow( "Detected Lines", 1 );
//    imshow( "Detected Lines", houghline);

//    waitKey(0);

//    edge_map = houghline.clone();

    edge_map = detect_edge.clone();
    return 0;
}


int correct_period_vertical(Mat &extract_point, Mat &period_number_vertical)
{
    for (int row = 0; row < extract_point.rows; row++)
    {
        for (int col = 0; col < extract_point.cols; col++)
        {
            if (extract_point.at<uchar>(row,col) == 1)
            {

                float count = 0;
                float sum = 0;
                for (int i = row-3; i < row+3; i++)
                {
                    for (int j = col-10; j < col-2; j++)
                    {
                        sum = sum + period_number_vertical.at<uchar>(i,j);
                        count++;
                    }
                }
                int period = round(sum/count);
//                cout << period << " ";
                if (((int)period_number_vertical.at<uchar>(row,col) - period < 1))
                {
                    period_number_vertical.at<uchar>(row,col) = period+1;
//                    cout << " Corect:" << (int)period_number_vertical.at<uchar>(row,col) << endl;
                }
            }
        }
    }
    return 0;

}

int correct_period_horizontal(Mat &extract_point, Mat &period_number_horizontal)
{
    for (int row = 0; row < extract_point.rows; row++)
    {
        for (int col = 0; col < extract_point.cols; col++)
        {
            if (extract_point.at<uchar>(row,col) == 1)
            {

                float count = 0;
                float sum = 0;
                for (int i = row-7; i < row-2; i++)
                {
                    for (int j = col-3; j < col+3; j++)
                    {
                        sum = sum + period_number_horizontal.at<uchar>(i,j);
                        count++;
                    }
                }
                int period = round(sum/count);
//                cout << period << " ";
                if (((int)period_number_horizontal.at<uchar>(row,col) - period < 1))
                {
                    period_number_horizontal.at<uchar>(row,col) = period+1;
//                    cout << " Corect:" << (int)period_number_horizontal.at<uchar>(row,col) << endl;
                }
            }
        }
    }
    return 0;

}

