/*
 * MOSSE_tracker.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: butters
 */

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "head.h"

using namespace cv;
using namespace std;


void MOSSE_tracker(Mat& image, Mat& frame, Mat& I_p, 
	Mat& hann, Mat& G, Mat& H, Mat& S_res, int& th, 
	double& PSR, int& dx, int& dy, bool& tracking_status, 
	int& x_r, int& y_r, Mat& H1, Mat& H2, double& alfa, 
	Scalar& color)

/*
void MOSSE_tracker(Mat& frame, Mat& I_p, 
	Mat& hann, Mat& G, Mat& H, Mat& S_res, 
	double& PSR, int& dx, int& dy, bool& tracking_status, 
	Mat& H1, Mat& H2, double& alfa)
*/
{
	
	Mat H1_n, H2_n;
	Mat t_p;
	int x_tmp, y_tmp;

	// Предобработка изображения
	I_p = preprocess(frame, hann);

	corr2D(I_p, H, S_res, PSR, dx, dy);


	if (PSR > th)
	{
		tracking_status = true;
		color = Scalar(0, 255, 0);

		x_tmp = x_r + dx;
		y_tmp = y_r + dy;
		
		if ( x_tmp >= 1 && y_tmp >= 1 && (x_tmp + frame.cols) <= image.cols && (y_tmp + frame.rows) <= image.rows)
		{
			x_r = x_tmp;
			y_r = y_tmp;

			Mat t(image, Rect(x_r, y_r, frame.cols, frame.rows));
			cvtColor(t, t, CV_RGB2GRAY, 1 );
			t.convertTo(t, CV_64FC1);

			string ty = type2str( t.type() );
			cout << "t: " << ty.c_str() << " " << t.cols << "x" << t.rows << endl;

			t_p = preprocess(t, hann);

			FILT_func(H1_n, H2_n, G, t_p);

			FILT_upd(H1, H2, H1_n, H2_n, alfa);

			FILT_div(H1, H2, H);
		}

		th = 7;

	}

	else
	{
		tracking_status = false;
		color = Scalar(0, 0, 255);	
	}
	
}
