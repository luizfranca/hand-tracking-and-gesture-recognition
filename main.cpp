/*
 * main.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: luizdaniel
 */

#include <time.h>

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Camera.h"
#include "Detection.h"

using namespace std;
using namespace cv;

int minY = 54;
int maxY = 163;

int minCr = 131;
int maxCr = 157;

int minCb = 110;
int maxCb = 135;

int morph_size = 120;

int lowThreshold = 80;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


int main() {
	cout << "Hand Tracking and gesture Recognition" << endl;

	namedWindow("image", CV_WINDOW_AUTOSIZE);

	VideoCapture capture(0);

	Mat currFrame;

	Mat background;

//	while(capture.read(background)) {
//
//		flip(background, background, 1);
//
//		imshow("image", background);
//
//		if (waitKey(1) == 27)
//			break;
//	}
//	imwrite("background.png", background);
//	imshow("background", background);

//	qimage", &maxCb, 255);

	background = imread("background.png");
//	imshow("background", background);

//	morph_size = 5;
	createTrackbar("Threshold:", "image", &morph_size, 255);
//	createTrackbar("lowthreshold:", "image", &lowThreshold, 100);


//		createTrackbar("MinY:", "image", &minY, 255);
//		createTrackbar("MaxY:", "image", &maxY, 255);
//
//		createTrackbar("MinCr:", "image", &minCr, 255);
//		createTrackbar("MaxCr:", "image", &maxCr, 255);
//
//		createTrackbar("MinCb:", "image", &minCb, 255);
//		createTrackbar("MaxCb:", "image", &maxCb, 255);

	while(capture.read(currFrame)) {
		flip(currFrame, currFrame, 1);

		int minThresh[3] = { minY, minCr, minCb };
		int maxThresh[3] = { maxY, maxCr, maxCb };

		Mat preprocessedImage = preprocess(currFrame, minThresh, maxThresh, morph_size, background, lowThreshold);

		imshow("image", preprocessedImage);

		if (waitKey(1) == 27) {
			string img_name = "skin-extraction-" + currentDateTime() + ".png";

			imwrite(img_name, preprocessedImage);
			break;
		}
	}


	return 0;
}

