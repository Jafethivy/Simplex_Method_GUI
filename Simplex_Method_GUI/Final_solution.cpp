#include "Final_solution.h"
#include <Vector>
#include <QHeaderView>

Final_solution::Final_solution(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);

    display_layout = new QVBoxLayout(ui.Solution_container);
    display_layout->setSpacing(0);
    display_layout->setContentsMargins(0, 0, 0, 0);

    // LA FUNCION INICIAL ES DISPLAY TABLE
}

Final_solution::~Final_solution() {}
void Final_solution::set_dimensions(int r, int c) {
    rows = r;
    cols = c;
    rest = rows - 1;
	vars = cols - rows;

}
void Final_solution::set_itr_values(QVector<Iteration> itr) {
    iterations = itr;
}

QTableWidget* Final_solution::create_table(int n, QWidget* parent) { // CREA LA TABLA (IMPORTANTE)
    QTableWidget* table = new QTableWidget(parent);

    //Columns
    table->setRowCount(rows);
    table->setColumnCount(cols);

	QStringList cols_str;
    QStringList rows_str;

    for (int i = 0; i < vars; i++) {
        QString name_a = QString("x_%1").arg(i + 1);
		cols_str.append(name_a);
        if(n==0){ vars_in.append(name_a); }
    }
    for (int i = vars; i < cols - 1; i++) {
        QString name_b = QString("s_%1").arg(i - vars + 1);
		cols_str.append(name_b);
        if (n == 0) { vars_in.append(name_b); }
    }
    QString name_c = QString("Resultado");
    cols_str.append(name_c);
    if (n == 0) { vars_in.append(name_c); }

    //Rows
    QString name_d = "Z";
    rows_str.append(name_d);
    if (n == 0) { rest_in.append(name_d); }

    for (int i = 1; i < rows; i++) {
        QString name_e = QString("s_%1").arg(i);

        if (n != 0 && !outputs.isEmpty()) {
            int found_index = -1;
            for (int k = 0; k < outputs.size(); k++) {
                if (outputs[k] == i) {
                    found_index = k;
                    break;
                }
            }

            if (found_index != -1 && found_index < inputs.size()) {
                name_e = inputs[found_index];
            }
        }

        if (n != 0) {
            Iteration& itr = iterations[n];
            int input_col = itr.piv_col;
            int piv_row_index = itr.piv_row;

            if (piv_row_index == i) {
                QString input_str = vars_in[input_col];
                name_e = input_str;
                inputs.append(name_e);
                outputs.append(i);
            }
        }

        rows_str.append(name_e);
        if (n == 0) {
            rest_in.append(name_e);
        }
    }

    style_table(table, cols_str, rows_str);

	return table;
}

QLabel* Final_solution::create_label(int i, QWidget* parent) { // LO DE ARRIBA DE LA TABLA
    QString name = QString("Iteración n.%1").arg(i);
    if (i == 0) {
        name = QString("Matriz Inicial");
    }
    QLabel* tituloLabel = new QLabel(name, parent);
    QFont font("Candara", 16); // AQUI EL TIPO DE LETRA Y SIZE
    font.setStyleStrategy(QFont::PreferAntialias);
    tituloLabel->setFont(font);
    tituloLabel->setStyleSheet( // AQUI EL STYLESHEET
        "QLabel {"
        "   background-color: #FFFFFF;" 
        "   color: #000000;"              
        "   padding: 10px;"               
        "}"
    );
    return tituloLabel;
}

QLabel* Final_solution::create_info(int i, QWidget* parent) { // LA INFO DE ABAJO
    QString text = "";
    if (i + 1 < static_cast<int>(iterations.size())) {
        text += QString("Ingresa la variable ");
        Iteration& next_itr = iterations[i + 1];
        text += QString(vars_in[next_itr.piv_col]);
        text += QString(" y sale la variable %1. ").arg(rest_in[next_itr.piv_row]);
        text += QString("El elemento pivote es %1.").arg(next_itr.iterated);
    }

    QLabel* label = new QLabel(text, parent);
    QFont font("Candara", 14);
    font.setStyleStrategy(QFont::PreferAntialias);
    label->setFont(font);
    label->setStyleSheet(
        "QLabel {"
        "   background-color: #FFFFFF;"
        "   color: #000000;"
        "   padding: 10px;"
        "}"
    );
    return label;
}

QTableWidget* Final_solution::init_table(int i, QWidget* parent) { // INICIALIZA DATOS DE LA TABLA
    QTableWidget* table = create_table(i, parent); // CREA LA TABLA SIN DATOS, CHECAR LA FUNCION ARRIBA

    Iteration& itr = iterations[i]; // COSAS IMPORTANTES
    std::vector<double> data = itr.table;
    QVector<double> qdata(data.begin(), data.end());
   

    table->setUpdatesEnabled(false); // DESACTIVA LA TABLA PARA EFICIENCIA DE INTRODUCCION DE DATOS

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int indx = row * cols + col;

            if (indx < qdata.size()) {
                double value = qdata[indx];
                QString text = QString::number(value, 'f', 2);
                QTableWidgetItem* item = new QTableWidgetItem(text);

                //TODO ESTO SOLO METE DATOS

                if (i + 1 < static_cast<int>(iterations.size())) {
                    Iteration& itr_next = iterations[i + 1];
                    int piv_row = itr_next.piv_row;
                    int piv_col = itr_next.piv_col;
                    int piv = piv_row * cols + piv_col;
                    if (piv == indx) {
                        item->setForeground(QBrush(QColor("#000000")));
                        item->setBackground(QBrush(QColor("#00A8E0")));
                    }
                }

                item->setTextAlignment(Qt::AlignCenter);

                table->setItem(row, col, item);
            }
        }
    }

    table_size(table);

    table->setUpdatesEnabled(true); // ACTIVA LA TABLA

    return table;
}

