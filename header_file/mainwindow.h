#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "dialog2.h"
#include "MyDetector.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_childwindow_clicked();
	void on_SVRtrain_clicked();
	void on_test_clicked();
	//void on_test_clicked();
private:
    Ui::MainWindow *ui;
	Dialog *dialog1;
	Dialog2 *dialog2;
	MyDetector *detector;
	std::vector<int> PCablibrationX,PCablibrationY;
	std::vector<cv::Point> PCablibration;
    //Dialog dialog1;
};

class mySvrFeature
{
public:
	mySvrFeature();
protected:

};

#endif // MAINWINDOW_H


