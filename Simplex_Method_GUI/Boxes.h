#pragma once

#include <QWidget>
#include "ui_Boxes.h"

class Boxes : public QWidget
{
	Q_OBJECT

public:
	Boxes(QWidget *parent = nullptr);
	~Boxes();

private:
	Ui::BoxesClass ui;
};

