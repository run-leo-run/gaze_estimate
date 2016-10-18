#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <sstream>
using namespace cv;
using namespace std;
class capturethread : public QThread
{
	Q_OBJECT
public:
	explicit capturethread(QObject *parent = 0);
	~capturethread();
	void stop();
	cv::Mat returnFrame() { return frame;}

protected:
	void run();

private :
	volatile bool stopped;
	cv::VideoCapture capture;
	cv::Mat frame;
	std::string test_file;

signals:

	public slots:
};
#endif