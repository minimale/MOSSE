/*
 * main.cpp
 *
 *  Created on: Mar 20, 2014
 *      Author: butters
 */

//////////////////////////////////////////////////////////
/*	
 *	Название:	Алгоритм сопровождения объекта с 
 *				использованием MOSSE-фильтра
 *	Разработал:	Лукавский Станислав, Стеценко Роман
 */
//////////////////////////////////////////////////////////

/* Includes */
//////////////////////////////////////////////////////////
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
// #include <fstream>
#include <string>
#include "head.h"

using namespace cv;
using namespace std;
//////////////////////////////////////////////////////////

/* Глобальные переменные для обработки событий мыши */
//////////////////////////////////////////////////////////
Point origin;
Rect selection, roi;
bool selectObject = false;
Mat image, crop_image, frame;
int trackObject = 0;
bool ready = false;
const char* keys = { "{1|  | 0 | camera number}" };
//////////////////////////////////////////////////////////

/* Функция обработки событий мыши */
//////////////////////////////////////////////////////////
static void onMouse(int event, int x, int y, int, void*)
{
	if (ready == false)
	{
		if (selectObject)
		{
			selection.x = MIN(x, origin.x);
			selection.y = MIN(y, origin.y);
			selection.width = std::abs(x - origin.x);
			selection.height = std::abs(y - origin.y);

			selection &= Rect(0, 0, image.cols, image.rows);
		}

		switch (event)
		{
		case CV_EVENT_LBUTTONDOWN:
			origin = Point(x, y);
			selection = Rect(x, y, 0, 0);
			selectObject = true;
			break;
		case CV_EVENT_LBUTTONUP:
			selectObject = false;
			if (selection.width > 0 && selection.height > 0)
				trackObject = -1;
			break;
		}
	}
}
//////////////////////////////////////////////////////////

