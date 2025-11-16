#pragma once
#include <vector>
#include <string>

class Matrix {
private:
    std::vector<double> tabla;
    std::vector<double> funcZ;
    int rows, cols, variables, restrictions;
    std::string objetive;

    // Acceso interno inline
    inline double& at_a(int i, int j);
    inline const double& at_b(int i, int j) const;

public:
    //Constructor
    explicit Matrix(int n_vars, int n_rest, const std::string& obj);

    //Getters
    [[nodiscard]] int cols_getter() const noexcept;
    [[nodiscard]] int rows_getter() const noexcept;
    [[nodiscard]] int vars_getter() const noexcept;
    [[nodiscard]] int rest_getter() const noexcept;
    [[nodiscard]] double Z_getter(int j) const;
    [[nodiscard]] double get_value(int i, int j) const;

    // Setters
    void Z_setter(int j, double value);
    void values_setter(int i, int j, double value);

    // Carga de datos (separada de constructor)
    void set_objetive_function(const std::vector<double>& coefs);
    void set_restrictions(int idx, const std::vector<double>& coefs, double result);

    // Utilidades
    void print_matrix() const;
};