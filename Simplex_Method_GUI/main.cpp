#include "Simplex_Method_GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Simplex_Method_GUI window;
    window.show();
    return app.exec();
}
