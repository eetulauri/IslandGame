#ifndef MAINUI_HH
#define MAINUI_HH

#include "graphichex.hh"
#include "gameboard.hh"
#include "gamestate.hh"
#include "gameengine.hh"
#include "igamerunner.hh"

#include <QMainWindow>

namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(QWidget *parent = 0);
    ~MainUI();

private:
    Ui::MainUI *ui;
    QGraphicsScene *scene_;

};

#endif // MAINUI_HH
