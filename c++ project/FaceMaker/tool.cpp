#include "tool.h"
#include <QImage>  
#include <dlib/opencv.h>  
#include <opencv2/opencv.hpp>  
#include <dlib/image_processing/frontal_face_detector.h>  
#include <dlib/image_processing/render_face_detections.h>  
#include <dlib/image_processing.h>  
#include <dlib/gui_widgets.h>  
#include "dlib/statistics/statistics.h"
#include <deque>
#include<stdlib.h>
using namespace dlib;



QImage ConvertToQImage(cv::Mat &mat)
{
	QImage img;
	int nChannel = mat.channels();
	if (nChannel == 3)
	{
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		img = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_RGB888);
	}
	else if (nChannel == 4 || nChannel == 1)
	{
		img = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_ARGB32);
	}

	return img;
}

QImage ConvertToQImage(IplImage *iplImg)
{
	QImage img;
	int nChannel = iplImg->nChannels;
	if (nChannel == 3)
	{
		cvConvertImage(iplImg, iplImg, CV_CVTIMG_SWAP_RB);
		img = QImage((const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_RGB888);
	}
	else if (nChannel == 4 || nChannel == 1)
	{
		img = QImage((const unsigned char*)iplImg->imageData, iplImg->width, iplImg->height, QImage::Format_ARGB32);
	}

	return img;
}

cv::Mat EndAdj(cv::Mat temp, frontal_face_detector detector, shape_predictor pose_model, int offset)
{
	cv_image<bgr_pixel> cimg(temp);

	// Detect faces   
	std::vector<rectangle> faces = detector(cimg);
	// Find the pose of each face.  
	std::vector<full_object_detection> shapes;
	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	cv::Mat im1;
	temp.copyTo(im1);

	//眉脚整形  左眼17-18-19 y0 右眼24-25-26 y5
	cv::Mat imo;
	temp.copyTo(imo);
	int y[6], len[6];
	if (!shapes.empty()) {//画点
		for (int i = 0; i < 68; i++) {
			temp.at<cv::Vec3b>(shapes[0].part(i).y(), shapes[0].part(i).x()) = cv::Vec3b(0, 0, 255);
			//  shapes[0].part(i).x();  
		}

		for (int i = 0; i < 3; i++)
		{
			//17-21左眼上部分  22-26右眼上部分
			len[i] = int((shapes[0].part(17 + i + 1).x() - shapes[0].part(17 + i).x())*1.1);
			y[i] = shapes[0].part(17 + i + 1).y() + len[i];
		}

		for (int i = 0; i < 3; i++)
		{
			len[i + 3] = int((shapes[0].part(22 + i + 1).x() - shapes[0].part(22 + i).x())*1.1);
			y[i + 3] = shapes[0].part(22 + i + 1).y() + len[i + 3];
		}

		for (int i = 0; i < 3; i++) {
			temp.at < cv::Vec3b>(y[i], shapes[0].part(18 + i).x()) = cv::Vec3b(0, 0, 255);
			//  shapes[0].part(i).x();  
		}
		for (int i = 0; i < 3; i++) {
			temp.at<cv::Vec3b>(y[i + 3], shapes[0].part(23 + i).x()) = cv::Vec3b(0, 0, 255);
			//  shapes[0].part(i).x();  
		}
	}

	//offset是偏移量
	if (!shapes.empty() && offset != 0) {
		//左眼区域
		cv::line(temp, cvPoint(shapes[0].part(17).x(), shapes[0].part(17).y()), cvPoint(shapes[0].part(18).x(), shapes[0].part(18).y()), cv::Scalar(0, 0, 255));
		cv::line(temp, cvPoint(shapes[0].part(18).x(), shapes[0].part(18).y()), cvPoint(shapes[0].part(19).x(), shapes[0].part(19).y()), cv::Scalar(0, 0, 255));
		cv::line(temp, cvPoint(shapes[0].part(17).x(), shapes[0].part(17).y()), cvPoint(shapes[0].part(18).x(), y[0]), cv::Scalar(0, 0, 255));
		cv::line(temp, cvPoint(shapes[0].part(18).x(), y[0]), cvPoint(shapes[0].part(19).x(), y[1]), cv::Scalar(0, 0, 255));
		//右眼区域
		cv::line(temp, cvPoint(shapes[0].part(25).x(), shapes[0].part(25).y()), cvPoint(shapes[0].part(26).x(), shapes[0].part(26).y()), cv::Scalar(0, 0, 255));
		cv::line(temp, cvPoint(shapes[0].part(24).x(), shapes[0].part(24).y()), cvPoint(shapes[0].part(25).x(), shapes[0].part(25).y()), cv::Scalar(0, 0, 255));
		cv::line(temp, cvPoint(shapes[0].part(26).x(), shapes[0].part(26).y()), cvPoint(shapes[0].part(25).x(), y[5]), cv::Scalar(0, 0, 255));
		cv::line(temp, cvPoint(shapes[0].part(25).x(), y[5]), cvPoint(shapes[0].part(24).x(), y[4]), cv::Scalar(0, 0, 255));

		//左眼以37为界，右眼以44为界
		int leftlow = (shapes[0].part(37).y() + shapes[0].part(17).y()) / 2;
		int rightlow = (shapes[0].part(44).y() + shapes[0].part(26).y()) / 2;
		temp.at<cv::Vec3b>(leftlow, shapes[0].part(37).x()) = cv::Vec3b(0, 0, 255);
		temp.at<cv::Vec3b>(rightlow, shapes[0].part(37).x()) = cv::Vec3b(0, 0, 255);

		//角点上升两倍，旁边上升一倍
		//左眉从x[17]-x[19],y:lestlow到第二根红线
		//在imo上画图，上挑斜率是（xlen-i)/xlen*offset
		int num = 1;
		int xlen = shapes[0].part(19).x() - shapes[0].part(17).x();
		//cout << xlen << endl;
		for (int i = 2; i<xlen; i++) {
			for (int j = 0; num != 2 && j<50; j++) {

				if (num == 0 && temp.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 1;
					imo.at < cv::Vec3b >(leftlow - j - 2, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow, shapes[0].part(17).x() + i);
					continue;
				}

				if (num == 1 && temp.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 2;

				}
				if (num == 1) {
					imo.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow, shapes[0].part(17).x() + i);
					imo.at < cv::Vec3b >(leftlow - j - 2, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow, shapes[0].part(17).x() + i);
					imo.at < cv::Vec3b >(leftlow - j - 3, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow, shapes[0].part(17).x() + i);
					imo.at < cv::Vec3b >(leftlow - j - 4, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow, shapes[0].part(17).x() + i);
				}
			}
			num = 0;
		}

		for (int i = 2; i<xlen; i++) {
			int left_offset = offset - double(i*offset / xlen);
			for (int j = 0; num != 2 && j<50; j++) {

				if (num == 0 && temp.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 1;
					imo.at< cv::Vec3b >(leftlow - j - 1 - left_offset, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i);
					continue;
				}

				if (num == 1 && temp.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 2;

				}
				if (num == 1) {
					imo.at< cv::Vec3b >(leftlow - j - 1 - left_offset, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i);
					//imo.at < cv::Vec3b >(leftlow - j - 1, shapes[0].part(17).x() + i) = im1.at < cv::Vec3b >(leftlow, shapes[0].part(17).x() + i);
					//cout << 2 << endl;
				}
			}
			num = 0;
		}
		//右眼
		//在imo上画图，上挑斜率是（xlen-i)/xlen*offset

		xlen = shapes[0].part(26).x() - shapes[0].part(24).x();
		//cout << xlen << endl;
		for (int i = 2; i<xlen; i++) {

			for (int j = 0; num != 2 && j<50; j++) {

				if (num == 0 && temp.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 1;
					imo.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 2, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 3, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 4, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 5, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 6, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					continue;
				}

				if (num == 1 && temp.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 2;

				}
				if (num == 1) {
					imo.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 2, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 3, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					imo.at < cv::Vec3b >(rightlow - j - 4, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow, shapes[0].part(24).x() + i);
					//cout << 2 << endl;
				}
			}
			num = 0;
		}

		for (int i = 2; i<xlen; i++) {
			int right_offset = double(i*offset / xlen);
			for (int j = 0; num != 2 && j<50; j++) {
				if (num == 0 && temp.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 1;
					imo.at< cv::Vec3b >(rightlow - j - 1 - right_offset, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i);
					continue;
				}

				if (num == 1 && temp.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i) == cv::Vec3b(0, 0, 255))
				{
					num = 2;

				}
				if (num == 1) {
					imo.at< cv::Vec3b >(rightlow - j - 1 - right_offset, shapes[0].part(24).x() + i) = im1.at < cv::Vec3b >(rightlow - j - 1, shapes[0].part(24).x() + i);
				}
			}
			num = 0;
		}


	}
	return imo;
}

