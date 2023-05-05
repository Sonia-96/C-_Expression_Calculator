#include <QApplication>
#include "msdwidget.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MSDWidget window;
    window.setWindowTitle("Calculator");
    window.show();

    return app.exec();
}
