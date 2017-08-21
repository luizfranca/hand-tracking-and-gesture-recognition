/*
 * Camera.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: luizdaniel
 */

#include "Camera.h"

Mat backgroundSubtraction(Mat imgYCRCB, Mat bgYCRCB, int thresh) {

	Mat img = bgYCRCB - imgYCRCB;

	Mat frameChannels[3];
	Mat BGChannels[3];
	split(img, frameChannels);

	// Chooses how we erode and dilate
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));

	for (int i = 0; i < 3; i++) {
		threshold(frameChannels[i], frameChannels[i], thresh, 255, THRESH_BINARY);

		// Runs pixel erosion and dilation for three iterations
		morphologyEx(frameChannels[i], frameChannels[i], MORPH_OPEN, element, Point(-1, -1), 3);
	}

	// Merge the channels back together
	Mat merged;
	merge(frameChannels, 3, merged);
	merged = merged & imgYCRCB;
	return merged;
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

	return output;
}

Mat preprocess(Mat original, int minThresh[3], int maxThresh[3], int morph_size, Mat background) {

	Mat bgYCRCB;

	cvtColor(background, bgYCRCB, CV_BGR2YCrCb);

	const Scalar min_YCrCb = Scalar(0, 133, 77);
	const Scalar max_YCrCb = Scalar(255, 173, 127);
	Mat frame = original.clone();
	Mat frameGray;
	Mat frameHist;
	Mat output, mask;
	Mat _bg = background;

//	cvtColor(original, frameGray, CV_BGR2GRAY);
////
//	equalizeHist(frameGray, frameHist);
//
//	CascadeClassifier faceCascade;
//
//	faceCascade.load("haarcascade_frontalface_default.xml");
//
//	vector<Rect> faces;
//	faceCascade.detectMultiScale(frameHist, faces);

	// detect faces
	cvtColor(frame, frame, CV_BGR2YCrCb);

//	// Copy the raw image for debugging purposes
	Mat raw = frame.clone();

//	GaussianBlur(_bg, _bg, Size(7,7), 1.8, 1.8);
//	GaussianBlur(frame, frame, Size(7,7), 1.8, 1.8);


	Mat term1 = frame - _bg;

	threshold(term1, term1, 90, 255, THRESH_BINARY);

	return backgroundSubtraction(frame, bgYCRCB, morph_size);



//	frame = backgroundSubtraction(frame, bgYCRCB, minThresh, maxThresh, morph_size);

//	frame = thresholdFilter(frame);

	// Run another pixel erosion and dilation on this function
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(frame, frame, MORPH_OPEN, element, Point(-1, -1), 3);

	// And the thresholded image with the original
	bitwise_and(frame, raw, frame);

	// Convert the frame to grayscale
	cvtColor(frame, frame, CV_YCrCb2BGR);
	cvtColor(frame, frame, CV_BGR2GRAY);

	// Threshold the grayscaled image with Otsu once more
	threshold(frame, frame, 120, 255, THRESH_BINARY);

	// Skin extraction from our member variables
	Mat skinRegion;
	inRange(raw, min_YCrCb, max_YCrCb, skinRegion);

	compare(frame, skinRegion, frame, CMP_EQ);

	// draw a black rectange over each face.
//	for(int i = 0; i < faces.size(); i++) {
//		rectangle(frame, faces[i], Scalar(0, 0, 0), -1, 0, 0);
//	}

	// Finally run a GaussianFilter
	GaussianBlur(frame, frame, Size(7,7), 1.8, 1.8);

	return frame;




//return original;
//	finalImg = faceDetection(original);

//	return bgSub;
//	return finalImg;
}
