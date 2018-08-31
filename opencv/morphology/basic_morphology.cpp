#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) 
{
	Mat input = imread("i.png", ImreadModes::IMREAD_GRAYSCALE);
	Mat o1, o2;

	//erode and dilate are the basic morphologic operations. Both of them use a kernel to convolve the image
	//Suppose the foreground has higher value.
	//erode convolve the image using the local min. Erode expands the foreground.
	//dilate convolve the image using the local max. Dilate shrinks the foreground.

	Mat kernel = getStructuringElement(MorphShapes::MORPH_RECT, Size(5, 5));

	//erode
	erode(input, o1, kernel);
	//dilate
	dilate(input, o2, kernel);

	namedWindow("input", WindowFlags::WINDOW_NORMAL);
	imshow("input", input);


	namedWindow("erode", WindowFlags::WINDOW_NORMAL);
	imshow("erode", o1);

	namedWindow("dilate", WindowFlags::WINDOW_NORMAL);
	imshow("dilate", o2);


	//Open first erode and then dilate.
	//It can be used to remove the disjoint noise points and does not affect the original image
	Mat openi = imread("openi.png", ImreadModes::IMREAD_GRAYSCALE);
	Mat o3;
	morphologyEx(openi, o3, MorphTypes::MORPH_OPEN, kernel);


	namedWindow("openi", WindowFlags::WINDOW_NORMAL);
	imshow("openi", openi);

	namedWindow("after open", WindowFlags::WINDOW_NORMAL);
	imshow("after open", o3);


	//Close first dialte and then erode.
	//It can be used to fill the holes in a piece of joint area
	Mat closei = imread("closei.png", ImreadModes::IMREAD_GRAYSCALE);
	Mat o4;
	morphologyEx(closei, o4, MorphTypes::MORPH_CLOSE, kernel);


	namedWindow("closei", WindowFlags::WINDOW_NORMAL);
	imshow("closei", closei);

	namedWindow("after close", WindowFlags::WINDOW_NORMAL);
	imshow("after close", o4);


	//there are other morphological operations:
	//Morphological gradient : It is the difference between the dilation and the erosion of an image.
	//Top Hat: It is the difference between an input image and its opening.
	//Black Hat: It is the difference between the closing and its input image

	waitKey(0);
	return(0);
}