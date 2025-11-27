#pragma once

#include <QWidget>
#include "ui_Rest_boxes.h"

class Rest_boxes : public QWidget
{
	Q_OBJECT

public:
	Rest_boxes(QWidget *parent = nullptr);
	~Rest_boxes();

	double box_rest_value() const;
private:
	Ui::Rest_boxesClass ui;
};