/* Основная программа */
//////////////////////////////////////////////////////////
int main(int argc, char** argv )
{

	Mat hann, I_p, G, H1, H2, H, S_res;
	int hsize = 5;					// параметры окна Ханнинга
	double sigma = 2;
	int th = 3;						// порог, определяющий статус сопровождения
	double PSR;						// пиковое соотношение сигнал/шум
	int dx = 0;						// смещение обьекта в текущем кадре видеопоследовательности
	int dy = 0;
	int x_r = 0;					// координаты верхнего левого угла рамки
	int y_r = 0;;
	bool tracking_status = false;	// статус сопровождения
	double alfa = 0.125;			// коеффициент альфа-смешивания
	Scalar val = Scalar(0, 255, 0);	// цвет рамки
	// double fps = 0;

	// инициализация окна для вывода изображения
	namedWindow("Image", 1);
	moveWindow("Image", 100, 100);
	// инициализация окна для вывода шаблона
	namedWindow("Crop", 0);
	moveWindow("Crop", 800, 200);

	VideoCapture cap;
	
	CommandLineParser parser(argc, argv, keys);
	int camNum = parser.get<int>("1");
	cap.open(camNum);

	// функция обработки событий мыши в окне "Image"
	setMouseCallback("Image", onMouse, 0);

	// цикл обработки видеопоследовательности
	for (;;)
	{
		// считать кадр с видеопоследовательности
		cap >> image;
		// fps = cap.get(CV_CAP_PROP_FPS);

		// cout << "FPS: " << fps << endl;

		if (trackObject)
		{
			if (trackObject < 0 && ready == false)
			{
				// Получить оптимальные размеры окна для FFT
				int m = getOptimalDFTSize( selection.width );
				int n = getOptimalDFTSize( selection.height );

				// cout << "optimal dft width: " << m << endl;
				// cout << "optimal dft height: " << n << endl;

				selection.width = m;
				selection.height = n;

				// Считать шаблон с изображения
				Mat image1(image, Rect(selection));
				// Перевести с RGB в Grayscale
				cvtColor(image1, frame, CV_RGB2GRAY, 1 );
				// Перевести с CV_8UC1 в CV_64FC1
				frame.convertTo(crop_image, CV_64FC1);

				// string ty = type2str( crop_image.type() );
				// cout << "crop_image: " << ty.c_str() << " " << crop_image.cols << "x" << crop_image.rows << endl;

				// вызвать функцию генерации фильтра
				Filter_gen(crop_image, I_p, hann, G, hsize, sigma, H1, H2, H);

				// сохранить координаты угла рамки
				x_r = selection.x;
				y_r = selection.y;

				// cout << "x_r: " << x_r << endl;
				// cout << "y_r: " << y_r << endl;

				trackObject = 1;
				ready = true;
			}

			if (trackObject == 1)
			{

				Mat image1(image, Rect(selection));
				cvtColor(image1, frame, CV_RGB2GRAY, 1 );
				frame.convertTo(crop_image, CV_64FC1);

				// вызвать функцию обновления фильтра и подсчета PSR
				MOSSE_tracker(image, crop_image, I_p, 
				hann, G, H, S_res, th, PSR, dx, dy, 
				tracking_status, x_r, y_r, H1, H2, alfa, val);

				// cout << "PSR: " << PSR << endl;
			}

			selection.x = x_r;
			selection.y = y_r;

			

			// Отрисовать рамку во время выделения объекта
			rectangle(image, selection, val, 1, CV_AA);
			// Отрисовка поля для вывода информации (X, Y, PSR)
			rectangle(image, Rect(0, image.rows - 20, 100, 20), val, CV_FILLED, CV_AA);
			rectangle(image, Rect(0, image.rows - 40, 100, 20), val, CV_FILLED, CV_AA);
			rectangle(image, Rect(0, image.rows - 60, 100, 20), val, CV_FILLED, CV_AA);
			line(image, Point(0, image.rows - 20), Point(100, image.rows - 20), Scalar(0, 0, 0));
			line(image, Point(0, image.rows - 40), Point(100, image.rows - 40), Scalar(0, 0, 0));

			// инициализация шрифта для вывода информации
			CvFont font = fontQt("Times");
			char buffer[10];

			// вывод значения PSR на изображение
			int buf_size = sprintf(buffer, "PSR: %5.2f", PSR);
			addText( image, buffer, Point(5,image.rows - 5), font);
			// вывод значения X на изображение
			buf_size = sprintf(buffer, "X: %d", x_r);
			addText( image, buffer, Point(5,image.rows - 25), font);
			// вывод значения Y на изображение
			buf_size = sprintf(buffer, "Y: %d", y_r);
			addText( image, buffer, Point(5,image.rows - 45), font);


			imshow("Crop", frame);
		}

		// цикл обработки нажатия клавиш
		if (waitKey (2) == 'r')
		{
			ready = false;
			trackObject = 0;

		}
		if (waitKey(2) == 27)
			break;

		// Обработать размеры рамки и вывести рамку на изображение
		if (selectObject && selection.width > 0 && selection.height > 0)
		{
			rectangle(image, selection, val, 1, CV_AA);
		}

		// вывести шаблон в отдельное окно
		imshow("Image", image);
	}
	
	/*
	image = imread("/home/butters/repo/TargetCode/Processor/MOSSE_tracking/src/test.jpg", 0);
	image.convertTo(image, CV_64FC1);

	Filter_gen(image, I_p, hann, G, hsize, sigma, H1, H2, H);

	MOSSE_tracker(image, I_p, hann, G, H, S_res, 
	PSR, dx, dy, tracking_status, H1, H2, alfa);

	cout << "PSR: " << PSR << endl;
	cout << "dx: " << dx << endl;
	cout << "dy: " << dy << endl;

	image = imread("/home/butters/repo/TargetCode/Processor/MOSSE_tracking/src/test1.jpg", 0);
	image.convertTo(image, CV_64FC1);

	MOSSE_tracker(image, I_p, hann, G, H, S_res, 
	PSR, dx, dy, tracking_status, H1, H2, alfa);

	cout << "PSR: " << PSR << endl;
	cout << "dx: " << dx << endl;
	cout << "dy: " << dy << endl;
	*/

/*
	MOSSE_tracker(image, crop_image, I_p, 
		hann, G, H, S_res, th, PSR, dx, dy, 
		tracking_status, x_r, y_r, H1, H2, alfa, val);
	*/

	destroyAllWindows();

	cout << "program closed" << endl;

	return 0;
}
//////////////////////////////////////////////////////////
