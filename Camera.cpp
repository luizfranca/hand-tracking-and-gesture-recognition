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

	for (int i = 0; i < 3; ++i) {
		threshold(imgChannels[i], imgChannels[i], minThresh[i], maxThresh[i], THRESH_BINARY);

		morphologyEx(imgChannels[i], imgChannels[i], MORPH_OPEN, element);
	}

	merge(imgChannels, 3, finalImage);

	morphologyEx(finalImage, finalImage, MORPH_OPEN, element);

	finalImage = finalImage & imgYCRCB;

	return finalImage;
}

Mat faceDetection(Mat original) {

	Mat image;
	Mat output, mask;

	cvtColor(original, image, CV_BGR2GRAY);

	equalizeHist(image, image);

	CascadeClassifier faceCascade;

	faceCascade.load("haarcascade_frontalface_default.xml");

	vector<Rect> faces;
	faceCascade.detectMultiScale(image, faces);

	uchar fillValue = 128;
//	Mat output;
//	floodFill(image, Point(0, 0), cv::Scalar(255) ,0, cv::Scalar(), cv::Scalar(), 4 | cv::FLOODFILL_MASK_ONLY | (fillValue << 8));


//	cvtColor(image, output, CV_GRAY2BGR);
//
//	for (int i = 0; i < faces.size(); ++i) {
//		rectangle(output, faces[i], Scalar(0, 0, 255));
//
//		Mat faceROI(image, faces[i]);
//	}

	return output;
}

Mat preprocess(Mat original, int minThresh[3], int maxThresh[3], int morph_size) {

	Mat bgSub;
	Mat imgYCRCB;

	Mat finalImg;

	cvtColor(original, imgYCRCB, CV_BGR2YCrCb);

	bgSub = backgroundSubtraction(imgYCRCB, minThresh, maxThresh, morph_size);

//	finalImg = faceDetection(original);

	return bgSub;
//	return finalImg;
}
