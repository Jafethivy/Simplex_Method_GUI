#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simplex_Method_GUI.h"

class Simplex_Method_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Simplex_Method_GUI(QWidget *parent = nullptr);
    ~Simplex_Method_GUI();

private:
    Ui::Simplex_Method_GUIClass ui;
};

