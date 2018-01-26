#include "network_key.h"
#include "ui_network_key.h"
#include <QDate>

Network_Key::Network_Key(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Network_Key)
{
    ui->setupUi(this);
}

Network_Key::~Network_Key()
{
    delete ui;
}

void Network_Key::on_pushButton_clicked()
{
    ui->ticketTemplate->clear(); // Clear data already in ticket.

    QDate today = today.currentDate();

    // Data from user.
    QString cstInvoice,
            tktReason   =       "Key Upgrade",
            cstName     =       ui->cstName->text(),
            cstID       =       ui->cstID->text(),
            tktAggregate  =     ui->tktAggregate->text(),
            tktManaged  =       ui->tktRadioIP->text(),
            tktMAC      =       ui->tktRouterMAC->text(),
            tktNotes    =       ui->tktNotes->toPlainText();

    // Check for blanks.
    checkBlank(tktNotes);

    // Create appropriate template lines.
    QString line1 = "Escalating Reason: " + tktReason;
    QString line2 = "Date: " + today.toString();
    QString line3 = "Customer Name: " + cstName;
    QString line4 = "Customer ID: " + cstID;
    QString line5 = "-------------------------------------------------";
    QString line6 = tktReason + " Request";
    QString line7 = "Current Aggregate: " + tktAggregate;
    QString line8 = "Radio IP: " + tktManaged;
    QString line9 = "Radio MAC: " + tktMAC + "\n";

    QString line10 = "Notes: " + tktNotes;

    // Check for errors.
    bool error = false;
    error = checkImportantInfo();

    if(!error)
    {
        resetColor();

        ui->ticketTemplate->append(line1);
        ui->ticketTemplate->append(line2);
        ui->ticketTemplate->append(line3);
        ui->ticketTemplate->append(line4);
        ui->ticketTemplate->append(line5);
        ui->ticketTemplate->append(line6);
        ui->ticketTemplate->append(line7);
        ui->ticketTemplate->append(line8);
        ui->ticketTemplate->append(line9);

        ui->ticketTemplate->append(line10);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }

}

void Network_Key::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}

void Network_Key::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

}

void Network_Key::checkBlank(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "NA" || string == "na")
        string = "--";
}

bool Network_Key::checkImportantInfo()
{
    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(ui->cstName->text() == "")
    {
        ui->ticketTemplate->append("Customer's name is needed.");
        return true;
    }
    else if(ui->cstID->text() == "")
    {
        ui->ticketTemplate->append("Customer's ID is needed.");
        return true;
    }
    else if(ui->tktAggregate->text() == "")
    {
        ui->ticketTemplate->append("The radio's aggregate (the current key) is needed.");
        return true;
    }
    else if(ui->tktRadioIP->text() == "")
    {
        ui->ticketTemplate->append("The radio's IP is needed.");
        return true;
    }
    else if(ui->tktRouterMAC->text() == "")
    {
        ui->ticketTemplate->append("The router's MAC address is needed.");
        return true;
    }
    else
    {
        resetColor();
        return false;
    }
}

void Network_Key::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}
