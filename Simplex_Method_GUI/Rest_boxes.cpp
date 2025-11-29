#include "Rest_boxes.h"

Rest_boxes::Rest_boxes(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Rest_boxes::~Rest_boxes()
{}

double Rest_boxes::box_rest_value() const{
	return ui.result_n->value();
}
