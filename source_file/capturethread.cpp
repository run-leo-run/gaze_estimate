#include "capturethread.h"
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

capturethread::capturethread(QObject *parent):
	QThread(parent)
{
	stopped = false;
}

void capturethread::run()
{
	//cv::namedWindow("displayWindow",WINDOW_AUTOSIZE);
	this->capture.open(0);
	if(capture.isOpened())
	{
		while(!stopped)
		{
			capture.read(frame);
			if( !frame.empty())
			{
				//imshow("displayWindow" , frame);
				//imwrite("1.jpg", frame);
			}
		}
	}
	stopped = false;
}

void capturethread::stop()
{	
	//cv::Mat aa = frame.clone();
	stopped = true;
//	capture.release();
	//this->quit();
	//this->wait();
	
}

capturethread::~capturethread()
{
	capture.release();
}