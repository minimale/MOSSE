/*
 * Gauss_filt.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: butters
 */

//////////////////////////////////////////////////////////
/*	
 *	Функция формирования фильтра Гаусса
 *
 *	Входные параметры:
 *		int w 
 *		int h			-	компоненты фильтра H
 *		int hsize
 *		double sigma	-	обновленные компоненты фильтра H
 *
 */
//////////////////////////////////////////////////////////

/* Includes */
//////////////////////////////////////////////////////////
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "head.h"

using namespace cv;
using namespace std;
////////////////////////////////////////////////////////// 

/* Includes */
//////////////////////////////////////////////////////////
Mat Gauss_filt(int w, int h, int hsize, double sigma)
{
	Mat g = Mat::zeros(h, w, CV_64FC1);

	Mat G;
	double max;

	g.at<double>(h/2, w/2) = 1;

	GaussianBlur(g, g, Size(hsize, hsize), sigma, sigma);
	minMaxLoc(g, 0, &max, 0, 0, Mat());
	g = g/max;

	dft(g, G, DFT_COMPLEX_OUTPUT);

	return G;
}
//////////////////////////////////////////////////////////