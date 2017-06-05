#include "mainwindow.h"
#include <QApplication>
#include "./viewparam.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    window->installEventFilter(new keyPressCatcher());

    w.show();

    return a.exec();
}
