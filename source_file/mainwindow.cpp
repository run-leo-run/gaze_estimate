#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include "myitem.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_childwindow_clicked()
{
    //qDebug() <<"clicked mainwindow ";
    this->hide();
    dialog1 = new Dialog();
    dialog1->setWindowFlags(Qt::Dialog);
    dialog1->showFullScreen();

    dialog1->show();
    dialog1->exec();
	this->PCablibrationX = dialog1->returnPCablibrationX();
	this->PCablibrationY = dialog1->returnPCablibrationY();
	this->PCablibration = dialog1->returnPCablibration();

	//第二次calibration 时会有Access violation，注意，暂时不知道原因，估计是线程的问题
	
	delete dialog1;
	//dialog1->hide();

    this->show();
}

void MainWindow::on_SVRtrain_clicked()
{
	//训练svm，1、提取数据 2、做成矩阵 3、svm训练
	//test
	cv::Mat testFrame;
	cv::Mat trainData( 45 , 12 , CV_32FC1);
	cv::Mat trainLabelX( 45 , 1 , CV_32FC1);
	cv::Mat trainLabelY(45 , 1, CV_32FC1);
	int tmp = 0;
	String s;
	detector = new MyDetector();
	for(int i = 0 ; i < 9;i++)
		for(int j = 0; j < 5; j++)
		{
			std::vector<cv::Point> feature;
			s = std::to_string(i) + std::to_string(j) + ".jpg";
			testFrame = cv::imread(s);
			detector->detectAndDisplay( testFrame );
			feature = detector->returnFeature();
			trainData.at<float>(tmp , 0) = feature.at(0).x;
			trainData.at<float>(tmp , 1) = feature.at(0).y;
			trainData.at<float>(tmp , 2) = feature.at(1).x;
			trainData.at<float>(tmp , 3) = feature.at(1).y;
			trainData.at<float>(tmp , 4) = feature.at(2).x;
			trainData.at<float>(tmp , 5) = feature.at(2).y;
			trainData.at<float>(tmp , 6) = feature.at(3).x;
			trainData.at<float>(tmp , 7) = feature.at(3).y;
			trainData.at<float>(tmp , 8) = feature.at(4).x;
			trainData.at<float>(tmp , 9) = feature.at(4).y;
			trainData.at<float>(tmp , 10) = feature.at(5).x;
			trainData.at<float>(tmp , 11) = feature.at(5).y;
			
			trainLabelX.at<float>(tmp , 0) = PCablibration.at(tmp/5).x;
			trainLabelY.at<float>(tmp , 0) = PCablibration.at(tmp/5).y;

			tmp++;
		}
	CvSVMParams param;
	param.svm_type = CvSVM::EPS_SVR;
	param.kernel_type = CvSVM::LINEAR;
	param.C = 1;
	param.p = 1e-7;
	param.gamma = 0.1;	

	CvSVM regresserX,regresserY;
	regresserX.train(trainData, trainLabelX, Mat(), Mat(), param);
	regresserY.train(trainData, trainLabelY, Mat(), Mat(), param);

	regresserX.save("Xsvm_model.xml");
	regresserY.save("Ysvm_model.xml");
	//cout << "Finished the training process now" <<endl;
	QMessageBox msgBox;
	msgBox.setWindowTitle("training finished");
	msgBox.setText("training finished");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.setDefaultButton(QMessageBox::No);
	if(msgBox.exec() == QMessageBox::Yes){
	  ;// do something
	}else {
	  ;// do something else
	}
		
}

void MainWindow::on_test_clicked()
{
	this->hide();
	dialog2 = new Dialog2();
	dialog2->setWindowFlags(Qt::Dialog);
    dialog2->showFullScreen();
    dialog2->show();
    dialog2->exec();

    this->show();

	

}
