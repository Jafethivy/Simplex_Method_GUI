#include "Setter.h"


Setter::Setter(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Setter::~Setter()
{}


void Setter::on_Generate_button_clicked(){
	int variable = ui.Variable_box->value();
	int restrictions = ui.Restriction_box->value();
	if (variable < 2 || restrictions < 2) { return; }

	emit signal_init_matrix(variable, restrictions);
	emit signal_set_boxes();
	emit signal_next_window(1);
}