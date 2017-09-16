// PlayVideoFileCpp.sln
// main.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

int main(void) {

    cv::VideoCapture capVideo;
    cv::Mat imgFrame;
    cv::Mat grayscaleFrame;

    capVideo.open("mobilku.mp4");

    if (!capVideo.isOpened()) {                                                 // if unable to open video file
        std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
        return(0);                                                              // and exit program
    }

    if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
        std::cout << "\nerror: video file must have at least one frame";
        return(0);
    }

    capVideo.read(imgFrame);

    while (capVideo.isOpened()) {

        cv::imshow("imgFrame", imgFrame);

        if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {       // if there is at least one more frame
            capVideo.read(imgFrame);                            // read it
/*	cv::Mat frame;
	capVideo>>frame;
        cvtColor(frame, grayscaleFrame, CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
        cv::Mat grayFrame;
        cv::imshow("grayFrame", grayFrame);
*/        }
        else {                                                  // else
            std::cout << "end of video\n";                      // show end of video message
            break;                                              // and jump out of while loop
        }

        cv::waitKey(1);

    }


    return(0);
}








