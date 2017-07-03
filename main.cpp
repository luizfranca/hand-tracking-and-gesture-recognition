/*
 * main.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: luizdaniel
 */


#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {


	cout << "template" << endl;

	Mat image = imread("Lenna.png");

	imshow("image", image);

	waitKey();

	return 0;
}

