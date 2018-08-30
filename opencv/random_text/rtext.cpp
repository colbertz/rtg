#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void) {

	RNG randomGen(getTickCount());
	string rs;
	for (int i = 0; i < 10; i++)
	{
		int n = randomGen.uniform(97, 120);
		rs.append(1, static_cast<char>(n));
	}

	Mat image = Mat::zeros(400, 400, CV_8UC3);

	putText(image, rs, Point(100, 100), HersheyFonts::FONT_ITALIC, 1, Scalar(0, 0, 255));

	imshow("random text", image);

	waitKey(0);
	return(0);
}