double hsl2RGB(double p, double q, double h) {
	if (h < 0) h += 1;
	if (h > 1) h -= 1;
	if (6 * h < 1) return p + (q - p) * 6.0 * h;
	if (2 * h < 1) return q;
	if (3 * h < 2) return p + (q - p) * 6.0 * ((2.0 / 3.0) - h);
	return p;
}

double GBR2HSL2GBR(int G, int B, int R, double change, double sat, double my[3])
{
	double GBR[3] = { double(G + 1) / 256, double(B + 1) / 256, double(R + 1) / 256 };
	double max = *std::max_element(GBR, GBR + 2);
	double min = *std::min_element(GBR, GBR + 2);
	double h = 0, s = 0, l = 0;

	// GBR2HSL
	l = (max + min) / 2.0;
	if (max == min || l == 0) s = 0;
	else if (l > 0 && l < 1.0 / 2.0) s = (max - min) / 2.0 / l;
	else if (l > 1.0 / 2.0 && l < 1.0) s = (max - min) / (2.0 - 2.0 * l);
	h = change; // change color
				//s = (1.1*s < 1) ? (1.1*s) : 1; //enhance hue
	//s = sat;

	// HSL2GBR
	double p, q;
	if (s == 0) {
		my[0] = l * 256.0 - 1;
		my[1] = l * 256.0 - 1;
		my[2] = l * 256.0 - 1;
	}
	else {
		(l < 0.5) ? (q = l * (1 + s)) : (q = (l + s) - (l * s));
		p = 2.0 * l - q;

		my[0] = -1 + 256.0 * hsl2RGB(p, q, h - (1.0 / 3.0));	// B
		my[1] = -1 + 256.0 * hsl2RGB(p, q, h);					// G
		my[2] = -1 + 256.0 * hsl2RGB(p, q, h + (1.0 / 3.0));	// R
	}

	return *my;
}

