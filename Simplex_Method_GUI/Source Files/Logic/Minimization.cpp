#include <iostream>
#include "Minimization.h"
#include "Matrix.h"
#include <QDebug>
#include <vector>
#include <cmath>
#include <limits>

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

void pivoting_min(Matrix& m, Iteration& itr) {
	int piv_col = det_piv_column_min(m);
	if (piv_col == -1) {
		return;
	}

	int piv_row = det_piv_row_min(m, piv_col);
	if (piv_row == -1) {
		return;
	}

	itr.piv_col = piv_col;
	itr.piv_row = piv_row;
	itr.iterated = m.get_value(piv_row, piv_col);

	row_pivot_iterate_min(m, piv_row, piv_col);
	col_iterate_min(m, piv_row, piv_col);
}

void fill_slack_min(Matrix& m) {
	fill_i_min(m);
}

void fill_j_min(int i, Matrix& m) {
	for (int j = m.vars_getter(); j < m.cols_getter() - 1; j++) {
		if (j - m.vars_getter() == i - 1) m.values_setter(i, j, 1);
		else m.values_setter(i, j, 0);
	}
}

void fill_i_min(Matrix& m) {
	for (int i = 1; i < m.rows_getter(); i++) {
		fill_j_min(i, m);
	}
}

int det_piv_column_min(Matrix& m) {
	const int cols = m.cols_getter() - 1;
	int best_col = -1;
	double most_pos = 0; // Inicializa en 0

	for (int j = 0; j < cols; ++j) {
		double coef = m.get_value(0, j);
		if (coef > most_pos) {
			most_pos = coef;
			best_col = j;
		}
	}
	return best_col; // Retorna -1 si no hay coeficientes positivos
}

int det_piv_row_min(Matrix& m, int piv_col) {
	const int rows = m.rows_getter();
	const int rhs_col = m.cols_getter() - 1;

	if (piv_col < 0) return -1;

	// Encuentra primer coeficiente positivo válido
	int first_valid_row = -1;
	for (int i = 1; i < rows; ++i) {
		double coeff = m.get_value(i, piv_col);
		if (coeff > 0) {
			first_valid_row = i;
			break;
		}
	}

	if (first_valid_row == -1) return -1;

	double min_ratio = m.get_value(first_valid_row, rhs_col) /
		m.get_value(first_valid_row, piv_col);
	std::vector<int> tied_rows = { first_valid_row };

	// Encuentra todas las filas con ratio mínimo
	const double epsilon = 1e-9;
	for (int i = first_valid_row + 1; i < rows; ++i) {
		double coeff = m.get_value(i, piv_col);
		double rhs_val = m.get_value(i, rhs_col);

		if (coeff <= 0) continue;

		double ratio = rhs_val / coeff;

		if (std::abs(ratio - min_ratio) < epsilon) {
			tied_rows.push_back(i);
		}
		else if (ratio < min_ratio) {
			min_ratio = ratio;
			tied_rows = { i };
		}
	}

	int best_row = tied_rows[0];
	for (size_t k = 1; k < tied_rows.size(); ++k) {
		if (tied_rows[k] < best_row) {
			best_row = tied_rows[k];
		}
	}
	return best_row;
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