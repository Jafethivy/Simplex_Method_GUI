#pragma once

#include <QWidget>
#include "ui_Setter.h"

class Setter : public QWidget {
	Q_OBJECT

public:
	Setter(QWidget* parent = nullptr);
	~Setter();

signals:
	void signal_init_matrix(int& variable, int& restrictions);
	void signal_next_window(int index);

private slots:
	void on_Generate_button_clicked();

private:
	Ui::SetterClass ui;
};
