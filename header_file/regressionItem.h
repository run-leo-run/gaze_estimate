#ifndef REGRESSIONITEM_H
#define REGRESSIONITEM_H

#include <QGraphicsItem>
#include "capturethread.h"
#include "MyDetector.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class regressionItem : public QGraphicsItem
{
public:
	regressionItem(qreal height , qreal width );
	~regressionItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    //void setColor(const QColor &color) { brushColor = color; }
    void advance(int phase);
   // QPainterPath shape();
	//void getSceneSize(qreal height , qreal width){this->sceneHeight = height;this->sceneWidth = width;};
protected:
    

private:
    QColor brushColor;
	qreal sceneHeight,sceneWidth;
	capturethread *capture;
	cv::Mat frame;
	MyDetector *detector;
	CvSVM predictorX , predictorY;
};

#endif // MYITEM_H