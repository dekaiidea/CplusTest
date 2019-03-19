#include <iostream> 
#include <opencv2/opencv.hpp>

using namespace cv;
int main(int arg, char** args) {
	std::cout << "ready" << std::endl;
 
    std::string img = "C:\\Users\\user\\Desktop\\1.png";
    Mat srcImage = imread(img,0);
    if (!srcImage.data) {
        return 1;
    }
    Mat thdst;
    adaptiveThreshold(srcImage,thdst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,2);
    imshow("srcImage", srcImage);
    cvWaitKey(0);
    imwrite("1.png",srcImage*255);
    return 0;
}