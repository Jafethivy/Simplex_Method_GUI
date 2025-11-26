#include "Boxes.h"

Boxes::Boxes(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Boxes::~Boxes()
{}

/*
hemos dejado el proyecto hasta aqui, debes continuar desde este punto
falta:
logica para llamar a las cajas y que se arreglen dinamicamente con el widget en 
objetive.cpp

objetive.cpp ya contiene variables importantes como vars y rest que indican
la cantidad de variables y restricciones, con ello vas a determinar la cantidad
de cajas que se deben crear en el widget de objetive

*/