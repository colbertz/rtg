#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void showWindow(const char* winname, cv::Mat img, int& locindex) {
	imshow(winname, img);

	int w = locindex / 5;
	int h = locindex % 5;

	moveWindow(winname, 1000 * w, 150 * h);
	locindex++;
}

int main(int argc, char** argv)
{
	Mat src = imread("notes.png", IMREAD_COLOR);

	int h = 0;
	// Show source image
	showWindow("src", src, h);

	// Transform source image to gray if it is not already
	Mat gray;
	if (src.channels() == 3)
	{
		cvtColor(src, gray, COLOR_BGR2GRAY);
	}
	else
	{
		gray = src;
	}
	showWindow("gray", gray, h);

	// Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
	Mat bw;
	adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	showWindow("binary", bw, h);


	// Create the images that will use to extract the horizontal and vertical lines
	Mat horizontal = bw.clone();
	// Specify size on horizontal axis
	int horizontal_size = horizontal.cols / 30;
	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));
	
	// Apply morphology operations or open
	//erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	//dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	morphologyEx(horizontal, horizontal, MorphTypes::MORPH_OPEN, horizontalStructure);
	// Show extracted horizontal lines
	showWindow("horizontal", horizontal, h);


	Mat vertical = bw.clone();
	// Specify size on vertical axis
	int vertical_size = vertical.rows / 30;
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

	// Apply morphology operations
	//erode(vertical, vertical, verticalStructure, Point(-1, -1));
	//dilate(vertical, vertical, verticalStructure, Point(-1, -1));
	morphologyEx(vertical, vertical, MorphTypes::MORPH_OPEN, verticalStructure);
	// Show extracted vertical lines
	showWindow("vertical", vertical, h);


	Mat vertical_bit;
	// Inverse vertical image
	bitwise_not(vertical, vertical_bit);
	showWindow("vertical_bit", vertical_bit, h);


	// Extract edges and smooth image according to the logic
	// extract edges
	Mat edges;
	adaptiveThreshold(vertical_bit, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, -2);
	showWindow("edges", edges, h);

	// dilate(edges)
	Mat kernel = Mat::ones(2, 2, CV_8UC1);
	dilate(edges, edges, kernel);
	showWindow("dilate", edges, h);

	// smooth the vertical_bit
	Mat smooth;
	vertical_bit.copyTo(smooth);
	blur(smooth, smooth, Size(2, 2));
	showWindow("smooth", smooth, h);

	// Show final result
	smooth.copyTo(vertical_bit, edges);
	showWindow("smooth - final", vertical_bit, h);

	waitKey(0);
	return 0;
}