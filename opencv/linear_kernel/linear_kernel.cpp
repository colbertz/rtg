//Origined from https://docs.opencv.org/master/d7/d37/tutorial_mat_mask_operations.html

#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

void Sharpen(const Mat& input, Mat& output) {
	CV_Assert(input.depth() == CV_8U);

	int channelNum = input.channels();
	//we need to call create to allocate the memory for output mat header
	output.create(input.size(), input.type());

	for (int i = 1; i < input.rows - 1; i++)
	{
		//from the second row to the last second row
		const uchar* pPreRow = input.ptr<uchar>(i-1);
		const uchar* pCurrentRow = input.ptr<uchar>(i);
		const uchar* pNextRow = input.ptr<uchar>(i + 1);

		uchar* pOut = output.ptr<uchar>(i);

		for (int j = channelNum; j < channelNum*(input.cols - 1); j++)
		{
			//saturate_cast ensures the calculation does not overflow. 0 for negative values and 255 for larger values
			*pOut = saturate_cast<uchar>(5 * pCurrentRow[j] - pPreRow[j] - pNextRow[j] - pCurrentRow[j - channelNum] - pCurrentRow[j + channelNum]);
			pOut++;
		}

		//set the unfilled rows and columns to be zero
		output.row(0).setTo(Scalar(0));
		output.row(output.rows-1).setTo(Scalar(0));
		output.col(0).setTo(Scalar(0));
		output.col(output.cols - 1).setTo(Scalar(0));
	}
}

void SystemSharpen(const Mat& input, Mat& output)
{
	//operator << is overridden to support comma initilization list for small matrix
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
									 -1, 5, -1,
									  0, -1, 0);
	/**
	The function applies an arbitrary linear filter to an image. In-place operation is supported. When
	the aperture is partially outside the image, the function interpolates outlier pixel values
	according to the specified border mode.

	The function does actually compute correlation, not the convolution:

	\f[\texttt{dst} (x,y) =  \sum _{ \stackrel{0\leq x' < \texttt{kernel.cols},}{0\leq y' < \texttt{kernel.rows}} }  \texttt{kernel} (x',y')* \texttt{src} (x+x'- \texttt{anchor.x} ,y+y'- \texttt{anchor.y} )\f]

	That is, the kernel is not mirrored around the anchor point. If you need a real convolution, flip
	the kernel using #flip and set the new anchor to `(kernel.cols - anchor.x - 1, kernel.rows -
	anchor.y - 1)`.

	The function uses the DFT-based algorithm in case of sufficiently large kernels (~`11 x 11` or
	larger) and the direct algorithm for small kernels.
	**/
	filter2D(input, output, input.depth(), kernel);
}

int main()
{
	Mat image; 

	image = imread("baby.jpg", ImreadModes::IMREAD_COLOR);
	Mat output1;
	Mat output2;

	int64 s = getTickCount();
	SystemSharpen(image, output1);
	int64 e = getTickCount();
	double cost = (e - s) / getTickFrequency();
	cout << "SystemSharpen finishes in " << cost << " seconds" << endl;
	
	s = getTickCount();
	Sharpen(image, output2);
	e = getTickCount();
	cost = (e - s) / getTickFrequency();
	cout << "Self Sharpen finishes in " << cost << " seconds" << endl;


	namedWindow("input", WindowFlags::WINDOW_NORMAL);
	namedWindow("output1", WindowFlags::WINDOW_NORMAL);
	namedWindow("output2", WindowFlags::WINDOW_NORMAL);

	imshow("input", image);
	imshow("output1", output1);
	imshow("output2", output2);

	resizeWindow("input", 600, 600);
	resizeWindow("output1", 600, 600);
	resizeWindow("output2", 600, 600);

	waitKey(0);
    return 0;
}

