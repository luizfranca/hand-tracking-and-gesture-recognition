/*
 * Camera.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: luizdaniel
 */

#include "Camera.h"

Mat preprocess(Mat original, int minThresh[3], int maxThresh[3]) {

	Mat finalImg;
	Mat imgYCRCB;
	Mat imgChannels[3];

	cvtColor(original, imgYCRCB, CV_BGR2YCrCb);

	split(imgYCRCB, imgChannels);

	for (int i = 0; i < 3; ++i) {
		threshold(imgChannels[i], imgChannels[i], minThresh[i], maxThresh[i], THRESH_BINARY);

	}

	merge(imgChannels, 3, finalImg);

	return finalImg;
}
