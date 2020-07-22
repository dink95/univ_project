#include "QtGuiApplication2.h"



QtGuiApplication2::QtGuiApplication2(QWidget* parent)
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
	QAction* set = new QAction(tr("set focal"), this);
	connect(projec, SIGNAL(triggered()), this, SLOT(button2()));
	connect(set, SIGNAL(triggered()), this, SLOT(setf()));
	menu = menuBar()->addMenu(tr("Projection"));
	menu->addAction(projec);
	menu->addAction(set);

	QAction* k = new QAction(tr("keypoint"), this);
	connect(k, SIGNAL(triggered()), this, SLOT(keypoint()));
	menu = menuBar()->addMenu(tr("keypoint"));
	menu->addAction(k);

	QAction* r = new QAction(tr("stitch"), this);
	connect(r, SIGNAL(triggered()), this, SLOT(stich()));
	menu = menuBar()->addMenu(tr("stitch"));
	menu->addAction(r);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(push1()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(push2()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(push3()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(push4()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(push5()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(push6()));

}
//projection
void QtGuiApplication2::ones()
{
	second sec;
	sec.exec();
	number = sec.num;
	if (number > 0 || number < 7)
	{
		for (int i = 0; i < number; i++)
		{
			
			QFileDialog dlg;
			QString filePath = dlg.getOpenFileName(this, "Load Image", "", "Image Files (*.*)");
			img[i].load(filePath);
			string text = filePath.toLocal8Bit().constData();
			s.push_back(imread(text));
		}
		for (int i = 0; i < 6; i++)
			pix[i] = QPixmap::fromImage(img[i]);
	}
	else
	{
		QMessageBox::information(this, "Title", "Please put in 1 to 6 images.");
	}
}
void QtGuiApplication2::setf()
{
	foca fo;
	fo.exec();
	f = fo.num;

}

//project
void QtGuiApplication2::button2()
{
	projectflag = 1;
	keyflag = 0;
	int hei = img[0].height();//row
	int wid = img[0].width();//coul
	//create empty image same with insert
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
				double cx = f * tan(x / f) + half_wid;
				double cy = half_hei + (y * sqrt((x * x) + (f * f)) / f);

				if (cx<0 || cy<0 || cx>half_wid * 2 || cy>half_hei * 2)
					continue;

				//interpolation 
				double xr = cx - (int)cx;
				double yr = cy - (int)cy;
				QColor a1 = img[count].pixelColor(cx, cy);
				QColor a2 = img[count].pixelColor(cx + 1, cy);
				QColor a3 = img[count].pixelColor(cx, cy + 1);
				QColor a4 = img[count].pixelColor(cx + 1, cy + 1);
				QColor p1((a2.red() - a1.red()) * xr + a1.red(), (a2.green() - a1.green()) * xr + a1.green(), (a2.blue() - a1.blue()) * xr + a1.blue());
				QColor p2((a4.red() - a3.red()) * xr + a3.red(), (a4.green() - a3.green()) * xr + a3.green(), (a4.blue() - a3.blue()) * xr + a3.blue());
				QColor res((p2.red() - p1.red()) * yr + p1.red(), (p2.green() - p1.green()) * yr + p1.green(), (p2.blue() - p1.blue()) * yr + p1.blue());

				cylin[count].setPixelColor(i, j, res);

			}
		}
	}
	//set projection image to label
	for (int i = 0; i < number; i++)
		pixs[i] = QPixmap::fromImage(cylin[i]);



}
//image 1
void QtGuiApplication2::push1()
{
	int w = ui.label->width();
	int h = ui.label->height();
	ui.label->setPixmap(pix[0].scaled(w, h, Qt::KeepAspectRatio));
	if (projectflag == 1)
		ui.label_2->setPixmap(pixs[0].scaled(w, h, Qt::KeepAspectRatio));
	if (keyflag == 1)
		ui.label_2->setPixmap(keys[0].scaled(w, h, Qt::KeepAspectRatio));
}
//image 2
void QtGuiApplication2::push2()
{
	if (number > 1)
	{
		int w = ui.label->width();
		int h = ui.label->height();
		ui.label->setPixmap(pix[1].scaled(w, h, Qt::KeepAspectRatio));
		if (projectflag == 1)
			ui.label_2->setPixmap(pixs[1].scaled(w, h, Qt::KeepAspectRatio));
		if (keyflag == 1)
			ui.label_2->setPixmap(keys[1].scaled(w, h, Qt::KeepAspectRatio));
	}
}
//image 3
void QtGuiApplication2::push3()
{
	if (number > 2)
	{
		int w = ui.label->width();
		int h = ui.label->height();
		ui.label->setPixmap(pix[2].scaled(w, h, Qt::KeepAspectRatio));
		if (projectflag == 1)
			ui.label_2->setPixmap(pixs[2].scaled(w, h, Qt::KeepAspectRatio));
		if (keyflag == 1)
			ui.label_2->setPixmap(keys[2].scaled(w, h, Qt::KeepAspectRatio));
	}
}
//image 4
void QtGuiApplication2::push4()
{
	if (number > 3)
	{
		int w = ui.label->width();
		int h = ui.label->height();
		ui.label->setPixmap(pix[3].scaled(w, h, Qt::KeepAspectRatio));
		if (projectflag == 1)
			ui.label_2->setPixmap(pixs[3].scaled(w, h, Qt::KeepAspectRatio));
		if (keyflag == 1)
			ui.label_2->setPixmap(keys[3].scaled(w, h, Qt::KeepAspectRatio));
	}
}
//image 5
void QtGuiApplication2::push5()
{
	if (number > 4)
	{
		int w = ui.label->width();
		int h = ui.label->height();
		ui.label->setPixmap(pix[4].scaled(w, h, Qt::KeepAspectRatio));
		if (projectflag == 1)
			ui.label_2->setPixmap(pixs[4].scaled(w, h, Qt::KeepAspectRatio));
		if (keyflag == 1)
			ui.label_2->setPixmap(keys[4].scaled(w, h, Qt::KeepAspectRatio));
	}
}
//image 6
void QtGuiApplication2::push6()
{
	if (number > 5)
	{
		int w = ui.label->width();
		int h = ui.label->height();
		ui.label->setPixmap(pix[5].scaled(w, h, Qt::KeepAspectRatio));
		if (projectflag == 1)
			ui.label_2->setPixmap(pixs[5].scaled(w, h, Qt::KeepAspectRatio));
		if (keyflag == 1)
			ui.label_2->setPixmap(keys[5].scaled(w, h, Qt::KeepAspectRatio));
	}
}
//keypoint
void QtGuiApplication2::keypoint()
{
	//choose print on label 2
	projectflag = 0;
	keyflag = 1;
	int h = img[0].height();//row
	int w = img[0].width();//coulm



	///set scale & Initialization
	for (int i = 0; i < number; i++)
	{
		keyp[i] = QImage(w, h, QImage::Format_RGB32);
		keyp[i].fill(0);//fill color black
	}

	//gausssian smoothing mask
	//delete noise from image
	int mask[3][3] = { {1,2,1},{2,4,2},{1,2,1} };

	for (int count = 0; count < number; count++)
	{
		for (int i = 1; i < w - 1; i++)
		{
			for (int j = 1; j < h - 1; j++)
			{
				int r = 0, g = 0, b = 0;
				for (int mr = 0; mr < 3; mr++) {
					for (int mc = 0; mc < 3; mc++)
					{
						r += (mask[mr][mc] * cylin[count].pixelColor(i + mr - 1, j + mc - 1).red());
						g += (mask[mr][mc] * cylin[count].pixelColor(i + mr - 1, j + mc - 1).green());
						b += (mask[mr][mc] * cylin[count].pixelColor(i + mr - 1, j + mc - 1).blue());
					}
				}//end of mr 3x3
				QColor res((double)r / 16, (double)g / 16, (double)b / 16);//Distribute to the sum of the masks.
				keyp[count].setPixelColor(i, j, res);

			}//end of j
		}
	}

	//rgb to grayscale
	for (int count = 0; count < number; count++)
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				QColor color;
				double gray;
				color = keyp[count].pixelColor(i, j);
				gray = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
				color.setRgb(gray, gray, gray);
				keyp[count].setPixelColor(i, j, color);
			}
		}
	}
	//sobel mask 
	int sx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	int sy[3][3] = { {1, 2, 1},{0, 0, 0},{-1,-2,-1} };
	//loop 
	for (int count = 0; count < number; count++)
	{
		gx = new int* [h];
		for (int i = 0; i < h; i++) {
			gx[i] = new int[w];
		}
		int** padding_result = padding(keyp[count], w, h);
		for (int i = 1; i < h + 1; i++) {
			for (int j = 1; j < w + 1; j++) {
				int newx = 0;
				newx = sx[0][0] * padding_result[i - 1][j - 1] +sx[0][1] * padding_result[i - 1][j] +
					sx[0][2] * padding_result[i - 1][j + 1] +sx[1][0] * padding_result[i][j - 1] +
					sx[1][1] * padding_result[i][j] +sx[1][2] * padding_result[i][j + 1] +
					sx[2][0] * padding_result[i + 1][j - 1] +sx[2][1] * padding_result[i + 1][j] +
					sx[2][2] * padding_result[i + 1][j + 1];

				gx[i - 1][j - 1] = newx;

			}
		}
		//allocate dynanic 2D ARRAY
		gy = new int* [h];
		for (int i = 0; i < h; i++) {
			gy[i] = new int[w];
		}

		for (int i = 1; i < h + 1; i++) {
			for (int j = 1; j < w + 1; j++) {
				int newy = 0;
				newy = sy[0][0] * padding_result[i - 1][j - 1] +sy[0][1] * padding_result[i - 1][j] +
					sy[0][2] * padding_result[i - 1][j + 1] +sy[1][0] * padding_result[i][j - 1] +
					sy[1][1] * padding_result[i][j] +sy[1][2] * padding_result[i][j + 1] +sy[2][0] * 
					padding_result[i + 1][j - 1] +sy[2][1] * padding_result[i + 1][j] +
					sy[2][2] * padding_result[i + 1][j + 1];
				gy[i - 1][j - 1] = newy;

			}
		}

		//dynamic allocation & set 0
		int** hold = new int* [h];
		for (int i = 0; i < h; i++) {
			hold[i] = new int[w];
			memset(hold[i], 0, sizeof(int) * w);

		}

		for (int i = 1; i < h - 1; i++) {
			for (int j = 1; j < w - 1; j++)
			{
				int Ix = 0, Iy = 0, IxIy = 0;
				float k = 0.04;
				int deter = 0, trace = 0, threshold = 0;
				QVector<int> x_9;
				QVector<int> y_9;
				x_9.clear();
				y_9.clear();
				
				//3x3 data for Harris Corner
				for (int a = -1; a < 2; a++) {
					for (int b = -1; b < 2; b++) {
						x_9.push_back(gx[i + a][j + b]);  
						y_9.push_back(gy[i + a][j + b]);  
					}
				}
				for (int k = 0; k < 9; k++) 
				{
					int temp_x = 0, temp_y = 0;
					temp_x = x_9.at(k);
					temp_y = y_9.at(k);
					Ix += temp_x * temp_x;
					IxIy += temp_x * temp_y;
					Iy += temp_y * temp_y;
				}
				//calculate the R
				deter = (Ix * Iy) - (IxIy * IxIy);
				trace = pow((Ix + Iy), 2);
				threshold = deter - (k * trace);

				if (threshold > 1000000000) 
				{
					hold[i][j] = threshold;
				}


			}//end of j
		}//end of i
		int** result;
		//initialize Dynamic allocation of 2D arrays
		result = new int* [h];
		for (int i = 0; i < h; i++) {
			result[i] = new int[w];
			memset(result[i], 0, sizeof(int)* w);
		}
		//non maximum 3x3
		for (int i = 1; i < h - 1; i++) {
			for (int j = 1; j < w - 1; j++) {
				int center = hold[i][j];
				//if center is larger than 3x3 near pixel then, keep result
				result[i][j] = hold[i][j];
				//but if center is smaller than n 3x3 near pixel then, result turn to zero
				for (int a = -1; a < 2; a++) {
					for (int b = -1; b < 2; b++) {
					 if ((a != 0) && (b != 0))
						{
							int vtemp = hold[i + a][j + b];
							if (vtemp > center) {
								result[i][j] = 0;
							}
						}
					}
				}
			}
		}
		// if result have value , it is keypoint
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (result[i][j] != 0) {
					keyp[count].setPixelColor(j, i, QColor(255, 0, 0));
				}
			}
		}

		//solve the dynamic allocation
		for (int i = 0; i < h; i++) {
			delete gx[i];
			delete gy[i];
			delete result[i];
			delete hold[i];
		}
		delete[]gx;
		delete[]gy;
		delete[]result;
		delete[]hold;

	}
	for (int i = 0; i < number; i++)
		keys[i] = QPixmap::fromImage(keyp[i]);
}

