#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "myitem.h"
#include "capturethread.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this); 	  
	ui->graphicsView->setScene(scene);
	
	ui->graphicsView->setWindowFlags(Qt::Dialog);
    ui->graphicsView->showFullScreen();
	// 减2是避免出现上下的滚动条
	scene->setSceneRect(0, 0, 
		ui->graphicsView->width() - 2 , ui->graphicsView->height() - 2);

	//ui->graphicsView->show();

    item = new MyItem(ui->graphicsView->height(), ui->graphicsView->width());
    //item->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    //item->setPos(0, 0);
    scene->addItem(item);	

	//capThread = new capturethread();
	//capThread->start();
	timer = new QTimer(this);
	timer1 = new QTimer(this);
    connect(timer, SIGNAL(timeout()),scene, SLOT(advance()));
	connect(timer1, SIGNAL(timeout()),this, SLOT(timerUpDate()));    
	
	timer->start(50);
	timer1->start(50);	

    //ui->graphicsView->setWindowFlags(Qt::Dialog);
    //ui->graphicsView->showFullScreen();
	//ui->graphicsView->show();


}

Dialog::~Dialog()
{
    delete ui;
	delete timer;
	delete timer1;
	delete item;
	delete scene;
//	delete graphicsView;
//	delete Bclose_dialog;
//	delete capThread;
}


void Dialog::on_pushButton_clicked()
{
    bool xxx = this->close();
    qDebug() << "clicked dialog  " << xxx;
}

void Dialog::timerUpDate()
{
	if( item->getMoveState() > 9) 
	{
			timer->stop();	
			timer1->stop();
			this->close();
			//delete scene;
			//ui->graphicsView->setWindowFlags(Qt::subwindow);
			//ui->graphicsView->resize(800 , 600);
			//ui->setupUi(this);
			//Bclose_dialog = new QPushButton("close" , this);
			//Bclose_dialog->move( 300 , 200);			
			//connect( Bclose_dialog , SIGNAL(clicked()),
			//	this , SLOT(close()));
	}
}

std::vector<int>  Dialog::returnPCablibrationX()
{
	//9个点的标定,顺便return pont
	for(int i = 0 ; i < 9; i++)
	{
		switch ( i )
		{
		case 0:			
			
			PCablibrationX.push_back( 0 );
			break;
		case 1:	
			
			PCablibrationX.push_back( 0 );
			break;
		case 2:
			
			PCablibrationX.push_back( 0 );
			break;
		case 3:
			
			PCablibrationX.push_back( ui->graphicsView->width()/2 - 2 );
		case 4:
			PCablibrationX.push_back( ui->graphicsView->width()/2 - 2 );
			break;
		case 5:
			PCablibrationX.push_back( ui->graphicsView->width()/2 - 2 );
			break;
		case 6:
			PCablibrationX.push_back( ui->graphicsView->width() - 2 - 30 );
			break;
		case 7:			
			PCablibrationX.push_back( ui->graphicsView->width() - 2 - 30 );
			break;
		case 8:
			PCablibrationX.push_back( ui->graphicsView->width() - 2 - 30 );
			break;
	}
	}

	return PCablibrationX;
}

std::vector<int>  Dialog::returnPCablibrationY()
{
	for(int i=0 ; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			PCablibrationY.push_back( 0 );
			break;
		case 1:
			PCablibrationY.push_back( ui->graphicsView->height()/2 - 2);			
			break;
		case 2:
			PCablibrationY.push_back( ui->graphicsView->height() - 2 - 30 );		
			break;
		case 3:
			PCablibrationY.push_back( 0 );		
			break;
		case 4:
			PCablibrationY.push_back( ui->graphicsView->height()/2 -2);		
			break;
		case 5:
			PCablibrationY.push_back( ui->graphicsView->height() - 2 - 30 );		
			break;
		case 6:
			PCablibrationY.push_back( 0 );		
			break;
		case 7:
			PCablibrationY.push_back( ui->graphicsView->height()/2 - 2);		
			break;
		case 8:
			PCablibrationY.push_back( ui->graphicsView->height() -2 - 30 );		
			break;
	}
	}
	return PCablibrationY;

}

std::vector<cv::Point> Dialog::returnPCablibration()
{
	for(int i = 0 ; i < 9 ; i ++)
	{
		cv::Point tmp;
		switch ( i )
		{
		case 0:	
			PCablibration.push_back(cv::Point( 0 ,0 ));
			break;
		case 1:	
			
			PCablibration.push_back(cv::Point( 0 ,  ui->graphicsView->height()/2 - 2));
			break;
		case 2:
			
			PCablibration.push_back(cv::Point( 0 , ui->graphicsView->height() - 2 - 30 ));
			break;
		case 3:
			
			PCablibration.push_back(cv::Point( ui->graphicsView->width()/2 - 2 , 0 ));
			break;
		case 4:
			PCablibration.push_back(cv::Point( ui->graphicsView->width()/2 - 2 ,  ui->graphicsView->height()/2 - 2));
			break;
		case 5:
			PCablibration.push_back(cv::Point( ui->graphicsView->width()/2 - 2 , ui->graphicsView->height() - 2 - 30 ));
			break;
		case 6:
			PCablibration.push_back(cv::Point(ui->graphicsView->width() - 2 - 30  , 0 ));
			break;
		case 7:			
			PCablibration.push_back(cv::Point(ui->graphicsView->width() - 2 - 30 , ui->graphicsView->height()/2 - 2));
			break;
		case 8:
			PCablibration.push_back(cv::Point(ui->graphicsView->width() - 2 - 30 ,  ui->graphicsView->height() - 2 - 30 ));
			break;
	}
	}
	return PCablibration;
}
