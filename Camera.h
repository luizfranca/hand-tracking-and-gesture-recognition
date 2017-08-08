/*
 * Camera.h
 *
 *  Created on: Jul 4, 2017
 *      Author: luizdaniel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat preprocess(Mat original, int minThresh[3], int maxThresh[3], int morph_size);

#endif /* CAMERA_H_ */
