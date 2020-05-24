#pragma once

#include <QDialog>
#include "ui_second.h"

class second : public QDialog
{
	Q_OBJECT

public:
	second(QWidget *parent = Q_NULLPTR);
	~second();
	//for flag about second dialogue
	int num = 0;

private:
	Ui::second sec;


public slots:
	void 
		button();
};