void find_eyebrow(std::vector<full_object_detection> shapes, cv::Mat temp, int L_eb[2][8], int R_eb[2][8]) {
	//using the shapes we got, we can find the nodes under eyebrows and draw points.
	int len[6];
	for (int i = 0; i < 5; i++) {
		L_eb[0][i] = shapes[0].part(i + 17).x();
		L_eb[1][i] = shapes[0].part(i + 17).y();
		//circle(temp, cvPoint(L_eb[0][i], L_eb[1][i]), 1, cv::Scalar(0, 0, 255), -1);
		R_eb[0][i] = shapes[0].part(i + 22).x();
		R_eb[1][i] = shapes[0].part(i + 22).y();
		//circle(temp, cvPoint(R_eb[0][i], R_eb[1][i]), 1, cv::Scalar(0, 0, 255), -1);
	}// record five nodes above eyebrows

	for (int i = 0; i < 3; i++) {
		len[i] = int((shapes[0].part(21 - i).x() - shapes[0].part(20 - i).x())*0.7);
		L_eb[0][i + 5] = L_eb[0][i + 1];
		L_eb[1][i + 5] = (L_eb[1][i + 1] + len[i]) == L_eb[1][i + 4] ? L_eb[1][i + 1] + len[i] - 1 : L_eb[1][i + 1] + len[i];
		//circle(temp, cvPoint(L_eb[0][i + 5], L_eb[1][i + 5]), 1, cv::Scalar(0, 0, 255), -1);
		len[i + 3] = int((shapes[0].part(23 + i).x() - shapes[0].part(22 + i).x())*0.7);
		R_eb[0][i + 5] = R_eb[0][i + 1];
		R_eb[1][i + 5] = (R_eb[1][i + 1] + len[i]) == R_eb[1][i + 4] ? R_eb[1][i + 1] + len[i] - 1 : R_eb[1][i + 1] + len[i];
		//circle(temp, cvPoint(R_eb[0][i + 5], R_eb[1][i + 5]), 1, cv::Scalar(0, 0, 255), -1);
	}// rewrite mxj's code of finding three nodes under eyebrows

}

