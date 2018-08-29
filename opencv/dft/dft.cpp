#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat input = imread("baby.jpg", ImreadModes::IMREAD_GRAYSCALE);

    Mat padded;
    int m = getOptimalDFTSize(input.rows);
    int n = getOptimalDFTSize(input.cols);

    copyMakeBorder(input,padded,0,m-input.rows,0,n-input.cols,BorderTypes::BORDER_CONSTANT,Scalar(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F)};
    Mat complexImage;
    merge(planes,2,complexImage);

    dft(complexImage, complexImage);

    split(complexImage, planes);
    magnitude(planes[0],planes[1],planes[0]);

    Mat image = planes[0];
    image += Scalar::all(1);
    log(image,image);

    image = image(Rect(0, 0, image.cols & -2, image.rows & -2));

    int cx = image.cols/2;
    int cy = image.rows/2;
    Mat q0(image, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(image, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(image, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(image, Rect(cx, cy, cx, cy)); // Bottom-Right
    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
    normalize(image, image, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    namedWindow("input", WindowFlags::WINDOW_NORMAL);
    namedWindow("spectrum", WindowFlags::WINDOW_NORMAL);
    imshow("input", input);
    imshow("spectrum", image);
    resizeWindow("input",500,500);
    resizeWindow("spectrum",500,500);

    waitKey(0);
    return 0;
}