#include "Objetive.h"

Objetive::Objetive(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	

}

Objetive::~Objetive()
{}

void Objetive::on_Editar_button_clicked(){
	emit signal_destroy_matrix();
	emit signal_previous_window(0);
}

void Objetive::set_vars_rests(int v, int r) {
	vars = v;
	rest = r;
}