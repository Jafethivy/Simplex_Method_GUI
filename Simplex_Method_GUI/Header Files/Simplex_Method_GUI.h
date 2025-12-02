#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simplex_Method_GUI.h"

class Setter;
class Objetive;
class Final_solution;
class Matrix;
struct Iteration;

class Simplex_Method_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Simplex_Method_GUI(QWidget *parent = nullptr);
    ~Simplex_Method_GUI();

	void init_matrix(int& vars, int& rest);
	void call_destructor();

	void set_boxes();	

	void set_values_matrix(QVector<double>& z_values,QQueue<double>& r_values, QQueue<double>& results_values) const;
	void set_objetive(bool objetive);

	void debug();

	void new_problem();
	void edit_problem();
	void exceptions();

	void showError(const QString& title, const QString& message);

	QVector<Iteration> itr_getter();
private:
    Ui::Simplex_Method_GUIClass ui;

	Setter* setterWindow = nullptr;
	Objetive* objetiveWindow = nullptr;
	Final_solution* solutionWindow = nullptr;

	Matrix* m;
	QVector<Iteration> iterations;
};