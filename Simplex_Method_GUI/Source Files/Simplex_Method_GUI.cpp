#include "Simplex_Method_GUI.h"
#include "Objetive.h"
#include "Setter.h"
#include "Matrix.h"
#include "Maximization.h"
#include "Minimization.h"

Simplex_Method_GUI::Simplex_Method_GUI(QWidget *parent)
    : QMainWindow(parent){

    ui.setupUi(this);

	setterWindow = new Setter(this);
	objetiveWindow = new Objetive(this);
	m = nullptr;
	
	ui.stackedWidget->addWidget(setterWindow);
	ui.stackedWidget->addWidget(objetiveWindow);

	connect(setterWindow, &Setter::signal_next_window, ui.stackedWidget, &QStackedWidget::setCurrentIndex);

	connect(objetiveWindow, &Objetive::signal_previous_window, ui.stackedWidget, &QStackedWidget::setCurrentIndex);

	connect(setterWindow, &Setter::signal_init_matrix, this, &Simplex_Method_GUI::init_matrix);
	connect(objetiveWindow, &Objetive::signal_destroy_matrix, this, &Simplex_Method_GUI::call_destructor );

	connect(setterWindow, &Setter::signal_set_boxes, this, &Simplex_Method_GUI::set_boxes);

	connect(objetiveWindow, &Objetive::signal_set_values_matrix, this, &Simplex_Method_GUI::set_values_matrix);
	connect(objetiveWindow, &Objetive::signal_set_objetive, this, &Simplex_Method_GUI::set_objetive);
	connect(objetiveWindow, &Objetive::signal_test, this, &Simplex_Method_GUI::test);

	ui.stackedWidget->setCurrentIndex(0);
}

Simplex_Method_GUI::~Simplex_Method_GUI(){
}
Matrix Simplex_Method_GUI::m2() {
	return *m;
}

void Simplex_Method_GUI::call_destructor() {
	if (m != nullptr) {
		delete m;
		m = nullptr;
	}
}

void Simplex_Method_GUI::init_matrix(int& vars, int& rest) {
	m = new Matrix(vars, rest);
	m->print_matrix();
}

void Simplex_Method_GUI::set_boxes() {
	int amount_boxes = m->vars_getter();
	int amount_rest = m->rest_getter();
	objetiveWindow->create_boxes_z(amount_boxes);
	objetiveWindow->create_boxes_rest(amount_boxes, amount_rest);
}

void Simplex_Method_GUI::set_values_matrix(QVector<double>& z_values, QQueue<double>& r_values, QQueue<double>& results_values) const{
	m->set_objetive_function(z_values);
	m->set_restrictions(r_values, results_values);
	
}

void Simplex_Method_GUI::set_objetive(bool objetive) {
	Matrix& m2 = *m;
	if (objetive) {
		start_maximization(m2);
	}
	else {
		start_minimization(m2);
	}
}

void Simplex_Method_GUI::test() {
	m->print_matrix();
}