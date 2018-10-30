/*
 * Detection.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: luizdaniel
 */

#include "Detection.h"

Mat detect(Mat image, int thresholdSize) {
//	cout << "detect " << endl;
	vector< vector<Point> > contours;
	vector< vector<Point> > contoursSelected;
	vector<Vec4i> hierarchy;

	findContours(image.clone(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);


	Mat drawing = Mat::zeros(image.size(), CV_8UC3);

	for (int i = 0; i < contours.size(); ++i) {

		if (contours[i].size() > thresholdSize) {
			Scalar color = Scalar(255, 255, 255);

			drawContours(drawing, contours, i, color);
			contoursSelected.push_back(contours[i]);


		}
	}
//	cout << "Contours extracted " << endl;
	vector< vector<Point> > approx(contoursSelected.size());
	vector<Rect> boundRect (contoursSelected.size());

	for (int i = 0; i < contoursSelected.size(); ++i) {

		approxPolyDP(Mat(contoursSelected[i]), approx[i], 3, true);
		boundRect[i] = boundingRect(Mat(approx[i]));
	}

	for (int i = 0; i < boundRect.size(); ++i) {
		string w = "ROI ";
		w += i;
		Mat roi = image(boundRect[i]);
		imshow(w, roi);
	}
	imshow("Drawing", drawing);
	imwrite("drawing.png", drawing);
	if (boundRect.size() > 0) {

//		imwrite("image", roi);


	}
	return image;
}

//
//int index = 0;
//
//	for (int i = 0; i < contours.size(); ++i) {
//
//		if (contours[i].size() > contours[index].size()) {
//			index = i;
//		}
//
//	}
//
//	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//
//	drawContours(drawing, contours, index, color);
