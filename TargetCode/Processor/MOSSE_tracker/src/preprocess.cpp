/*
 * preprocess.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: butters
 */

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat preprocess(Mat src, Mat window)
{
	Mat res;
	Mat meanArr, stddevArr;
	double mean, stddev;
	double max;
	// double min;
	double eps = 0.00001;
	// Point minPt;
	Point maxPt;

	// Переводим в тип double (float не работает)
	// src.convertTo(src, CV_64FC1);

	// логарифм натуральный масива image
	log(src + 1, src);

	// среднее и среднеквадратичное отклонение изображения
	meanStdDev(src, meanArr, stddevArr);
	mean = meanArr.at<double>(0, 0);
	stddev = stddevArr.at<double>(0, 0);



	// Нормализация изображения
	res = (src - mean)/(stddev + eps);

	// minMaxLoc(res, &min, &max, &minPt, &maxPt, Mat());
	minMaxLoc(res, 0, &max, 0, &maxPt, Mat());
	

	// Поэлементное перемножение с окном Ханнинга
	res = res.mul(window);

	return res;
}
