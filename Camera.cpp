/*
 * Camera.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: luizdaniel
 */

#include "Camera.h"

Mat backgroundSubtraction(Mat imgYCRCB, int minThresh[3], int maxThresh[3], int morph_size) {

	Mat finalImage;
	Mat imgChannels[3];

	split(imgYCRCB, imgChannels);

	Mat element = getStructuringElement( 1, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );

//	int morph_size = 15;

	for (int i = 0; i < 3; ++i) {
		threshold(imgChannels[i], imgChannels[i], minThresh[i], maxThresh[i], THRESH_BINARY);

		morphologyEx(imgChannels[i], imgChannels[i], MORPH_OPEN, element);
	}

	merge(imgChannels, 3, finalImage);

	morphologyEx(finalImage, finalImage, MORPH_OPEN, element);

	finalImage = finalImage & imgYCRCB;

	return finalImage;
}

Mat preprocess(Mat original, int minThresh[3], int maxThresh[3], int morph_size) {

	Mat finalImg;
	Mat imgYCRCB;


	cvtColor(original, imgYCRCB, CV_BGR2YCrCb);

	finalImg = backgroundSubtraction(imgYCRCB, minThresh, maxThresh, morph_size);

	return finalImg;
}
