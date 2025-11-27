#include "Boxes.h"

Boxes::Boxes(const QString &x_number,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.x_n->setText(x_number);
}

Boxes::~Boxes()
{}


void Boxes::plus_visible() {
	ui.plus->setText("");
}

double Boxes::box_value() const{
	return ui.box->value();
}