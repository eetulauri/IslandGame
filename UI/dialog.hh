#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    int getSpinBoxValue();

signals:
    void sendValue();

private slots:

    void on_readyButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_HH
