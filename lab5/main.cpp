#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow window;
    window.setWindowTitle("Fourier Transformation");
    window.resize(500, 450);
    
    window.show();
    return a.exec();
}
