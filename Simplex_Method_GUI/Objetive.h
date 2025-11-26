#pragma once

#include <QWidget>
#include "ui_Objetive.h"

class Objetive : public QWidget
{
	Q_OBJECT

public:
	Objetive(QWidget *parent = nullptr);
	~Objetive();

	void set_vars_rests(int v, int r);

signals:
	void signal_previous_window(int index);
	void signal_destroy_matrix();

private slots:
	void on_Editar_button_clicked();

private:
	Ui::Objetive ui;
	int vars, rest;
};

