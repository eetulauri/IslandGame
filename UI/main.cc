#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "mainwindow.hh"

#include <memory>
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;


    return a.exec();
}
