/*
 * FILT_div.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: butters
 */

//////////////////////////////////////////////////////////
/*	
 *	Функция расчета фильтра H
 *
 *	Входные параметры:
 *		Mat& H1, 
 *		Mat& H2			-	элементы фильтра MOSSE
 *		Mat& H 			- 	фильтр MOSSE	
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

/* Тело функции расчета фильтра H */
//////////////////////////////////////////////////////////
void FILT_div(Mat& H1, Mat& H2, Mat& H)
{
	vector<Mat> channels1(3);
	vector<Mat> channels2(3);

	// разделить каналы компонентов фильтра (Re Im)
	split(H1, channels1);
	split(H2, channels2);

	// H_re = H1_re/H2_re
	divide(channels1[0], channels2[0], channels1[0], 1, -1);
	// H_im = H1_im/H2_re
	divide(channels1[1], channels2[0], channels1[1], 1, -1);

	// обьединить каналы в изображение (Re Im)
	merge(channels1, H);
}
//////////////////////////////////////////////////////////