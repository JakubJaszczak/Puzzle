#include "gamemenager.h"
#include "mainwindow.h"
#include "gamemenager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameMenager myGameMeanger;
    w.show();
    return a.exec();
}
