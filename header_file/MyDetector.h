#ifndef MYDETECTOR_H
#define MYDETECTOR_H

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include <string>
#include <strstream>

#include "constants.h"
#include "findEyeCenter.h"
#include "findEyeCorner.h"

class MyDetector
{	
public:
	MyDetector();
	void detectAndDisplay( cv::Mat frame);
	void findEyes(cv::Mat frame_gray, cv::Rect face);
	void corner_track(cv::Mat &src_gray , std::vector<cv::Point2f> &corners);
	int detecteye_row( cv::Mat& eyeROI , cv::Point eyeCenter , int eye_region_width , cv::Point &detaL , cv::Point &detaR);
	int maxofrow(cv::Mat &row);
	cv::Point eye_corner_detect(std::vector<cv::Point2f> &corner_track , cv::Point &eye_centerO , int loc);
	cv::Mat returenDebugImage(){return debugImage;}
	std::vector<cv::Point> returnFeature();

private:
	cv::Point irisL , irisR;
	cv::Point LcornerL, LcornerR , RcornerL , RcornerR;
	cv::Mat debugImage;
	cv::String face_cascade_name;
	cv::CascadeClassifier face_cascade;
	std::string test_file;
};
#endif