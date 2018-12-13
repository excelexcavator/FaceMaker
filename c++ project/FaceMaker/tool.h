#pragma once
#include <QImage>  
#include <dlib/opencv.h>  
#include <opencv2/opencv.hpp>  
#include <dlib/image_processing/frontal_face_detector.h>  
#include <dlib/image_processing/render_face_detections.h>  
#include <dlib/image_processing.h>  
#include <dlib/gui_widgets.h>  
#include "dlib/statistics/statistics.h"
#include <deque>
using namespace dlib;

QImage ConvertToQImage(cv::Mat &mat);

QImage ConvertToQImage(IplImage *iplImg);

cv::Mat EndAdj(cv::Mat temp, frontal_face_detector detector, shape_predictor pose_model, int offset=0);

cv::Mat ColorAdj(cv::Mat temp, frontal_face_detector detector, shape_predictor pose_model, double colorhsl=0, double saturation=0);

double hsl2RGB(double p, double q, double h);

double GBR2HSL2GBR(int G, int B, int R, double change, double sat, double my[3] = { 0, });

void find_eyebrow(std::vector<full_object_detection> shapes, cv::Mat temp, int L_eb[2][8], int R_eb[2][8]);

void draw_eyebrow(cv::Mat temp, int eb[2][8], double hue, double saturation);

void draw_eyebrow(cv::Mat temp, int L_eb[2][8], int B, int G, int R);