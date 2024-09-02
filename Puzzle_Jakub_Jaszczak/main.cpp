
#include "mainwindow.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameManager manager;
    w.setManager(manager);
    w.show();
    return a.exec();
}
