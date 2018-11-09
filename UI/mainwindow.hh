#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "graphichex.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "gameengine.hh"
#include "igamerunner.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeGameRunner(std::shared_ptr<Common::IGameRunner> gameRunner);

private:
    void setScene();

    std::shared_ptr<Common::IGameRunner> gameRunner_;
    std::shared_ptr<QGraphicsView> view_;
    std::shared_ptr<QGraphicsScene> scene_;


};

#endif // MAINWINDOW_HH
