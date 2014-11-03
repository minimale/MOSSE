/*
 * Filter_gen.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: butters
 */

//////////////////////////////////////////////////////////
/*	
 *	Функция генерации фильтра
 *
 *	Входные параметры:
 *		Mat& image		- 	шаблон
 *		Mat& I_p		- 	обработанный шаблон
 *		Mat& hann 		- 	окно Ханнинга
 *		Mat& G 			- 	фильтр Гаусса
 *		int& hsize, 
 *		double& sigma	-	параметры фильтра Гаусса
 *		Mat& H1, 
 *		Mat& H2			-	элементы фильтра MOSSE
 *		Mat& H 			- 	фильтр MMOSSE	
 *	
 */
//////////////////////////////////////////////////////////

/* Includes */
//////////////////////////////////////////////////////////
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "head.h"

using namespace cv;
using namespace std;
//////////////////////////////////////////////////////////

/* Тело функции генерации фильтра Н */
//////////////////////////////////////////////////////////
void Filter_gen(Mat& image, Mat& I_p, Mat& hann, Mat& G, 
	int& hsize, double& sigma, Mat& H1, Mat& H2, Mat& H)
{
	// Создать окно Ханнинга, с  размерами изображения типа double
	createHanningWindow(hann, Size(image.cols, image.rows), CV_64FC1);

	// Предобработка изображения
	I_p = preprocess(image, hann);

	// Создать ядро фильтра Гаусса
	G = Gauss_filt(image.cols, image.rows, hsize, sigma);

	// Расчет компонентов фильтра H
	FILT_func(H1, H2, G, I_p);

	// Расчет фильтра H
	FILT_div(H1, H2, H);
}
//////////////////////////////////////////////////////////