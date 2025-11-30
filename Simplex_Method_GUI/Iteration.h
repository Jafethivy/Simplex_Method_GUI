#pragma once
#include <vector>
#include <functional>

struct Iteration {
	std::vector<double> table;
	int piv_row, piv_col;
};

using callback_itr = std::function<void(const Iteration&)>;