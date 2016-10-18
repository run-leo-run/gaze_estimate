#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>
#include "capturethread.h"
class MyItem : public QGraphicsItem
{
public:
    MyItem(qreal height , qreal width);
	~MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    //void setColor(const QColor &color) { brushColor = color; }
    void advance(int phase);
   // QPainterPath shape();
	//void getSceneSize(qreal height , qreal width){this->sceneHeight = height;this->sceneWidth = width;};
	int getMoveState(){ return moveState;}
protected:
    //void keyPressEvent(QKeyEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    QColor brushColor;
	int moveState ;
	qreal sceneHeight,sceneWidth;
	capturethread *capture;
	int count;
	cv::Mat frame;
};

#endif // MYITEM_H
