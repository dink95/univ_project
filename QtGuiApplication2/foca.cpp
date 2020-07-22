#include "foca.h"

foca::foca(QWidget *parent)
	: QDialog(parent)
{
	foc.setupUi(this);

	connect(foc.pushButton, SIGNAL(clicked()), this, SLOT(button()));

}

foca::~foca()
{
}


void foca::button()
{
	num = foc.lineEdit->text().toDouble();
}
