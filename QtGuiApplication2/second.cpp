#include "second.h"
#include "QtGuiApplication2.h"

second::second(QWidget* parent)
	: QDialog(parent)
{
	sec.setupUi(this);
	//connect button's signal to slot
	connect(sec.pushButton, SIGNAL(clicked()), this, SLOT(button()));


}
second::~second()
{
}
void second::button()
{
	num = sec.lineEdit->text().toInt();
}


