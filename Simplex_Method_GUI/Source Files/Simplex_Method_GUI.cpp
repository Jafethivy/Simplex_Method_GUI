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
	connect(objetiveWindow, &Objetive::signal_destroy_matrix, this, &Simplex_Method_GUI::destroy_matrix);

	connect(setterWindow, &Setter::signal_vars_rests, this, &Simplex_Method_GUI::send_package);

	ui.stackedWidget->setCurrentIndex(0);
}

Simplex_Method_GUI::~Simplex_Method_GUI()
{}

void Simplex_Method_GUI::init_matrix(int& vars, int& rest) {
	m = new Matrix(vars, rest);
	m->print_matrix();
}

void Simplex_Method_GUI::send_package(int& vars, int& rest) {
	objetiveWindow -> set_vars_rests(vars, rest);
}

void Simplex_Method_GUI::destroy_matrix() {
	if (m != nullptr) {
		delete m;
		m = nullptr;
	}
}