#include "dialog.hh"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::getSpinBoxValue()
{
    ui->spinBox->value();
}

void Dialog::on_readyButton_clicked()
{
    QDialog::accept();
    emit accepted();
}