void Final_solution::table_size(QTableWidget* table) {
    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    QFontMetrics fm(table->font());
    int minWidth = fm.horizontalAdvance("000000000");

    for (int col = 0; col < table->columnCount(); ++col) {
        if (table->columnWidth(col) < minWidth) {
            table->setColumnWidth(col, minWidth);
        }
    }

    int width = table->verticalHeader()->width();
    for (int col = 0; col < table->columnCount(); ++col) {
        width += table->columnWidth(col);
    }
    width += table->frameWidth() * 2;

    int height = table->horizontalHeader()->height();
    for (int row = 0; row < table->rowCount(); ++row) {
        height += table->rowHeight(row);
    }
    height += table->frameWidth() * 2;

    table->setFixedSize(width, height);
}

void Final_solution::style_table(QTableWidget* table, QStringList cols_str, QStringList rows_str) {
    QFont font = table->font();
    font.setPointSize(12);
    table->setFont(font);

    table->horizontalHeader()->setObjectName("hHeader");
    table->verticalHeader()->setObjectName("vHeader");

    table->horizontalHeader()->setFont(font);
    table->verticalHeader()->setFont(font);

    table->setHorizontalHeaderLabels(cols_str);
    table->setVerticalHeaderLabels(rows_str);

    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

    QString styleSheet = R"(
        QTableWidget {
            color: #000000;
            gridline-color: #000000;
	        border: 2px solid #000000;
            border-radius: 8px; 
            background-color: white;
        }

        QHeaderView#hHeader::section {
            background-color: white;
            color: #000000;
	        border: 1px solid #000000;
            border-left:none;
        }
        
        QHeaderView#hHeader::section:first {
            background-color: white;
            color: #000000;
            border: 1px solid #000000;
        }

        QHeaderView#hHeader::section:last {
            background-color: white;
            color: #000000;
            border: 1px solid #000000;
            border-left:none;
            border-top-right-radius: 7px;
        }


        QHeaderView#vHeader::section {
            background-color: white;
            color: #000000;
            border: 1px solid #000000;
        }

        QHeaderView#vHeader::section {
            background-color: white;
            color: #000000;
	        border: 1px solid #000000;
            border-bottom:none;
        }

        QHeaderView#vHeader::section:last{
            background-color: white;
            color: #000000;
            border: 1px solid #000000;
            border-bottom:1px solid #000000;
            border-bottom-left-radius: 7px;
        }
    
        QTableWidget::item {
            color: #000000;
        }
    )";

    table->setStyleSheet(styleSheet);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

QVBoxLayout* Final_solution::create_base(int i, QWidget* parent){ // ESTA FUNCION CREA TODO
    QVBoxLayout* base = new QVBoxLayout;
    base->setSpacing(0);
    base->setContentsMargins(0, 0, 0, 0);
    base->addWidget(create_label(i, parent)); // ESTO ES EL LABEL DE ARRIBA QUE DICE QUE TABLA ES
    base->addWidget(init_table(i, parent)); // ESTO ES LA TABLA
    base->addWidget(create_info(i, parent)); // ESTO CREA LA INFO DE ABAJO DE LA TABLA
    return base;
}

void Final_solution::display_table() { // inicia todos los datos a mostrar

    //Manejo de errores no voy a explicar pq es mucho
    qDeleteAll(ui.Solution_container->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));

    while (QLayoutItem* item = display_layout->takeAt(0)) {
        if (item->spacerItem()) {
            delete item->spacerItem();
        }
        delete item;
    }

    //Crea la cantidad de tablas que se mostraran
    for (int i = 0; i < iterations.size(); i++) {
        QHBoxLayout* spacers = new QHBoxLayout;
        spacers->setSpacing(0);
        spacers->setContentsMargins(0, 0, 0, 0);

        QSpacerItem* leftSpacer = new QSpacerItem(50, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);
        QSpacerItem* rightSpacer = new QSpacerItem(50, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);

        spacers->addSpacerItem(leftSpacer);
        spacers->addLayout(create_base(i, ui.Solution_container));//CREATE_BASE ES UNA FUNCION QUE GENERA TODO LO NECESARIO (CHECAR LA FUNCION)
        spacers->addSpacerItem(rightSpacer);

        display_layout->addLayout(spacers);
    }
}

void Final_solution::on_Editar_button_clicked() { // QUE HACE EL BOTON DE EDITAR
    emit signal_previous_window(1); 
    emit signal_edit_problem(); // SU SIGNAL CORRESPONDIENTE EN SMG.cpp
}

void Final_solution::on_New_button_clicked() { // QUE HACE EL BOTON DE NUEVO PROBLEMA
    emit signal_previous_window(0);
    emit signal_new_problem(); // SU SIGNAL CORRESPONDIENTE EN SMG.cpp
}

//LIMPIEZA
void Final_solution::clear() {
    vars_in.clear();
    rest_in.clear();
    iterations.clear();
    inputs.clear();
    outputs.clear();
}
