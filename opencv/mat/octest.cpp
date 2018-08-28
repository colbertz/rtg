//These practice codes are origined from official documentation
//https://docs.opencv.org/3.4.2/d6/d6d/tutorial_mat_the_basic_image_container.html

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    //this just define the mat header
    Mat image;
    //imread allocate and return the real picture data in heap
    //the new opencv c++ api is good for the case, that client do not need to think about memory management
    //this image just behaves like a smart pointer. When it goes out the block, its desctructor will release
    //the underlying image data. Internally, it also uses the reference counting. The underlying memory will
    //only release after all the references(Mat header) in the stack are out of life 
    image = imread("baby.jpg", ImreadModes::IMREAD_COLOR );

    //no memory allocated. image2 is a different header on stack, but pointing to the same underlying image
    //reference count increases to 2
    Mat image2(image);   
    //reference count increases to 3
    Mat image3 = image;

    Mat gray;
    //cvtColor allocates the memory for the gray, extract image's data store into gray as 8 bit 1 channel 
    cvtColor(image, gray, ColorConversionCodes::COLOR_BGR2GRAY);
    //write the gray image to local file
    imwrite("gray.jpg", gray);

    //initialize a mat with ROI. Note this still does not allocate new memory. The reference count goes to 5
    Mat roi(image, Rect(520,40,400,400));
    Mat roi2(image, Range(0,380), Range::all());

    //To copy out a new image data in heap. Call mat.clone or mat.copyTo
    Mat newimage1 = image.clone();
    Mat newimage2;
    gray.copyTo(newimage2);

    //show in window. This is portable for both Microsoft Windows and Linux based system
    namedWindow("baby", WindowFlags::WINDOW_NORMAL);
    namedWindow("gray", WindowFlags::WINDOW_NORMAL);
    imshow("baby", image);
    imshow("gray", gray);
    imshow("roi", roi);
    imshow("roi2", roi2);
    resizeWindow("baby",400,600);
    resizeWindow("gray",400,600);

    //Mat does not only work as a image container. It is designed for a general matrix
    Mat matrix(2,2,CV_8UC1,Scalar::all(111));
    std::cout<<"matrix="<<std::endl<<matrix<<std::endl;

    //create function cannot be used to initialize, but resize the matrix if its not bigger enough
    matrix.create(4,4, CV_8UC(2));
    std::cout << "matrix resized = "<< std::endl << " "  << matrix << std::endl << std::endl;
    // call format to format the output matrix
    std::cout << "R (python)  = " << std::endl << format(matrix, Formatter::FMT_PYTHON) << std::endl << std::endl;

    //3 dimemson
    int size[3] = {2,2,2};
    Mat matrix2(3, size, CV_8U, Scalar::all(0));
    
    //matlab style
    Mat E = Mat::eye(4, 4, CV_64F);
    std::cout << "E = " << std::endl << " " << E << std::endl << std::endl;
    Mat O = Mat::ones(2, 2, CV_32F);
    std::cout << "O = " << std::endl << " " << O << std::endl << std::endl;
    Mat Z = Mat::zeros(3,3, CV_8UC1);
    std::cout << "Z = " << std::endl << " " << Z << std::endl << std::endl;


    //hang for a key input and quit
    waitKey(0);
    return 0;
}