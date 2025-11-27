#pragma once

#include <QWidget>
#include "ui_Boxes.h"

class Boxes : public QWidget
{
	Q_OBJECT

public:
	Boxes(const QString &x_number,QWidget *parent = nullptr);
	~Boxes();

	void plus_visible();

	double box_value() const;
private:
	Ui::BoxesClass ui;
};
