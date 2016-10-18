#ifndef TESTITEM_H
#define TESTITEM_H

#include <QGraphicsItem>

class testItem : public QGraphicsItem
{
public:
    testItem(qreal height , qreal width);
	~testItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    //void setColor(const QColor &color) { brushColor = color; }
    void advance(int phase);
protected:

private:
	QColor brushColor;
	qreal sceneHeight,sceneWidth;
	int count;
};

#endif