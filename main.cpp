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

	VideoCapture capture(0);

	Mat currFrame;

	namedWindow("image", CV_WINDOW_AUTOSIZE);

	createTrackbar("MinY:", "image", &minY, 255);
	createTrackbar("MaxY:", "image", &maxY, 255);

	createTrackbar("MinCr:", "image", &minCr, 255);
	createTrackbar("MaxCr:", "image", &maxCr, 255);

	createTrackbar("MinCb:", "image", &minCb, 255);
	createTrackbar("MaxCb:", "image", &maxCb, 255);

	createTrackbar("Morph_Size:", "image", &morph_size, 21);


	while(capture.read(currFrame)) {

		int minThresh[3] = { minY, minCr, minCb };
		int maxThresh[3] = { maxY, maxCr, maxCb };

		Mat preprocessedImage = preprocess(currFrame, minThresh, maxThresh, morph_size);

		imshow("image", preprocessedImage);

		waitKey(50);
	}


	return 0;
}

