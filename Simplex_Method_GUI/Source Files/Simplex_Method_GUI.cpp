#include "Simplex_Method_GUI.h"
#include "Objetive.h"
#include "Setter.h"
#include "Final_solution.h"
#include "Matrix.h"
#include "Maximization.h"
#include "Minimization.h"
#include "Iteration.h"
#include <QMessageBox>

Simplex_Method_GUI::Simplex_Method_GUI(QWidget *parent)
    : QMainWindow(parent){

    ui.setupUi(this);

	setterWindow = new Setter(this);
	objetiveWindow = new Objetive(this);
	solutionWindow = new Final_solution(this);
	m = nullptr;

	ui.stackedWidget->addWidget(setterWindow);
	ui.stackedWidget->addWidget(objetiveWindow);
	ui.stackedWidget->addWidget(solutionWindow);

	connect(setterWindow, &Setter::signal_next_window, ui.stackedWidget, &QStackedWidget::setCurrentIndex);// cambia a objetive.ui
	connect(objetiveWindow, &Objetive::signal_previous_window, ui.stackedWidget, &QStackedWidget::setCurrentIndex);
	connect(objetiveWindow, &Objetive::signal_next_window, ui.stackedWidget, &QStackedWidget::setCurrentIndex);
	connect(solutionWindow, &Final_solution::signal_previous_window, ui.stackedWidget, &QStackedWidget::setCurrentIndex);

	connect(setterWindow, &Setter::signal_init_matrix, this, &Simplex_Method_GUI::init_matrix);// signal de setter.cpp a init_matrix
	connect(objetiveWindow, &Objetive::signal_destroy_matrix, this, &Simplex_Method_GUI::call_destructor );// signal de objetive.cpp para eliminar la matriz completa

	connect(objetiveWindow, &Objetive::signal_set_values_matrix, this, &Simplex_Method_GUI::set_values_matrix);
	connect(objetiveWindow, &Objetive::signal_set_objetive, this, &Simplex_Method_GUI::set_objetive);
	
	connect(objetiveWindow, &Objetive::signal_solution, this, &Simplex_Method_GUI::debug);//CHECAR LA FUNCION DEBUG DE ESTE ARCHIVO

	connect(solutionWindow, &Final_solution::signal_new_problem, this, &Simplex_Method_GUI::new_problem);

	ui.stackedWidget->setCurrentIndex(0);//Esto te manda a setter.cpp / setter.ui
}

Simplex_Method_GUI::~Simplex_Method_GUI(){
}
void Simplex_Method_GUI::call_destructor() { // utilidad
	if (m != nullptr) {
		delete m;
		m = nullptr;
	}
}

void Simplex_Method_GUI::init_matrix(int& vars, int& rest) { // esto recibe las variables del signal en setter.cpp
	m = new Matrix(vars, rest);
	set_boxes();//define las cantidades de cajas
}

void Simplex_Method_GUI::set_boxes() { // lo de arriba
	int amount_boxes = m->vars_getter(); // define la cantidad de cajas para la func z
	int amount_rest = m->rest_getter(); // define la cantidad de cajas para restricciones
	objetiveWindow->create_boxes_z(amount_boxes); // lo manda a objetiveWindow que es Objetive.cpp
	objetiveWindow->create_boxes_rest(amount_boxes, amount_rest); // lo de arriba
}

void Simplex_Method_GUI::set_values_matrix(QVector<double>& z_values, QQueue<double>& r_values, QQueue<double>& results_values) const{
	m->set_objetive_function(z_values);
	m->set_restrictions(r_values, results_values);
	
}

void Simplex_Method_GUI::set_objetive(bool objetive) {
	Matrix& m2 = *m;
	int index = 2;
	if (!objetive) {
		bool unbounded = start_maximization(m2, [this](const Iteration& itr) {iterations.append(itr); });
		if (unbounded) {
			showError("Solucion no acotada", "El problema tiene solucion ilimitada (no acotada)");
			exceptions();
			index = 1;
		}
		ui.stackedWidget->setCurrentIndex(index);
	}
	else {
		bool unbounded = start_maximization(m2, [this](const Iteration& itr) {iterations.append(itr); });
		if (unbounded) {
			showError("Solucion no acotada", "El problema tiene solucion ilimitada (no acotada)");
			exceptions();
			index = 1;
		}
		ui.stackedWidget->setCurrentIndex(index);
	}
}

void Simplex_Method_GUI::debug() { // esta funcion tiene nombre raro pq la otra no compilaba jijijijiji
	//Define las cosas que usara la ventana solutionWindow
    solutionWindow->set_dimensions(m->rows_getter(), m->cols_getter());
	
	QVector<Iteration> itrs = itr_getter(); //Cosas para iterar

    solutionWindow->set_itr_values(itrs); // Define las cosas para iterar

	iterations.clear(); //limpia el vector inicial (para evitar errores)
	itrs.clear(); // cosas de c++ y garbage
	itrs.squeeze(); // lo de arriba

	solutionWindow->display_table(); // inicializa la siguiente ventana (Final_solution.cpp)
}

//Un getter
QVector<Iteration> Simplex_Method_GUI::itr_getter() {
	return iterations;
}

//TODO LO DE ACA ES MANEJO DE ERRORES Y LIMPIEZA
void Simplex_Method_GUI::new_problem() {
	solutionWindow->clear();
	objetiveWindow->clear();
	iterations.clear();
	call_destructor();
}

void Simplex_Method_GUI::edit_problem() {
	solutionWindow->clear();
	objetiveWindow->clear_alt();
	iterations.clear();
	call_destructor();
}

void Simplex_Method_GUI::exceptions() {
	solutionWindow->clear();
	objetiveWindow->clear_alt();
	iterations.clear();
	m->clear_matrix();
}

void Simplex_Method_GUI::showError(const QString& title, const QString& message){
	QMessageBox::critical(
		qApp->activeWindow(),
		title,
		message,
		QMessageBox::Ok
	);
}