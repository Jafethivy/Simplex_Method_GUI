#include "Final_solution.h"
#include <Vector>
#include <QHeaderView>

Final_solution::Final_solution(QWidget* parent)
	: QWidget(parent) {
	ui.setupUi(this);

    display_layout = new QVBoxLayout(ui.Solution_container);
    display_layout->setSpacing(0);
    display_layout->setContentsMargins(0, 0, 0, 0);

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

QTableWidget* Final_solution::create_table() {
    QTableWidget* table = new QTableWidget();

    table->setRowCount(rows);
    table->setColumnCount(cols);
	QStringList cols_str;
    QStringList rows_str;
    for (int i = 0; i < vars; i++) {
		cols_str.append(QString("x_%1").arg(i+1));
    }
    for (int i = vars; i < cols - 1; i++) {
		cols_str.append(QString("s_%1").arg(i - vars + 1));
    }
    cols_str.append(QString("Resultado"));
    rows_str.append("Z");
    for (int i = 1; i < rows; i++) {    
        rows_str.append(QString("x_%1").arg(i));
    }

    table->setHorizontalHeaderLabels(cols_str);
	table->setVerticalHeaderLabels(rows_str);

    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

    table->setStyleSheet(
        "QTableWidget{"
        "color: #000000;"
        "gridline - color: #FFFFFF;"
        "}"
        "QHeaderView::section{"
        "color: #000000;"
        "background - color: white;"
        "padding: 4px;"
        "border: 1px solid #c0c0c0;"
        "}"
    );
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	return table;
}

QLabel* Final_solution::create_label(int i) {
    QString name = QString("Iteracion n.%1").arg(i);
    if (i == 0) {
        name = QString("Matriz Inicial");
    }
    QLabel* tituloLabel = new QLabel(name,this);
    QFont font("Candara", 16);
    font.setStyleStrategy(QFont::PreferAntialias);
    tituloLabel->setFont(font);
    tituloLabel->setStyleSheet(
        "QLabel {"
        "   background-color: #FFFFFF;" 
        "   color: #000000;"              
        "   padding: 10px;"               
        "}"
    );
    return tituloLabel;
}

QTableWidget* Final_solution::init_table(int i) {
    QTableWidget* table = create_table();
    Iteration itr = iterations[i];
    std::vector<double> data = itr.table;
    QVector<double> qdata(data.begin(), data.end());

    table->setUpdatesEnabled(false);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int indx = row * cols + col;

            if (indx < qdata.size()) {
                double value = qdata[indx];
                QString text = QString::number(value, 'f', 2);
                QTableWidgetItem* item = new QTableWidgetItem(text);
                item->setTextAlignment(Qt::AlignCenter);

                table->setItem(row, col, item);
            }
        }
    }

    table_size(table);

    table->setUpdatesEnabled(true);

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

QVBoxLayout* Final_solution::create_base(int i){
    QVBoxLayout* base = new QVBoxLayout;
    base->setSpacing(0);
    base->setContentsMargins(0, 0, 0, 0);
    base->addWidget(create_label(i));
    base->addWidget(init_table(i));
    return base;
}

void Final_solution::display_table() {
    for (int i = 0; i < iterations.size(); i++) {
        QHBoxLayout* spacers = new QHBoxLayout;
        spacers->setSpacing(0);
        spacers->setContentsMargins(0, 0, 0, 0);

        QSpacerItem* leftSpacer = new QSpacerItem(50, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);
        QSpacerItem* rightSpacer = new QSpacerItem(50, 0, QSizePolicy::Preferred, QSizePolicy::Minimum);

        spacers->addSpacerItem(leftSpacer);
        spacers->addLayout(create_base(i));
        spacers->addSpacerItem(rightSpacer);

        display_layout->addLayout(spacers);
    }
}