//Extend for sobel
int** QtGuiApplication2::padding(QImage keyp, int w, int h)
{
	int sizeh = h + 2;
	int sizew = w + 2;
	int** pad = new int* [sizeh];

	for (int i = 0; i < h + 2; i++) {
		pad[i] = new int[sizew];
	}

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			pad[i + 1][j + 1] = keyp.pixelColor(j, i).red();

	for (int i = 0; i < w; i++) {
		pad[0][i + 1] = keyp.pixelColor(i, 0).red();
		pad[h + 1][i + 1] = keyp.pixelColor(i, h - 1).red();
	}

	for (int i = 0; i < h; i++) {
		pad[i + 1][0] = keyp.pixelColor(0, i).red();
		pad[i + 1][w + 1] = keyp.pixelColor(w - 1, i).red();
	}


	pad[0][0] = keyp.pixelColor(0, 0).red();
	pad[h + 1][0] = keyp.pixelColor(0, h - 1).red();
	pad[0][w + 1] = keyp.pixelColor(w - 1, 0).red();
	pad[h + 1][w + 1] = keyp.pixelColor(w - 1, h - 1).red();


	return pad;
}

void QtGuiApplication2::stich()
{
	///cylinderical projection image  panorama/////////////
	for (int i = 0; i < number; i++) //change qimage to mat
	{
		Mat b;
		b = Qtomat(cylin[i]);//use q image to mat func 
		Po.push_back(b);//in to vector
	}
	///use sticher to make panorama 
	Mat proresult;
	Ptr<Stitcher> sti = Stitcher::create(Stitcher::PANORAMA);
	sti->stitch(Po, proresult);
	imwrite("clider.jpg", proresult);
	//change mat to qimage 
	QImage toq = mattoQ(proresult);
	QPixmap topix = QPixmap::fromImage(toq);//image to pixmap
	/// draw in label 1down side
	int w = ui.label->width();
	int h = ui.label->height();
	ui.label->setPixmap(topix.scaled(w, h, Qt::KeepAspectRatio));

	////////////orignal image projection/////////////////////
	Mat res;
	Ptr<Stitcher> sticher = Stitcher::create(Stitcher::PANORAMA);
	sticher->stitch( s, res);
	imwrite("result.jpg",res);
	//draw in label_2 down side
	QImage q = mattoQ(res);
	QPixmap qpix=QPixmap::fromImage(q);
	ui.label_2->setPixmap(qpix.scaled(w, h, Qt::KeepAspectRatio));




}