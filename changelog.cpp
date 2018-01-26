#include "changelog.h"
#include "ui_changelog.h"

Changelog::Changelog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Changelog)
{
    ui->setupUi(this);

}

Changelog::~Changelog()
{
    delete ui;
}

void Changelog::on_Close_clicked()
{
    this->close();
}
