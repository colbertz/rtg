#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	VideoCapture capture("output.mp4");

	Mat frame, back;
	Ptr<BackgroundSubtractorMOG2> pBSMog = createBackgroundSubtractorMOG2();
	while (true)
	{
		if (!capture.read(frame)) break;

		pBSMog->apply(frame, back);
		imshow("Frame", frame);
		imshow("Background", back);

		//get the input from the keyboard
		(char)waitKey(30);
	}
	
	capture.release();

	return 0;
}