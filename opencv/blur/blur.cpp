#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) 
{
	Mat input = imread("mom.jpg", ImreadModes::IMREAD_COLOR);
	Mat o1, o2, o3, o4;

	//normal blur
	blur(input, o1, Size(9, 9));

	//median blur
	medianBlur(input, o2, 9);

	//Gaussian filter
	GaussianBlur(input, o3, Size(9, 9), 0, 0);

	//Bilateral filter
	bilateralFilter(input, o4, 9, 18, 5);


	namedWindow("input", WindowFlags::WINDOW_NORMAL);
	imshow("input", input);
	resizeWindow("input", 400, 600);


	namedWindow("blur", WindowFlags::WINDOW_NORMAL);
	imshow("blur", o1);
	resizeWindow("blur", 400, 600);

	namedWindow("median", WindowFlags::WINDOW_NORMAL);
	imshow("median", o2);
	resizeWindow("median", 400, 600);

	namedWindow("Gaussian", WindowFlags::WINDOW_NORMAL);
	imshow("Gaussian", o3);
	resizeWindow("Gaussian", 400, 600);

	namedWindow("Bilateral", WindowFlags::WINDOW_NORMAL);
	imshow("Bilateral", o4);
	resizeWindow("Bilateral", 400, 600);


	waitKey(0);
	return(0);
}