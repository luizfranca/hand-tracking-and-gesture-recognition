/*
 * main.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: luizdaniel
 */


#include <iostream>
#include "opencv2/opencv.hpp"
#include "Camera.h"

using namespace std;
using namespace cv;

int minY = 89;
int maxY = 140;

int minCr = 134;
int maxCr = 147;

int minCb = 117;
int maxCb = 127;

int morph_size = 17;

int main() {

	cout << "template" << endl;

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
	createTrackbar("Morph_Size:", "image", &morph_size, 255);


//	while(true) {
//		if (waitKey(1) == 27)
//			break;
//
//	}

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

		Mat preprocessedImage = preprocess(currFrame, minThresh, maxThresh, morph_size, background);

		imshow("image", preprocessedImage);

		if (waitKey(1) == 27)
			break;
	}


	return 0;
}

