// PlayVideoFileCpp.sln
// main.cpp

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

int main(void) {

    cv::VideoCapture capVideo ("mobilku.mp4");
    cv::Mat imgFrame;
    cv::Mat grayscaleFrame;


    if (!capVideo.isOpened()) {                                                 // if unable to open video file
        std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
        return(0);                                                              // and exit program
    }

	cv::namedWindow( "video", 1);
    for( ; ; )
    {
	cv::Mat frame;
        capVideo >> frame;
        if(frame.empty())
            break;
        imshow("video", frame);
        cv::waitKey(20); // waits to display frame
    }
    cv::waitKey(0); 

/*    capVideo.read(imgFrame);

    while (capVideo.isOpened()) {

        cv::imshow("imgFrame", imgFrame);

        if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {       // if there is at least one more frame
            capVideo.read(imgFrame);                            // read it
	cv::Mat frame;
	capVideo>>frame;
        cvtColor(frame, grayscaleFrame, CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
        cv::Mat grayFrame;
        cv::imshow("grayFrame", grayFrame);
        }
        else {                                                  // else
            std::cout << "end of video\n";                      // show end of video message
            break;                                              // and jump out of while loop
        }

        cv::waitKey(1);

    }
*/

    return(0);
}








