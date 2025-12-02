#include "Objetive.h"
#include "Boxes.h"
#include "Rest_boxes.h"

Objetive::Objetive(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	z_layout = new QHBoxLayout(ui.Func_z_container); //genera el container para cajas en func z
	z_layout->setSpacing(0);
	z_layout->setContentsMargins(0, 0, 0, 0);

	r2_layout = new QVBoxLayout(ui.Restrictions_container); //genera el container para cajas en restricciones
	r2_layout->setSpacing(0);
	r2_layout->setContentsMargins(0, 0, 0, 0);
}

Objetive::~Objetive(){
}

void Objetive::on_Editar_button_clicked() {//Esto te manda a la pantalla anterior
	emit signal_destroy_matrix(); // signal a SMG.cpp
	emit signal_previous_window(0); // cambia a la .ui de inicio
}
void Objetive::on_Solve_button_clicked() {
	solve_matrix(); // resuelve la matriz

	emit signal_solution(); //Te manda a SMG.cpp en la funcion Debug
}

void Objetive::solve_matrix() {
	get_values_z();
	get_values_r();
	emit signal_set_values_matrix(z_values, r_values, results_values);
	emit signal_set_objetive(get_objetive());//Aqui se detiene cuando es no acotada
}

void Objetive::set_amount_boxes(int boxes) {
	amount_boxes = boxes;
}
void Objetive::set_amount_rest(int rest) {
	amount_rest = rest;
}

//Objetive zone
bool Objetive::get_objetive() {
	return ui.Objetive_box->currentIndex();
}

//Function Z zone
void Objetive::create_boxes_z(int amount_boxes) { // esto crea las cajas en Func Z
	clear_boxes_z(); // Limpia cajas anteriores
	set_amount_boxes(amount_boxes); //Define la cantidad de cajas

	for (int i = 0; i < amount_boxes; i++) { // todo esto crea caja por caja
		Boxes* box = new Boxes(QString("x_%1").arg(i+1), this);
		if (i == amount_boxes - 1) {
			box->plus_visible();
		}
		z_layout->insertWidget(z_layout->count(), box);
		z_list.append(box);
	}
	ui.Func_z_container->adjustSize();
}

void Objetive::clear_boxes_z() {
	for (Boxes* box : z_list) {
		z_layout->removeWidget(box);
		delete box;
	}
	z_list.clear();
}

//Restrictions zone

void Objetive::create_boxes_rest(int amount_boxes, int amount_rest) { // esto crea las cajas para restricciones y el valor
	clear_boxes_r1(); //ambas limpian
	clear_boxes_r2();
	set_amount_rest(amount_rest); // define cantidad de resticciones

	for (int j = 0; j < amount_rest; j++) { //crea la fila de restricciones y resultado
		r_layout = new QHBoxLayout();
		r_layout->setSpacing(0);
		r_layout->setContentsMargins(0, 0, 0, 0);

		
		for (int i = 0; i < amount_boxes; i++) {
			Boxes* box = new Boxes(QString("x_%1").arg(i + 1), this);
			if (i == amount_boxes - 1) {
				box->plus_visible();
			}
			r_layout->insertWidget(r_layout->count(), box);
			r_list.append(box);
		}
		
		Rest_boxes* rest_box = new Rest_boxes(this);
		r_layout->insertWidget(r_layout->count(), rest_box);
		rest_list.append(rest_box);
		r2_layout->addLayout(r_layout);
	}
	ui.Restrictions_container->adjustSize();
}

void Objetive::clear_boxes_r1() {
	for (Boxes* box : r_list) {
		r_layout->removeWidget(box);
		delete box;
	}
	r_list.clear();
}
void Objetive::clear_boxes_r2() {
	for (Rest_boxes* box : rest_list) {
		r_layout->removeWidget(box);
		delete box;
	}
	rest_list.clear();
}

void Objetive::get_values_z() { // Obtiene valores de las cajas
	for (int i = 0; i < amount_boxes; i++) {
		double value = z_list[i]->box_value();
		z_values.append(value);
	}
}

void Objetive::get_values_r() { //Obtiene valores de las cajas
	for (int j = 0; j < amount_rest; j++) {
		for (int i = 0; i < amount_boxes; i++) {
			double value = r_list[j * amount_boxes + i]->box_value();
			r_values.enqueue(value);
		}
		double rest_value = rest_list[j]->box_rest_value();
		results_values.enqueue(rest_value);
	}
}

void Objetive::clear() { // limpieza
	int amount_boxes = 0;
	int amout_rest = 0;

	qDeleteAll(z_list);
	z_list.clear();
	qDeleteAll(r_list);
	r_list.clear();
	qDeleteAll(rest_list);
	rest_list.clear();

	z_values.clear();
	r_values.clear();
	results_values.clear();

	if (z_layout) {
		qDeleteAll(z_layout->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
	}
	if (r2_layout) {
		qDeleteAll(r2_layout->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));
	}
}

void Objetive::clear_alt() {// limpieza
	z_values.clear();
	r_values.clear();
	results_values.clear();
}