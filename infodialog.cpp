#include "infodialog.h"
#include "ui_infodialog.h"
#include "repairticket.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

QPlainTextEdit* InfoDialog::infoDialog_Job()
{
    return ui->tktPrevLoc;
}

QLineEdit* InfoDialog::infoDialog_Tech()
{
    return ui->tktPrevTech;
}

void InfoDialog::disableTextBox()
{
    ui->tkt_Group_prevLoc->setDisabled(true);
}