void draw_eyebrow(cv::Mat temp, int eb[2][8], double hue, double saturation) {
	for (int y = *std::min_element(eb[1], eb[1] + 8); y < *std::max_element(eb[1], eb[1] + 8); y++) {
		for (int x = eb[0][0]; x < eb[0][4]; x++) {
			// if the pixel in the region, change its color
			if (double(x - eb[0][0]) * (eb[1][1] - eb[1][0]) <= double(y - eb[1][0]) * (eb[0][1] - eb[0][0]) &&
				double(x - eb[0][1]) * (eb[1][2] - eb[1][1]) <= double(y - eb[1][1]) * (eb[0][2] - eb[0][1]) &&
				double(x - eb[0][2]) * (eb[1][3] - eb[1][2]) <= double(y - eb[1][2]) * (eb[0][3] - eb[0][2]) &&
				double(x - eb[0][3]) * (eb[1][4] - eb[1][3]) <= double(y - eb[1][3]) * (eb[0][4] - eb[0][3]) && !(
					double(x - eb[0][5]) * (eb[1][6] - eb[1][5]) <= double(y - eb[1][5]) * (eb[0][6] - eb[0][5]) &&
					double(x - eb[0][6]) * (eb[1][7] - eb[1][6]) <= double(y - eb[1][6]) * (eb[0][7] - eb[0][6])) && !(
						double(x - eb[0][0]) * (eb[1][5] - eb[1][0]) <= double(y - eb[1][0]) * (eb[0][5] - eb[0][0]) &&
						double(x - eb[0][7]) * (eb[1][4] - eb[1][7]) <= double(y - eb[1][7]) * (eb[0][4] - eb[0][7]))
				) {
				cv::Vec3b color = temp.at<cv::Vec3b>(y, x); //original color
				double my[3];
				GBR2HSL2GBR(color[0], color[1], color[2], hue, saturation, my); //change its hue
				temp.at<cv::Vec3b>(y, x) = cv::Vec3b(int(my[0]), int(my[1]), int(my[2])); //put back the pixel
			}
		}
	}
}

void draw_eyebrow(cv::Mat temp, int eb[2][8], int B, int G, int R) {
	for (int y = *std::min_element(eb[1], eb[1] + 8); y < *std::max_element(eb[1], eb[1] + 8); y++) {
		for (int x = eb[0][0]; x < eb[0][4]; x++) {
			// if the pixel in the region, change its color
			if (double(x - eb[0][0]) * (eb[1][1] - eb[1][0]) <= double(y - eb[1][0]) * (eb[0][1] - eb[0][0]) &&
				double(x - eb[0][1]) * (eb[1][2] - eb[1][1]) <= double(y - eb[1][1]) * (eb[0][2] - eb[0][1]) &&
				double(x - eb[0][2]) * (eb[1][3] - eb[1][2]) <= double(y - eb[1][2]) * (eb[0][3] - eb[0][2]) &&
				double(x - eb[0][3]) * (eb[1][4] - eb[1][3]) <= double(y - eb[1][3]) * (eb[0][4] - eb[0][3]) && !(
					double(x - eb[0][5]) * (eb[1][6] - eb[1][5]) <= double(y - eb[1][5]) * (eb[0][6] - eb[0][5]) &&
					double(x - eb[0][6]) * (eb[1][7] - eb[1][6]) <= double(y - eb[1][6]) * (eb[0][7] - eb[0][6])) && !(
						double(x - eb[0][0]) * (eb[1][5] - eb[1][0]) <= double(y - eb[1][0]) * (eb[0][5] - eb[0][0]) &&
						double(x - eb[0][7]) * (eb[1][4] - eb[1][7]) <= double(y - eb[1][7]) * (eb[0][4] - eb[0][7]))
				)
			{
				temp.at<cv::Vec3b>(y, x) = cv::Vec3b(B, G, R); //change the color
			}
		}
	}
}

cv::Mat ColorAdj(cv::Mat temp, frontal_face_detector detector, shape_predictor pose_model, double colorhsl, double saturation)
{
	cv_image<bgr_pixel> cimg(temp);

	// Detect faces   
	std::vector<rectangle> faces = detector(cimg);
	// Find the pose of each face.  
	std::vector<full_object_detection> shapes;
	for (unsigned long i = 0; i < faces.size(); ++i)
		shapes.push_back(pose_model(cimg, faces[i]));

	if (!shapes.empty()) {
		int L_eb[2][8], R_eb[2][8];					//locations of Left eyebrow and Right eyebrow
		find_eyebrow(shapes, temp, L_eb, R_eb);		//find the locations of Left eyebrow and Right eyebrow
		draw_eyebrow(temp, L_eb, colorhsl, saturation);
		draw_eyebrow(temp, R_eb, colorhsl, saturation);
	}

	return temp;
}