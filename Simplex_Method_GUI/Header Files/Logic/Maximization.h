#pragma once
#include "Iteration.h"
class Matrix;

bool start_maximization(Matrix& m, callback_itr callback = nullptr);

void pivoting(Matrix& m, Iteration& itr, bool& unbounded);

void define_z(Matrix& m);
void fill_slack(Matrix& m);
void fill_i(Matrix& m);
void fill_j(int i, Matrix& m);

int det_piv_column(Matrix& m);
int det_piv_row(Matrix& m, int piv_col);

void row_pivot_iterate(Matrix& m, int piv_row, int piv_col);
void col_iterate(Matrix& m, int piv_row, int piv_col);

bool optimal_solution(Matrix& m);