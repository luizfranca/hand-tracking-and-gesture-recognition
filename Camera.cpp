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

	split(img, frameChannels);

	// Chooses how we erode and dilate
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));

	for (int i = 0; i < 3; i++) {
		threshold(frameChannels[i], frameChannels[i], thresh, 255, THRESH_BINARY);

		// Runs pixel erosion and dilation for three iterations
		morphologyEx(frameChannels[i], frameChannels[i], MORPH_OPEN, element, Point(-1, -1), 3);
//		imshow(i, frameChannels[i]);
	}

	// Merge the channels back together
	Mat merged;

	merge(frameChannels, 3, merged);

	threshold(merged, merged, thresh, 255, THRESH_BINARY);

	morphologyEx(merged, merged, MORPH_OPEN, element, Point(-1, -1), 3);

	merged = merged & imgYCRCB;

//	bitwise_and(merged, imgYCRCB, merged);

	return merged;
}

vector<Rect> faceDetection(Mat original) {

	Mat image;

	cvtColor(original, image, CV_BGR2GRAY);

	equalizeHist(image, image);

	CascadeClassifier faceCascade;

	faceCascade.load("haarcascade_frontalface_default.xml");

	vector<Rect> faces;
	faceCascade.detectMultiScale(image, faces);

	return faces;
}

Mat faceRemoval(Mat img, Mat original) {
	vector<Rect> faces;

	faces = faceDetection(original);

	// draw a black rectange over each face.
	for(int i = 0; i < faces.size(); i++) {
		rectangle(img, faces[i], Scalar(0, 0, 0), -1, 0, 0);
	}

	return img;
}

Mat skinExtraction(Mat original, Mat img) {

	Scalar min_YCrCb = Scalar(54, 131, 110);
	Scalar max_YCrCb = Scalar(163, 157, 135);

	Mat skinRegion;

	inRange(original, min_YCrCb, max_YCrCb, skinRegion);

//	cvtColor(skinRegion, skinRegion, CV_GRAY2BGR);
//	cvtColor(skinRegion, skinRegion, CV_BGR2YCrCb);

	compare(img, skinRegion, img, CMP_EQ);


	return skinRegion;
}

Mat preprocess(Mat original, int morph_size, Mat background, int lowThreshold) {

	Mat bgYCRCB;
	Mat frame = original.clone();
	Mat output;
	Mat detect_Edges;

	cvtColor(background, bgYCRCB, CV_BGR2YCrCb);

	cvtColor(frame, frame, CV_BGR2YCrCb);

	Mat bgRemoved =  backgroundSubtraction(frame, bgYCRCB, 5);

	output = bgRemoved;

//	output = faceRemoval(bgRemoved, original);

//	threshold(output, output, morph_size, 255, THRESH_BINARY);
//	return output;

//	GaussianBlur(output, output, Size(7,7), 1.8, 1.8);

//	threshold(output, output, morph_size, 255, THRESH_BINARY);
	GaussianBlur(output, output, Size(7,7), 1.8, 1.8);
	Canny(output, detect_Edges, lowThreshold, lowThreshold * 3);

//	morphologyEx(detect_Edges, detect_Edges, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 3);

	dilate(detect_Edges, detect_Edges, getStructuringElement(MORPH_RECT, Size(3, 3)));
//	dilate(detect_Edges, detect_Edges, getStructuringElement(MORPH_RECT, Size(3, 3)));
//	dilate(detect_Edges, detect_Edges, getStructuringElement(MORPH_RECT, Size(3, 3)));

//	erode(detect_Edges, detect_Edges, getStructuringElement(MORPH_RECT, Size(3, 3)));

	cvtColor(detect_Edges, detect_Edges, CV_GRAY2BGR);
	cvtColor(detect_Edges, detect_Edges, CV_BGR2YCrCb);

	output = output + detect_Edges;

	cvtColor(output, output, CV_YCrCb2BGR);
	cvtColor(output, output, CV_BGR2GRAY);

	output = skinExtraction(frame, output);

//	cvtColor(output, output, CV_BGR2GRAY);

	threshold(output, output, morph_size, 255, THRESH_BINARY);

	morphologyEx(output, output, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 3);

	GaussianBlur(output, output, Size(7,7), 1.8, 1.8);

	threshold(output, output, 100, 255, THRESH_BINARY);

	return output;
}
