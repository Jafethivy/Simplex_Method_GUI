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
    funcZ.resize(variables);    
    objetive = "";
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
double Matrix::Z_getter(int j) const { return funcZ[j]; }
double Matrix::get_value(int i, int j) const { return at_b(i, j); }

// Setters
void Matrix::Z_setter(int j, double value) {
    assert(j >= 0 && j < cols);
    at_a(0, j) = value;
}
void Matrix::values_setter(int i, int j, double value) {
    at_a(i, j) = value;
}

// Cargar función objetivo
void Matrix::set_objetive_function(const std::vector<double>& coefs) { // coefs : valores
	assert(static_cast<int>(coefs.size()) == variables); // debug : la cantidad de coeficientes debe coincidir
    funcZ = coefs;
    for (int j = 0; j < variables; ++j) {
        at_a(0, j) = coefs[j];
    }
}

// Cargar restricción
void Matrix::set_restrictions(int idx, const std::vector<double>& coefs, double result) { // idx es el indice; coefs : valores ; result: valor de la restriccion
	assert(idx < restrictions && static_cast<int>(coefs.size()) == variables); // debug : la cantidad de coeficientes debe coincidir
    for (int j = 0; j < variables; ++j) {
        at_a(idx + 1, j) = coefs[j];
    }
    at_a(idx + 1, cols - 1) = result;
}

// Imprimir matriz
void Matrix::print_matrix() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            qDebug()<< "[" << at_b(i, j) << "]";
        }
        qDebug()<<"";
    }
}
