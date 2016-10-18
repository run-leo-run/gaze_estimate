#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QGraphicsEffect>
#include <QtGui>
#include <QTransform>

#include <string>
#include <sstream>
//笨方法，在myitem advance中实现videocapture，并写图像到当地文件夹
MyItem::~MyItem()
{
	//capture->terminate();
	//capture->wait();
}
MyItem::MyItem(qreal height , qreal width)
{
    brushColor = Qt::red;
	moveState = 0;
	count = 0;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

	sceneHeight = height;
	sceneWidth = width;

	capture = new capturethread();
	this->capture->start();
}

QRectF MyItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0 - adjust, 0 - adjust,
                  30 + adjust, 30 + adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
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

void MyItem::advance(int phase)
{
	
	
	frame = this->capture->returnFrame();

	//保存图片路径
	String s;
	
    //在第一个阶段不进行处理
    if (!phase)
        return;
	if(frame.empty())
		return;
	(this->count)++;
	//count 每数10次，改变一次moveState，并把图片保存
	//图形项按照规定的路径移动
	if( moveState < 9) 
	{
		switch ((moveState%9))
		{
		case 0:
			this->setPos( 0 , 0 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "0" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 1:
			this->setPos( 0 , this->sceneHeight/2 );		
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "1" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 2:
			this->setPos( 0, this->sceneHeight - 2 - 30 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "2" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 3:
			this->setPos( this->sceneWidth/2 - 2 , 0 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "3" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 4:
			this->setPos( this->sceneWidth/2 - 2 , this->sceneHeight/2 - 2 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "4" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 5:
			this->setPos( this->sceneWidth/2 - 2 , this->sceneHeight - 2 - 30 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "5" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 6:
			this->setPos( this->sceneWidth - 2 - 30 , 0 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "6" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 7:
			this->setPos( this->sceneWidth - 2 -30 , this->sceneHeight/2 - 2 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "7" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
		case 8:
			this->setPos( this->sceneWidth - 2 -30 , this->sceneHeight - 2 - 30 );
			if((count > 94)&&(count < 100))
			{ 				
				frame = this->capture->returnFrame();
				s = std::to_string(count%10 - 5);
				s = "8" + s + ".jpg";
				imwrite( s , frame);
			}
			else if(count > 100) 
			{
					moveState++;
					count = 0;
			}	
			break;
	
		default:
			break;
		}
	}
	else if(moveState == 9)
	{
		this->capture->stop();
		moveState++;
	}

    //图形项向不同方向随机移动
    //int value = qrand() % 100;
    //if (value < 25) {
    //    //rotate(45);
    //    moveBy(qrand() % 10, qrand() % 10);
    //} else if (value < 50) {
    //    //rotate(-45);
    //    moveBy(- qrand() % 10, - qrand() % 10);
    //} else if (value < 75) {
    //    //rotate(30);
    //    moveBy(- qrand() % 10, qrand() % 10);
    //} else {
    //    //rotate(-30);
    //    moveBy(qrand() % 10, - qrand() % 10);
    //}
}


//
//QPainterPath MyItem::shape()
//{
//    QPainterPath path;
//    path.addRect(-10, -10, 25, 25);
//    return path;
//}


