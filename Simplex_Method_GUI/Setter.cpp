#include "Setter.h"


Setter::Setter(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Setter::~Setter()
{}


void Setter::on_Generate_button_clicked(){ //Esto genera las variables para la inicializacion de matrix
	int variable = ui.Variable_box->value();
	int restrictions = ui.Restriction_box->value();
	if (variable < 2 || restrictions < 2) { return; }

	emit signal_init_matrix(variable, restrictions);// Signal a SMG (Simplex Method GUI.cpp)
	emit signal_next_window(1); // Signal para cambiar de ventana a la siguiente
}