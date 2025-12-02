#include "Matrix.h"
#include <cassert>
#include <qdebug.h>

// Constructor: inicializa todo a cero
Matrix::Matrix(int& n_vars, int& n_rest){
    variables = n_vars;
    restrictions = n_rest;
    rows = n_rest + 1;
    cols = n_vars + rows;
    size_t total_size = static_cast<size_t>(rows) * static_cast<size_t>(cols);
    tabla.resize(total_size, 0);
}

// Para setter
inline double& Matrix::at_a(int i, int j) {
    size_t index = static_cast<size_t>(i);
    return tabla[index * cols + j];
}
// Para getter
inline const double& Matrix::at_b(int i, int j) const {
    size_t index = static_cast<size_t>(i);
    return tabla[index * cols + j];
}

// Getters simples
int Matrix::cols_getter() const noexcept { return cols; }
int Matrix::rows_getter() const noexcept { return rows; }
int Matrix::vars_getter() const noexcept { return variables; }
int Matrix::rest_getter() const noexcept { return restrictions; }
double Matrix::get_value(int i, int j) const { return at_b(i, j); }
std::vector<double> Matrix::table_getter() const { return tabla; }

// Setters
void Matrix::Z_setter(int j, double value) {
    assert(j >= 0 && j < cols);
    at_a(0, j) = value;
}
void Matrix::values_setter(int i, int j, double value) {
    at_a(i, j) = value;
}

// Iteration getter and setter
int Matrix::iteration_getter() const noexcept {
    return iteration;
}
void Matrix::iteration_setter() noexcept {
    iteration += 1;
}

// Cargar función objetivo
void Matrix::set_objetive_function(QVector<double>& coefs) {
    for (int j = 0; j < variables; ++j) {
        at_a(0, j) = coefs[j];
    }
}

// Cargar restricción
void Matrix::set_restrictions(QQueue<double>& r_values, QQueue<double>& results_values) { 
    for (int idx = 0; idx < variables; idx++) {
        for (int j = 0; j < variables; ++j) {
            at_a(idx + 1, j) = r_values.head();
			r_values.dequeue();
        }
        at_a(idx + 1, cols - 1) = results_values.head();
		results_values.dequeue();
    }
}

// Imprimir matriz
void Matrix::print_matrix() const {
    for (int i = 0; i < vars_getter(); i++) {
		qDebug()<<at_b(0, i);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            qDebug()<< "[" << at_b(i, j) << "]";
        }
        qDebug()<<"";
    }
}

void Matrix::clear_matrix() {
    iteration = 0;
    tabla.clear();
}