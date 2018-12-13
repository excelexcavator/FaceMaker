#pragma once

#include <QTimer> 
#include <QWidget>  
#include <QImage>  
#include <highgui.h> 
#include <cv.h>  
#include <dlib/opencv.h>  
#include <opencv2/opencv.hpp>  
#include "ui_mainwindow.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include "dlib/statistics/statistics.h"
#include <deque>
using namespace dlib;

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = Q_NULLPTR);

private slots:
	void button1();
	void button2();
	void button3();
	void button4();
	void button5();
	void slider1();
	void slider2();

public slots:
	void opencamera();
	void closecamera();
	void readcamera();

private:
	Ui::mainwindowClass ui;
	QTimer *timer;
	cv::VideoCapture cap;
	//IplImage *frame;

public:
	shape_predictor pose_model;
	frontal_face_detector detector;
	double hue;
	double sat;
	int offset;
};
