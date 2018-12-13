#include "mainwindow.h"
#include "tool.h"
#include<qdialog.h>
#include<qcolordialog.h>
#include<qlabel.h>
#include<QtWidgets/qwidget.h>
#include <QPixmap>  
#include <QImage>  

#include <dlib/opencv.h>  
#include <opencv2/opencv.hpp>  
#include <dlib/image_processing/frontal_face_detector.h>  
#include <dlib/image_processing/render_face_detections.h>  
#include <dlib/image_processing.h>  
#include <dlib/gui_widgets.h>  

using namespace dlib;
using namespace std;


mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	timer = new QTimer(this);
	offset = 0;
	connect(timer, SIGNAL(timeout()), this, SLOT(readcamera()));
}


void mainwindow::button1()
{
	QColor color = QColorDialog::getColor(Qt::red, this, tr("Color map"));
	hue = color.hue() / 359.0;
	sat = color.saturation() / 255.0;
}

void mainwindow::button2()
{
	QSlider *slider = new QSlider(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(20);
	slider->setValue(10);
	slider->setWindowTitle(tr("End Adjustment"));
	slider->setFixedWidth(400);
	slider->show();
	//connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setLineEditValue(int)));
}

void mainwindow::button3()
{
	QSlider *slider = new QSlider(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(20);
	slider->setValue(10);
	slider->setWindowTitle(tr("Shape Adjustment"));
	slider->setFixedWidth(400);
	slider->show();
}

void mainwindow::button4()
{
	QLabel *label = new QLabel(0,Qt::Dialog);
	QFont ft;
	ft.setBold(1);
	ft.setPointSize(13);
	ft.setFamily("Ink Free");
	label->setFont(ft);
	label->setWindowTitle(tr("Developers"));
	label->setText(tr("Boyu Lin            2015011082\n\nShuhao Chang    2015011064\n\nXiaojun Ma         2015011112"));
	label->resize(300, 200);
	//cv::Mat temp = cv::imread(".\test.jpg");
	//QImage img = ConvertToQImage(temp);
	//QPixmap pixmap = QPixmap::fromImage(img);
	//label->setPixmap(pixmap);
	label->show();
}

void mainwindow::button5()
{
	hue = 0;
	sat = 0;
	ui.endadj->setValue(0);
	ui.shapeadj->setValue(0);
}
void mainwindow::slider1()
{
	offset = ui.endadj->value();
}
void mainwindow::slider2()
{

}
void mainwindow::opencamera()
{
	//cv::VideoCapture cap(0);
	cap.open(0);
	detector = get_frontal_face_detector();
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	timer->start(100);
}

void mainwindow::readcamera()
{
	cv::Mat temp;
	cap.grab();
	cap.read(temp);
	temp = ColorAdj(temp, detector, pose_model, hue, sat);
	temp=EndAdj(temp, detector, pose_model, offset);
	QImage img = ConvertToQImage(temp);
	QPixmap pixmap = QPixmap::fromImage(img);
	QPixmap pixmap_fit = pixmap.scaled(ui.Facelabel->width(), ui.Facelabel->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui.Facelabel->setPixmap(pixmap_fit);
	ui.Facelabel->show();
}

void mainwindow::closecamera()
{
	timer->stop();
	cap.release();
}