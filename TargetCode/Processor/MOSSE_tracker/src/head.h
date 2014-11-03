/*
 * head.h
 *
 *  Created on: Mar 20, 2014
 *      Author: butters
 */

#ifndef HEAD_H_
#define HEAD_H_

// #include <iostream>
// #include <string>

using namespace std;
using namespace cv;

string type2str(int type);
Mat preprocess(Mat src, Mat window);
Mat Gauss_filt(int w, int h, int hsize, double sigma);
void FILT_func(Mat& H1, Mat& H2, Mat& window, 
	Mat& pr_image);
void matlab_cout(Mat src, char* name);
void matlab_cout(Mat src);
void FILT_div(Mat& H1, Mat& H2, Mat& H);
void corr2D(Mat& i_p, Mat& H, Mat& S_res, 
	double& PSR, int& dx, int& dy);
void Filter_gen(Mat& image, Mat& I_p, Mat& hann, 
	Mat& G, int& hsize, double& sigma, Mat& H1, 
	Mat& H2, Mat& H);
void MOSSE_tracker(Mat& image, Mat& frame, Mat& I_p, 
	Mat& hann, Mat& G, Mat& H, Mat& S_res, int& th, 
	double& PSR, int& dx, int& dy, bool& tracking_status, 
	int& x_r, int& y_r, Mat& H1, Mat& H2, double& alfa, 
	Scalar& color);
void FILT_upd(Mat& H1, Mat& H2, Mat& H1_n, Mat& H2_n, 
	double& alfa);

#endif /* HEAD_H_ */
