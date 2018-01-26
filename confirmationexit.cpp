#include "confirmationexit.h"
#include "ui_confirmationexit.h"
#include "mainwindow.h"
#include <QPixmap>

ConfirmationExit::ConfirmationExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationExit)
{
    ui->setupUi(this);

    // Disables window resizeability.
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}

ConfirmationExit::~ConfirmationExit()
{
    delete ui;
}

void ConfirmationExit::on_exitButton_clicked()
{
    QApplication::quit();
}

