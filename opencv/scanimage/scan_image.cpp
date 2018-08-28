#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//pass mat by reference because we need to reduce the color space on the image.
//this is the efficient way to do the job. It is the client's duty to make sure the skip the row's gap
void ScanReduce1(Mat& image)
{
    CV_Assert(image.depth() == CV_8U);

    int begin = getTickCount();
    cout<<"ScanReduce1 is called"<<endl;

    int channelNum = image.channels();
    int rowsNum = image.rows;
    int colNum = image.cols*channelNum;

    if(image.isContinuous())
    {
        colNum = colNum * rowsNum;
        rowsNum = 1;
    }

    int i,j;
    uchar* p;
    for(i=0;i<rowsNum;i++)
    {
        p = image.ptr<uchar>(i);
        for(j=0;j<colNum;j++)
        {
            p[j] = (p[j]>>5)<<5;
        }
    }

    int end = getTickCount();
    double cost = (end-begin)/getTickFrequency();
    cout<<"ScanReduce1 finishes in "<<cost<<" seconds"<<endl;
}

//Use iterator to go through the pixel one by one. Each pixel is Vec3b type containing 
//3 bytes, each for one channel
void ScanReduce2(Mat& image)
{
    CV_Assert(image.depth() == CV_8U);
    CV_Assert(image.channels() == 3);

    int begin = getTickCount();
    cout<<"ScanReduce2 is called"<<endl;

    MatIterator_<Vec3b> it, tail;
    for(it=image.begin<Vec3b>(),tail=image.end<Vec3b>();it!=tail;it++)
    {
        (*it)[0] = ((*it)[0]>>5)<<5;
        (*it)[1] = ((*it)[1]>>5)<<5;
        (*it)[2] = ((*it)[2]>>5)<<5;
    }
    
    int end = getTickCount();
    double cost = (end-begin)/getTickFrequency();
    cout<<"ScanReduce2 finishes in "<<cost<<" seconds"<<endl;
}

//Mat_ is the same as Mat with the extra need that at definition you need to specify
//the data type through what to look at the data matrix, 
//however in return you can use the operator() for fast access of items.

//This calls the Random Access. Mat override the () to random access the item by index.
//In debug mode, it will perform a check that your input coordinates are valid and does exist.
//In the release mode, it may beat the iterator method or not.
void ScanReduce3(Mat& image)
{
    CV_Assert(image.depth() == CV_8U);
    CV_Assert(image.channels() == 3);

    int begin = getTickCount();
    cout<<"ScanReduce3 is called"<<endl;

    Mat_<Vec3b> _I = image;
    for( int i = 0; i < image.rows; ++i)
        for( int j = 0; j < image.cols; ++j ){
            _I(i,j)[0] = (_I(i,j)[0]>>5)<<5;
            _I(i,j)[1] = (_I(i,j)[1]>>5)<<5;
            _I(i,j)[2] = (_I(i,j)[2]>>5)<<5;
        }
    image = _I;
    
    int end = getTickCount();
    double cost = (end-begin)/getTickFrequency();
    cout<<"ScanReduce2 finishes in "<<cost<<" seconds"<<endl;
}

//cv::LUT() has even better performance due to OpenCV library is multi-thread enabled via Intel Threaded Building Blocks 
//    Mat lookUpTable(1, 256, CV_8U);
//    uchar* p = lookUpTable.ptr();
//    for( int i = 0; i < 256; ++i)
//        p[i] = table[i];

//Finally call the function (I is our input image and J the output one):
//        LUT(I, lookUpTable, J);

int main()
{
    Mat image;
    image = imread("zhouhe.jpg", ImreadModes::IMREAD_COLOR);
    Mat image2 = image.clone();
    ScanReduce1(image2);

    namedWindow("origin", WindowFlags::WINDOW_NORMAL);
    namedWindow("reduced", WindowFlags::WINDOW_NORMAL);

    imshow("origin", image);
    imshow("reduced", image2);

    resizeWindow("origin",600,600);
    resizeWindow("reduced",600,600);

    waitKey(0);
    return 0;
}