#include <iostream>
#include "Minimization.h"
#include "Matrix.h"
#include <QDebug>

void start_minimization(Matrix& m, callback_itr callback) {
	Iteration itr;
	fill_slack_min(m);
	itr.table = m.table_getter();
	callback(itr);
	while (!optimal_solution_min(m)) {
		pivoting_min(m, itr);
		m.iteration_setter();
		itr.table = m.table_getter();
		callback(itr);
	}
}

void pivoting_min(Matrix& m, Iteration itr) {
	int piv_col = det_piv_column_min(m);
	int piv_row = det_piv_row_min(m, piv_col);
	itr.piv_col = piv_col;
	itr.piv_row = piv_row;
	row_pivot_iterate_min(m, piv_row, piv_col);
	col_iterate_min(m, piv_row, piv_col);
}

void fill_slack_min(Matrix& m) {
	fill_i_min(m);
}
void fill_j_min(int i, Matrix& m) {
	for (int j = m.vars_getter(); j < m.cols_getter() - 1; j++) {
		if (j - m.vars_getter() == i - 1) m.values_setter(i, j, 1);
		else m.values_setter(i, j, 0);;
	}
}
void fill_i_min(Matrix& m) {
	for (int i = 1; i < m.rows_getter(); i++) {
		fill_j_min(i, m);
	}
}

int det_piv_column_min(Matrix& m) {
	int piv_col = 0;
	double most_pos = 0;
	for (int j = 0; j < m.cols_getter() - 1; j++) {
		if (m.get_value(0, j) > most_pos) {
			most_pos = m.get_value(0, j);
			piv_col = j;
		}
	}
	return piv_col;
}
int det_piv_row_min(Matrix& m, int piv_col) {
	int piv_row = 1;
	const int it_cols = m.cols_getter() - 1;
	double val_min = m.get_value(1, it_cols) / m.get_value(1, piv_col);
	if (val_min < 0) {
		val_min = std::numeric_limits<double>::infinity();
	}
	for (int i = 1; i < m.rows_getter(); i++) {
		double ratio = m.get_value(i, it_cols) / m.get_value(i, piv_col);
		if (ratio < val_min && ratio >= 0) {
			val_min = ratio;
			piv_row = i;
		}
	}
	return piv_row;
}

void row_pivot_iterate_min(Matrix& m, int piv_row, int piv_col) {
	double piv_value = m.get_value(piv_row, piv_col);
	for (int j = 0; j < m.cols_getter(); j++) {
		m.values_setter(piv_row, j, m.get_value(piv_row, j) / piv_value);
	}

}
void col_iterate_min(Matrix& m, int piv_row, int piv_col) {
	for (int i = 0; i <= m.rest_getter(); i++) {
		double multiplier = m.get_value(i, piv_col);
		if (i == piv_row) { continue; }
		for (int j = 0; j < m.cols_getter(); j++) {
			double pivoted_value = m.get_value(piv_row, j);
			double new_value = m.get_value(i, j) - (multiplier * pivoted_value);
			m.values_setter(i, j, new_value);
		}
	}
}

bool optimal_solution_min(Matrix& m) {
	for (int j = 0; j < m.cols_getter() - 1; j++) {
		if (m.get_value(0, j) > 0) {
			return false;
		}
	}
	return true;
}
