
#include "engine.h"
#include "mainwindow.h"
#include "player.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameManager manager;
    Player newPlayer;
    Engine gameEngine;
    w.setManager(manager);
    w.show();
    return a.exec();
}
