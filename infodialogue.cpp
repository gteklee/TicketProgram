#include "infodialogue.h"
#include "ui_infodialogue.h"

Infodialogue::Infodialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Infodialogue)
{
    ui->setupUi(this);
}

Infodialogue::~Infodialogue()
{
    delete ui;
}
