#include <iostream>
#include "Maximization.h"
#include "Matrix.h"
#include <vector>
#include <cmath>
#include <limits>

void start_maximization(Matrix& m, callback_itr callback) {
	Iteration itr;
	define_z(m);
	fill_slack(m);
	itr.table = m.table_getter();
	callback(itr);
	while (!optimal_solution(m)) {
		pivoting(m, itr);
		m.iteration_setter();
		itr.table = m.table_getter();
		callback(itr);
	}
}

void pivoting(Matrix& m, Iteration itr) {
	int piv_col = det_piv_column(m);
	if (piv_col == -1) {
		// Óptimo alcanzado
		return;
	}

	int piv_row = det_piv_row(m, piv_col);
	if (piv_row == -1) {
		// Manejar problema no acotado
		return;
	}

	itr.piv_col = piv_col;
	itr.piv_row = piv_row;
	row_pivot_iterate(m, piv_row, piv_col);
	col_iterate(m, piv_row, piv_col);
}

void define_z(Matrix& m) {
	for (int j = 0; j < m.vars_getter(); j++) {
		double value_new = -m.get_value(0, j);
		m.Z_setter(j, value_new);
	}
}

void fill_slack(Matrix& m) {
	fill_i(m);
}

void fill_j(int i, Matrix& m) {
	for (int j = m.vars_getter(); j < m.cols_getter() - 1; j++) {
		if (j - m.vars_getter() == i - 1) m.values_setter(i, j, 1);
		else m.values_setter(i, j, 0);
	}
}

void fill_i(Matrix& m) {
	for (int i = 1; i < m.rows_getter(); i++) {
		fill_j(i, m);
	}
}

int det_piv_column(Matrix& m) {
	const int cols = m.cols_getter() - 1;
	int best_col = -1;
	double most_neg = 0; // Inicializa en 0

	for (int j = 0; j < cols; ++j) {
		double coef = m.get_value(0, j);
		if (coef < most_neg) {
			most_neg = coef;
			best_col = j;
		}
	}
	return best_col; // Retorna -1 si no hay negativos (óptimo)
}

int det_piv_row(Matrix& m, int piv_col) {
	const int rows = m.rows_getter();
	const int rhs_col = m.cols_getter() - 1;

	if (piv_col < 0) return -1;

	int first_valid_row = -1;
	for (int i = 1; i < rows; ++i) {
		double coeff = m.get_value(i, piv_col);
		if (coeff > 0) {
			first_valid_row = i;
			break;
		}
	}

	if (first_valid_row == -1) return -1; // No acotado

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
			tied_rows.push_back(i); // Empate detectado
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

void row_pivot_iterate(Matrix& m, int piv_row, int piv_col) {
	double piv_value = m.get_value(piv_row, piv_col);
	for (int j = 0; j < m.cols_getter(); j++) {
		m.values_setter(piv_row, j, m.get_value(piv_row, j) / piv_value);
	}
}

void col_iterate(Matrix& m, int piv_row, int piv_col) {
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

bool optimal_solution(Matrix& m) {
	for (int j = 0; j < m.cols_getter() - 1; j++) {
		if (m.get_value(0, j) < 0) {
			return false;
		}
	}
	return true;
}