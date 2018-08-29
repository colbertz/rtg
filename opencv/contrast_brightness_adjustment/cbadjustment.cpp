#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//We call addWeighted method to linear blend to pictures.
//The formula is out(x,y) = alpha*i1(x,y)+beta*i2(x,y)+gamma
void LinearBlend()
{
	Mat image1, image2, output;

	image1 = imread("i1.jpg", ImreadModes::IMREAD_COLOR);
	image2 = imread("i2.jpg", ImreadModes::IMREAD_COLOR);

	addWeighted(image1, 0.5, image2, 0.5, 0.0, output);

	namedWindow("output", WindowFlags::WINDOW_NORMAL);

	imshow("output", output);
}

//We use out(x,y) = alpha*i(x,y)+beta to adjust the contrast and brightness
//Obviously alpha is used to control the contrast felt by human being
//and beta is used to control the brightness
//implemented via addWeighted
void addWeightedCBAdjust()
{
	Mat image1, output;

	image1 = imread("darkbaby.jpg", ImreadModes::IMREAD_COLOR);
	Mat image2 = Mat::zeros(image1.size(), image1.type());
	addWeighted(image1, 2.4, image2, 0, 60.0, output);
	namedWindow("output", WindowFlags::WINDOW_NORMAL);

	imshow("output", output);
	imwrite("cba_baby.jpg", output);
}

//We use out(x,y) = alpha*i(x,y)+beta to adjust the contrast and brightness
//Obviously alpha is used to control the contrast felt by human being
//and beta is used to control the brightness
//implemented via convertTo
void convertToCBAdjust()
{
	Mat image1, output;

	image1 = imread("darkbaby.jpg", ImreadModes::IMREAD_COLOR);
	image1.convertTo(output, -1, 2.4, 60.0);
	
	namedWindow("output", WindowFlags::WINDOW_NORMAL);
	imshow("output", output);
	imwrite("cba_baby.jpg", output);
}
//Besides the above two, we can mannually call a for loop to apply the formular to output mat

//Gamma correction also can be used to adjust contrast and brightness. The difference is it is not linear
//Formular is out(x,y) = (i(x,y)/255)^gamma * 255
//implemented via lookupTable and cv::LUT
void GammaCorrection()
{
	Mat image1, output;

	image1 = imread("darkbaby.jpg", ImreadModes::IMREAD_COLOR);
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, 0.4) * 255.0);
	Mat res = image1.clone();
	LUT(image1, lookUpTable, output);

	namedWindow("output", WindowFlags::WINDOW_NORMAL);
	imshow("output", output);
	imwrite("gc_baby.jpg", output);
}

int main()
{
	//LinearBlend();
	convertToCBAdjust();
	//addWeightedCBAdjust();
	//GammaCorrection();

	waitKey(0);
    return 0;
}

