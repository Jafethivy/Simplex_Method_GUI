#pragma once

#include <QWidget>
#include <QTableWidget>
#include "ui_Final_solution.h"
#include "Iteration.h"

class Final_solution : public QWidget
{
	Q_OBJECT

public:
	Final_solution(QWidget *parent = nullptr);
	~Final_solution();

	void set_dimensions(int r, int c);
	void set_itr_values(QVector<Iteration> itr);

	QTableWidget* create_table(int n, QWidget* parent);
	QLabel* create_label(int i, QWidget* parent);
	QLabel* create_info(int i, QWidget* parent);

	void table_size(QTableWidget* table);
	void style_table(QTableWidget* table, QStringList cols_str, QStringList rows_str);

	QVBoxLayout* create_base(int i, QWidget* parent);
	QTableWidget* init_table(int i, QWidget* parent);

	void display_table();

	void clear();

signals:

	void signal_new_problem();
	void signal_previous_window(int index);
	void signal_edit_problem();

private slots:

	void on_Editar_button_clicked();
	void on_New_button_clicked();

private:
	Ui::Final_solutionClass ui;

	QVBoxLayout* display_layout = nullptr;

	int rows = 0;
	int cols = 0;

	int rest = 0;
	int vars = 0;

	QVector<QString> vars_in;
	QVector<QString> rest_in;

	QVector<Iteration> iterations;

	QVector<QString> inputs;
	QVector<int>outputs;
};

