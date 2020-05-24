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

class QtGuiApplication2 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication2(QWidget *parent = Q_NULLPTR);
	QPixmap pix[6];
	QImage img[6];
	QPixmap pixs[6];
	double f = 1200;
	int number = 0;

private:
	Ui::QtGuiApplication2Class ui;
	

public slots:
	void
		ones();// check number of the image & exception handling
	void
		button2();
};

