#include "QtGuiApplication2.h"



QtGuiApplication2::QtGuiApplication2(QWidget *parent)
	: QMainWindow(parent)
{
	//set mainwindow
	ui.setupUi(this);

	QMenu* menu;
	//open part//
	QAction* openm = new QAction(tr("image"), this);
	connect(openm, SIGNAL(triggered()), this, SLOT(ones()));

	//add new menu
	menu = menuBar()->addMenu(tr("Open"));
	menu->addAction(openm);
	//add new menu
	QAction* projec = new QAction(tr("projection"), this);
	connect(projec, SIGNAL(triggered()), this, SLOT(button2()));
	menu = menuBar()->addMenu(tr("Projection"));
	menu->addAction(projec);
}
//projection
void QtGuiApplication2::ones()
{
	second sec;
	sec.exec();
	number = sec.num;
	if (number>0||number<7)
	{
		for (int i = 0; i < number; i++)
		{
			QFileDialog dlg;
			QString filePath = dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.*)");
			img[i].load(filePath);
		}
		for (int i = 0; i < 6; i++)
			pix[i] = QPixmap::fromImage(img[i]);

		//set image size about label
		int w = ui.label->width();
		int h = ui.label->height();

		ui.label->setPixmap(pix[0].scaled(w, h, Qt::KeepAspectRatio));
		ui.label_2->setPixmap(pix[1].scaled(w, h, Qt::KeepAspectRatio));
		ui.label_3->setPixmap(pix[2].scaled(w, h, Qt::KeepAspectRatio));
		ui.label_4->setPixmap(pix[3].scaled(w, h, Qt::KeepAspectRatio));
		ui.label_5->setPixmap(pix[4].scaled(w, h, Qt::KeepAspectRatio));
		ui.label_6->setPixmap(pix[5].scaled(w, h, Qt::KeepAspectRatio));
	}
	else
	{
		QMessageBox::information(this, "Title", "Please put in 1 to 6 images.");
	}
}
void QtGuiApplication2::button2()
{
	int w = ui.label->width();
	int h = ui.label->height();



	int hei = img[0].height();//row
	int wid = img[0].width();//coul
	//create empty image same with insert
	QImage cylin[6];
	for (int i = 0; i < number; i++)
	{
		cylin[i] = QImage(wid, hei, QImage::Format_RGB888);
		cylin[i].fill(0);//fill color black
	}

	//center position
	double half_wid = wid / 2;
	double half_hei = hei / 2;

	//inverse warping 
	for (int count = 0; count < number; count++)
	{
		for (int j = 0; j < hei; j++)
		{
			for (int i = 0; i < wid; i++)
			{
				double x = i - half_wid;
				double y = j - half_hei;
				int cx = f * tan(x / f) + half_wid;
				int cy = half_hei +(y * sqrt((x * x) + (f * f)) / f);
				QColor colors = img[count].pixel(cx, cy);
				cylin[count].setPixelColor(i, j, colors);

			}
		}
	}
	//set projection image to label
	for (int i = 0; i < number; i++)
		pixs[i] = QPixmap::fromImage(cylin[i]);
	ui.label_7->setPixmap(pixs[0].scaled(w, h, Qt::KeepAspectRatio));
	ui.label_8->setPixmap(pixs[1].scaled(w, h, Qt::KeepAspectRatio));
	ui.label_9->setPixmap(pixs[2].scaled(w, h, Qt::KeepAspectRatio));
	ui.label_10->setPixmap(pixs[3].scaled(w, h, Qt::KeepAspectRatio));
	ui.label_11->setPixmap(pixs[4].scaled(w, h, Qt::KeepAspectRatio));
	ui.label_12->setPixmap(pixs[5].scaled(w, h, Qt::KeepAspectRatio));


}