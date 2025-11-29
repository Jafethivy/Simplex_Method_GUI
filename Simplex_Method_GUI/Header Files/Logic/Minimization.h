#pragma once
#include "Matrix.h"

void start_minimization(Matrix& m);

void pivoting_min(Matrix& m);

void fill_slack_min(Matrix& m);
void fill_i_min(Matrix& m);
void fill_j_min(int i, Matrix& m);

int det_piv_column_min(Matrix& m);
int det_piv_row_min(Matrix& m, int piv_col);

void row_pivot_iterate_min(Matrix& m, int piv_row, int piv_col);
void col_iterate_min(Matrix& m, int piv_row, int piv_col);

bool optimal_solution_min(Matrix& m);


