#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "myitem.h"
#include <QPushButton>
#include "capturethread.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
	std::vector<int>  returnPCablibrationX();
	std::vector<int>  returnPCablibrationY();
	std::vector<cv::Point> returnPCablibration();
    ~Dialog();

private slots:
    void on_pushButton_clicked();
	void timerUpDate();
private:
	MyItem *item;
    Ui::Dialog *ui;
    QGraphicsScene *scene;	
	QGraphicsView *graphicsView;
	QTimer *timer , *timer1;
	QPushButton *Bclose_dialog;
	capturethread *capThread;
	std::vector<int> PCablibrationX,PCablibrationY;
	std::vector<cv::Point> PCablibration;
};

#endif // DIALOG_H
