#include "network_static.h"
#include "ui_network_static.h"
#include <QDate>

Network_Static::Network_Static(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Network_Static)
{
    ui->setupUi(this);
}

Network_Static::~Network_Static()
{
    delete ui;
}

void Network_Static::on_pushButton_clicked()
{
    ui->ticketTemplate->clear(); // Clear data already in ticket.

    QDate today = today.currentDate();

    // Data from user.
    QString cstInvoice,
            tktReason   =       "Static IP",
            cstName     =       ui->cstName->text(),
            cstID       =       ui->cstID->text(),
            tktPurpose  =       ui->tktPurpose->text(),
            tktManaged  =       ui->tktRadioIP->text(),
            tktMAC      =       ui->tktRouterMAC->text(),
            tktNotes    =       ui->tktNotes->toPlainText();

    if(ui->cstInvoice->isChecked())
        cstInvoice = "Done";
    else
        cstInvoice = "";

    // Check for blanks.
    checkBlank(tktNotes);

    // Create appropriate template lines.
    QString line1 = "Escalating Reason: " + tktReason;
    QString line2 = "Date: " + today.toString();
    QString line3 = "Customer Name: " + cstName;
    QString line4 = "Customer ID: " + cstID;
    QString line5 = "-------------------------------------------------";
    QString line6 = tktReason + " Request";
    QString line7 = "Invoice Paid: " + cstInvoice;
    QString line8 = "Reason: " + tktPurpose;
    QString line9 = "Router MAC Address: " + tktMAC;
    QString line10 = "Management IP: " + tktManaged + "\n";

    QString line11 = "Notes: " + tktNotes;

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

        ui->ticketTemplate->append(line11);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }

}

void Network_Static::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}

void Network_Static::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

    foreach(QCheckBox *widget, this->findChildren<QCheckBox *>())
        widget->setChecked(false);
}

void Network_Static::checkBlank(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "NA" || string == "na")
        string = "--";
}

bool Network_Static::checkImportantInfo()
{
    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(!ui->cstInvoice->isChecked())
    {
        ui->ticketTemplate->append("Invoice Paid needs to be checked.");
        return true;
    }
    else if(ui->cstName->text() == "")
    {
        ui->ticketTemplate->append("Customer's name is needed.");
        return true;
    }
    else if(ui->cstID->text() == "")
    {
        ui->ticketTemplate->append("Customer's ID is needed.");
        return true;
    }
    else if(ui->tktPurpose->text() == "")
    {
        ui->ticketTemplate->append("A reason for for the static IP is needed.");
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

void Network_Static::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}
