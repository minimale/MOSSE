/*
 * corr2D.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: butters
 */

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "head.h"

using namespace cv;
using namespace std;

void corr2D(Mat& i_p, Mat& H, Mat& S_res, double& PSR, 
	int& dx, int& dy)
{
	Mat meanArr, stddevArr;
	Mat I_p;
	double mean, stddev;
	double max;
	Point maxPt;
	double eps = 0.000001;

	dft(i_p, I_p, DFT_COMPLEX_OUTPUT);

	mulSpectrums(I_p, H, S_res, 0, false);

	dft(S_res, S_res, DFT_INVERSE | DFT_REAL_OUTPUT );

	meanStdDev(S_res, meanArr, stddevArr);
	mean = meanArr.at<double>(0, 0);
	stddev = stddevArr.at<double>(0, 0);

	cout << "mean: " << mean << endl;
	cout << "std: " << stddev << endl;

	minMaxLoc(S_res, 0, &max, 0, &maxPt, Mat());
	cout << "max: " << max << "  x: " << maxPt.x << "  y: " << maxPt.y << endl;

	dx = maxPt.x - S_res.cols/2;
	dy = maxPt.y - S_res.rows/2;

	// cout << "dx: " << dx << endl;
	// cout << "dy: " << dy << endl;

	PSR = (max - mean)/(stddev + eps);

	// cout << "PSR: " << PSR << endl;
}