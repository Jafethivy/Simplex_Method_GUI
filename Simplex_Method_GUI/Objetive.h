#pragma once

#include <QWidget>
#include <QQueue>
#include <QString>
#include "ui_Objetive.h"

class Boxes;
class Rest_boxes;

class Objetive : public QWidget
{
	Q_OBJECT

public:
	Objetive(QWidget *parent = nullptr);
	~Objetive();

	void set_amount_boxes(int amount_boxes);
	void set_amount_rest(int amount_rest);

	void create_boxes_z(int amount_boxes);
	void clear_boxes_z();

	void create_boxes_rest(int amount_boxes, int amount_rest);
	void clear_boxes_r1();
	void clear_boxes_r2();

	bool get_objetive();
	void get_values_z();
	void get_values_r();

	void solve_matrix();

	void clear();

signals:
	void signal_previous_window(int index);
	void signal_next_window(int index);
	void signal_destroy_matrix();

	void signal_set_values_matrix(QVector<double>& z_values,QQueue<double>& r_values,QQueue<double>& results_values);
	void signal_set_objetive(bool objetive);

	void signal_solution();

private slots:
	void on_Editar_button_clicked();
	void on_Solve_button_clicked();

private:
	Ui::Objetive ui;
	int amount_boxes= 0;
	int amount_rest = 0;

	QVector<Boxes*> z_list;
	QHBoxLayout* z_layout = nullptr;

	QVector<Boxes*> r_list;
	QVector<Rest_boxes*> rest_list;
	QVBoxLayout* r2_layout = nullptr;
	QHBoxLayout* r_layout = nullptr;

	QVector<double> z_values;
	QQueue<double> r_values;
	QQueue<double> results_values;
};

 