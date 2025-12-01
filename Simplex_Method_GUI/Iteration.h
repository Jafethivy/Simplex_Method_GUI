#pragma once
#include <vector>
#include <functional>

struct Iteration {
	std::vector<double> table;
	int piv_row = 0;
	int piv_col = 0;

	double iterated = 0;
};

using callback_itr = std::function<void(const Iteration&)>;