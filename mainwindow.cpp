#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmationexit.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Disables window resizeability.
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    // Automatically selects Repair Tickets.
    ui->radioSonar->setChecked(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_3_triggered()
{
    ConfirmationExit ce;
    ce.setModal(true);
    ce.exec();
}

void MainWindow::on_ticketButton_clicked()
{
    if(ui->radioRepair->isChecked())
    {
        repairTicket = new RepairTicket(this);
        repairTicket->show();
    }
    else if(ui->radioSonar->isChecked())
    {
        repairTicketSonar = new RepairTicketSonar(this);
        repairTicketSonar->show();
    }
    /*else if(ui->radioDisconnect->isChecked())
    {
        disconnectTicket = new DisconnectTicket(this);
        disconnectTicket->show();
    }*/
    else if(ui->install->isChecked())
    {
        install = new Install(this);
        install->show();
    }
    else if(ui->onsite->isChecked())
    {
        onsite = new Onsite(this);
        onsite->show();
    }
    else if(ui->radioRelo->isChecked())
    {
        relo = new Relo(this);
        relo->show();
    }
    else if(ui->radioNetwork->isChecked() && ui->ticketType->currentText() == "Static IP")
    {
        network_Static = new Network_Static(this);
        network_Static->show();
    }
    else if(ui->radioNetwork->isChecked() && ui->ticketType->currentText() == "Key Upgrade")
    {
        network_Key = new Network_Key(this);
        network_Key->show();
    }
    else if(ui->radioNetwork->isChecked() && ui->ticketType->currentText() == "Voip / Nextiva")
    {
        network_Voip = new Network_Voip(this);
        network_Voip->show();
    }
    else if(ui->radioNetwork->isChecked() && ui->ticketType->currentText() == "MTL / MDU")
    {
        network_MTL = new Network_MTL(this);
        network_MTL->show();
    }
    else if(ui->radioNetwork->isChecked() && ui->ticketType->currentText() == "Other")
    {
        network_Other = new Network_Other(this);
        network_Other->show();
    }
}

void MainWindow::on_radioNetwork_clicked()
{
    ui->ticketType->setEnabled(true);
}

/*void MainWindow::on_radioDisconnect_clicked()
{
    ui->ticketType->setDisabled(true);
}*/

void MainWindow::on_radioSonar_clicked()
{
    ui->ticketType->setDisabled(true);
}

void MainWindow::on_radioRepair_clicked()
{
    ui->ticketType->setDisabled(true);
}

void MainWindow::on_onsite_clicked()
{
    ui->ticketType->setDisabled(true);
}

void MainWindow::on_commandLinkButton_clicked()
{
    changelog = new Changelog(this);
    changelog->show();
}
