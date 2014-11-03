/*
 * FILT_gen.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: butters
 */

//////////////////////////////////////////////////////////
/*	
 *	Функция расчета компонентов фильтра H
 *
 *	Входные параметры:
 *		Mat& H1, 
 *		Mat& H2			-	элементы фильтра MOSSE
 *		Mat& window 	- 	ядро фильтра Гаусса
 *		Mat& pr_image	-	шаблон после предобработки	
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

/* Тело функции расчета компонентов фильтра H */
//////////////////////////////////////////////////////////
void FILT_func(Mat& H1, Mat& H2, Mat& window, Mat& pr_image)
{
	Mat T;

	// прямое быстрое преобразование Фурье предобработанного шаблона
	dft(pr_image, T, DFT_COMPLEX_OUTPUT);

	// H1 = window(*)T_conj
	mulSpectrums(window, T, H1, 0, true);
	// H2 = T(*)T_conj
	mulSpectrums(T, T, H2, 0, true);
}
//////////////////////////////////////////////////////////