#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "ui_QtGuiApplication2.h"
#include <qfiledialog.h>
#include <QtWidgets/QDialog>
#include <QString>
#include <QMatrix>
#include "second.h"
#include <QImage>
#include <QFile>
#include <QByteArray>
#include <QMenuBar> 
#include <QStatusBar>
#include <QAction>
#include<cstring>
#include "foca.h"
#include<cmath>
#include<opencv2/opencv.hpp>
#include<opencv2/stitching.hpp>
#include<opencv2/stitching/warpers.hpp>
#include<vector>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include <opencv2/core/mat.hpp>

using namespace cv;
using namespace std;
class QtGuiApplication2 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication2(QWidget *parent = Q_NULLPTR);
	//origin image
	QPixmap pix[6];
	QImage img[6];
	//projection image
	QImage cylin[6];
	QPixmap pixs[6];
	//keypoint image
	QImage keyp[6];
	QPixmap keys[6];
	int** gx;
	int** gy;
	int** hold;
	int** padding(QImage keyp,int w, int h);


	//default focal 
	double f = 1200;
	int number = 0;//count
	int projectflag = 0;
	int keyflag = 0;

	char name[6][40] = { 0, };
	vector<Mat> Po;
	vector<Mat> s;
private:
	Ui::QtGuiApplication2Class ui;
	

public slots:
	void
		ones();// check number of the image & exception handling
	void
		button2();
	void
		setf();
	void
		push1();
	void
		push2();
	void
		push3();
	void
		push4();
	void
		push5();
	void
		push6();
	void
		keypoint();
	void
		stich();

public:
	QImage mattoQ(Mat const& src)//CV mat to QImage
	{
		Mat temp=src; // inintialize temp with input mat  
		cvtColor(src,temp,COLOR_BGR2RGB); // use cvtColor to  
		QImage ima((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
		ima.bits();
		return ima;
	}

	Mat Qtomat(QImage const& src)//qimage to mat
	{
		Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
		Mat result;
		cvtColor(tmp, result,COLOR_RGB2BGR);//qimage use rgb so to bgr
		return result;
	}

};

