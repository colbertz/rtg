#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	VideoCapture capture("1.mp4");
	Size s = Size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));
	double fps = capture.get(CAP_PROP_FPS);
	int ex = static_cast<int>(capture.get(CAP_PROP_FOURCC));

	VideoWriter writer;
	writer.open("output.mp4", ex, fps, s);

	Mat frame;
	while (true)
	{
		capture.read(frame);
		int mseconds = capture.get(VideoCaptureProperties::CAP_PROP_POS_MSEC);

		if (mseconds < 10 * 1000) continue;

		if (mseconds > 30 * 1000) break;

		writer.write(frame);
	}
	capture.release();
	writer.release();

	return 0;
}