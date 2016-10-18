#include "testItem.h"
#include <QPainter>
#include <stdio.h> 


testItem::testItem(qreal height , qreal width)
{
	count = 0;
	brushColor = Qt::red;
	sceneHeight = height;
	sceneWidth = width;
}

QRectF testItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0 - adjust, 0 - adjust,
                  30 + adjust, 30 + adjust);
}

void testItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
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

void testItem::advance(int phase)
{
	if(!phase) return;
	if(count < 10) 
	{
		count ++;
		return;
	}
	int width = this->sceneWidth;
	int height = this->sceneHeight;
	int Px = rand()%width;
	int Py = rand()%height;

	this->setPos(Px , Py);
	count = 0;
}

testItem::~testItem()
{

}