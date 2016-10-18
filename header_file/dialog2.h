#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <Qtimer>
#include <Qtime>
#include <opencv2\opencv.hpp>
#include <opencv2\ml\ml.hpp>
#include "testItem.h"
#include "regressionItem.h"
namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();
    
private:
    Ui::Dialog2 *ui;

    QGraphicsScene *scene;
	QGraphicsView *graphicsView;
	QTimer *timer1 , *timer2;
	testItem *myitem;
	regressionItem *myitem2;
	//CvSVM myRegresserX, myRegresserY;
	
};
#endif // DIALOG_H