#include "Simplex_Method_GUI.h"
#include "Objetive.h"
#include "Setter.h"
#include "Matrix.h"

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
	connect(objetiveWindow, &Objetive::signal_destroy_matrix, this, &Simplex_Method_GUI::call_destuctor );

	connect(setterWindow, &Setter::signal_set_boxes, this, &Simplex_Method_GUI::set_boxes);

	connect(objetiveWindow, &Objetive::signal_solve_matrix, this, &Simplex_Method_GUI::solve_matrix);

	ui.stackedWidget->setCurrentIndex(0);
}

Simplex_Method_GUI::~Simplex_Method_GUI(){
}

void Simplex_Method_GUI::call_destuctor() {
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

void Simplex_Method_GUI::solve_matrix() {
	objetiveWindow->get_values_z();
}
