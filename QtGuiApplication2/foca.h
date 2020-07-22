#pragma once

#include <QDialog>
#include "ui_foca.h"

class foca : public QDialog
{
	Q_OBJECT

public:
	foca(QWidget *parent = Q_NULLPTR);
	~foca();
	double num = 0;

private:
	Ui::foca foc;

public slots:
	void
		button();

};
