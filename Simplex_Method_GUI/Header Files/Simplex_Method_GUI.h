#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simplex_Method_GUI.h"

class Setter;
class Objetive;
class Matrix;

class Simplex_Method_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Simplex_Method_GUI(QWidget *parent = nullptr);
    ~Simplex_Method_GUI();

	void init_matrix(int& vars, int& rest);
	void call_destuctor();

	void set_boxes();	

	void solve_matrix();

private:
    Ui::Simplex_Method_GUIClass ui;

	Setter* setterWindow = nullptr;
	Objetive* objetiveWindow = nullptr;

	Matrix* m = nullptr;
};