#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv/cv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(void) {
    cv::VideoCapture capVideo ("mobilku.mp4");
    cv::Mat imgFrame;
    cv::Mat grayscaleFrame;
    cv::Ptr<cv::BackgroundSubtractor> bg_model = cv::createBackgroundSubtractorMOG2().dynamicCast<cv::BackgroundSubtractor>();

    if (!capVideo.isOpened()) {                                                 // if unable to open video file
        std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
        return(0);                                                              // and exit program
    }
	cv::namedWindow( "video", 1);
    for( ; ; )
    {
	cv::Mat frame;
        capVideo >> frame;
        if(frame.empty()) break;
        imshow("video", frame);

	cvtColor(frame, grayscaleFrame, CV_BGR2GRAY);
    equalizeHist(grayscaleFrame, grayscaleFrame);
    cv::Mat grayFrame, foregroundMask, foregroundFrame, backgroundFrame;
//	cv::namedWindow("grayFrame",1);
//  cv::imshow("grayFrame", grayscaleFrame);
    cv::waitKey(20); // waits to display frame
	if( foregroundMask.empty() ){
        foregroundMask.create(frame.size(), frame.type());
        }
	bg_model->apply(frame, foregroundMask, true ? -1 : 0);
	cv::GaussianBlur(foregroundMask, foregroundMask, cv::Size(11,11), 3.5,3.5);
	cv::threshold(foregroundMask, foregroundMask, 150, 255, cv::THRESH_BINARY);
	foregroundFrame = cv::Scalar::all(0);
	frame.copyTo(foregroundFrame, foregroundMask);
	bg_model->getBackgroundImage(backgroundFrame);
    Mat Temp;
	foregroundMask.convertTo(Temp, CV_8UC1);
	vector<vector<Point> > contours;
	vector<Vec4i> hier;
    cv::findContours(Temp, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    cv::Mat contourImage(Temp.size(), CV_8UC3, cv::Scalar(0,0,0));
	for (size_t idx = 0; idx < contours.size(); idx++) {
		cv::drawContours(contourImage, contours, idx, Scalar(255, 255, 255), 1, 8, hier);
	}
	imshow("foreground mask", foregroundMask);
    imshow("foreground frame", foregroundFrame);
    imshow("Contour", contourImage);
	cv::waitKey(40);
    }
    cv::waitKey(0); 

    return(0);
}
