#include "regressionItem.h"
#include <QPainter>
regressionItem::~regressionItem()
{
	//capture->terminate();
	//capture->wait();
}
regressionItem::regressionItem(qreal height , qreal width )
{

	this->sceneHeight = height;
	this->sceneWidth = width;
	this->predictorX.load("Xsvm_model.xml");
	this->predictorY.load("Ysvm_model.xml");

	brushColor = Qt::blue;

	capture = new capturethread();
	this->capture->start();
	
}

QRectF regressionItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0 - adjust, 0 - adjust,
                  30 + adjust, 30 + adjust);
}

void regressionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    if(hasFocus() || !collidingItems().isEmpty()) {
        painter->setPen(QPen(QColor(255,255,255,200)));
    } else {
        painter->setPen(QPen(QColor(100,100,100,100)));
    }
    painter->setBrush(brushColor);
	painter->drawEllipse( 0 , 0 , 30, 30);
    //painter->drawRect(-10, -10, 50, 50);
}

void regressionItem::advance(int phase)
{
	if(!phase) 
		return;

	cv::Mat predictData( 1 , 12 , CV_32FC1);
	cv::Mat predictLabelX( 1 , 1 , CV_32FC1);
	cv::Mat predictLabelY( 1 , 1, CV_32FC1);

	frame = this->capture->returnFrame();
	detector = new MyDetector();
	std::vector<cv::Point> feature;
	detector->detectAndDisplay( frame );
	feature = detector->returnFeature();
	predictData.at<float>(0 , 0) = feature.at(0).x;
	predictData.at<float>(0 , 1) = feature.at(0).y;
	predictData.at<float>(0 , 2) = feature.at(1).x;
	predictData.at<float>(0 , 3) = feature.at(1).y;
	predictData.at<float>(0 , 4) = feature.at(2).x;
	predictData.at<float>(0 , 5) = feature.at(2).y;
	predictData.at<float>(0 , 6) = feature.at(3).x;
	predictData.at<float>(0 , 7) = feature.at(3).y;
	predictData.at<float>(0 , 8) = feature.at(4).x;
	predictData.at<float>(0 , 9) = feature.at(4).y;
	predictData.at<float>(0 , 10) = feature.at(5).x;
	predictData.at<float>(0 , 11) = feature.at(5).y;

	this->predictorX.predict(predictData , predictLabelX);
	this->predictorY.predict(predictData , predictLabelY);
	
	int px = predictLabelX.at<float>(0,0);
	int py = predictLabelY.at<float>(0,0);
	this->setPos( px ,py);

}