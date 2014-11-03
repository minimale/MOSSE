/*
 * matlab_cout.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: butters
 */

// #include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <fstream>
// #include "head.h"

using namespace cv;
using namespace std;

void matlab_cout(Mat src)
{
	int c, r;

	ofstream myfile;
	// char path[] = "/home/butters/repo/TargetCode/Processor/MOSSE_tracking/src/";
	// strcat(path, name);
	// cout << path << endl;
	myfile.open ("/home/butters/repo/TargetCode/Processor/MOSSE_tracking/txt_dump/H_re.txt");
	
	for (c = 0; c < src.cols; c++)
	{
		for (r = 0; r < src.rows; r++)
		{
			myfile << src.at<double>(c, r);
			myfile << " ";
		}
		myfile << endl;
	}
	
	myfile.close();
}
