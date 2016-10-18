#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{

    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
	ui->graphicsView->setWindowFlags(Qt::Dialog);
    ui->graphicsView->showFullScreen();
	// 减2是避免出现上下的滚动条
	scene->setSceneRect(0, 0, 
		ui->graphicsView->width() - 2 , ui->graphicsView->height() - 2);
	myitem = new testItem(ui->graphicsView->height(), ui->graphicsView->width());
	myitem2 = new regressionItem(ui->graphicsView->height(), ui->graphicsView->width());
    //item->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    //item->setPos(0, 0);
	scene->addItem(myitem);	
	scene->addItem(myitem2);

	timer1 = new QTimer(this);
	//timer2 = new QTimer(this);
	connect(timer1 , SIGNAL(timeout()),scene,SLOT(advance()));
	//connect(timer2 , SIGNAL(timeout()),scene,SLOT(myitem2->advance()));
	timer1->start(500);

}

Dialog2::~Dialog2()
{
    delete ui;
}