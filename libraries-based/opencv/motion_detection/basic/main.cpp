#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>

#define CAMERA_INDEX 0
#define FRAME_THRESHOLD 25
#define MIN_DETECT_AERA 500

using namespace std;

int main()
{
	// check if OpenCL is avaiable
    if (!cv::ocl::haveOpenCL())
    {
        cout << "OpenCL is not avaiable..." << endl;
        return 1;
    }

	// open the camera
	cv::VideoCapture cam = cv::VideoCapture(CAMERA_INDEX);
    if (!cam.isOpened()) {
        cout << "Cannot open camera " << CAMERA_INDEX << endl;
        return 1;
    }

	// loop for each frame
	cv::UMat backgroundFrame, frame;
	cv::UMat gray, frameDelta, thresh;
	while (true) {
		cam >> frame;
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(gray, gray, cv::Size(21, 21), 0);
		if (backgroundFrame.empty())
			gray.copyTo(backgroundFrame);

		// processing
		cv::absdiff(backgroundFrame, gray, frameDelta);
		cv::threshold(frameDelta, thresh, FRAME_THRESHOLD, 255, cv::THRESH_BINARY);
		cv::dilate(thresh, thresh, NULL, cv::Point(-1, -1), 2);

		vector<cv::UMat> contours;
		cv::findContours(thresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		//cout << "Size: " << contours.size() << endl;
		for (int i = 0; i<contours.size(); i++) {
			//cout << "Aera: " << cv::contourArea(contours[i]) << endl;
			if (cv::contourArea(contours[i]) < MIN_DETECT_AERA) {
				continue;
			}
			cv::Rect r = cv::boundingRect(contours[i]);
			//cout << r.x << ',' << r.y << ',' << endl;
			cv::rectangle(frame, 
				cv::Point(r.x, r.y), 
				cv::Point(r.x + r.width, r.y + r.height), 
				cv::Scalar(0, 255, 0), 2);
		}
		

		// show fram
		cv::imshow("Frame", frame);
		//cv::imshow("Gray", gray);
		//cv::imshow("Thresh", thresh);

		// quit if 'q' is pressed
		if ((cv::waitKey(1) & 0xFF) == 'q')
			break;
	}

	// Clean up
	cam.release();
	cv::destroyAllWindows();
    return 0;
}