#include "network_mtl.h"
#include "ui_network_mtl.h"
#include <QDate>

Network_MTL::Network_MTL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Network_MTL)
{
    ui->setupUi(this);
}

Network_MTL::~Network_MTL()
{
    delete ui;
}

void Network_MTL::on_pushButton_clicked()
{
    ui->ticketTemplate->clear(); // Clear data already in ticket.

    QDate today = today.currentDate();

    // Data from user.
    QString tktReason       =       "MTL / MDU",
            cstName         =       ui->cstName->text(),
            cstID           =       ui->cstID->text(),
            cstPhone        =       ui->cstPhone->text(),
            cstStatus,
            checkLeased,
            checkVISP,
            checkVilla,
            tktPurpose      =       ui->tktPurpose->toPlainText();

    // Current Customer?
    if(ui->cstCurrent->isChecked())
        cstStatus = "Current Customer";
    else if(ui->cstNew->isChecked())
        cstStatus = "New Customer";
    else
        cstStatus = "ERROR -- Please take a screen shot and report this to Lee.";

    // New customer checklist.
    if(ui->check_villa->isChecked())
        checkVilla = "Yes";
    else
        checkVilla = "--";

    if(ui->check_leased->isChecked())
        checkLeased = "Leased";
    else
        checkLeased = "--";

    if(ui->check_visp->isChecked())
        checkVISP = "VISP";
    else
        checkVISP = "--";

    // If new customer is seleccted.
    if(ui->cstNew->isChecked())
        cstID = "--";

    // Create appropriate template lines without conditions.
    QString line1 = "Escalating Reason: " + tktReason;
    QString line2 = "Date: " + today.toString();
    QString line3 = "Customer Name: " + cstName;
    QString line4 = "Customer ID: " + cstID;
    QString line4_5 = "Customer Number: " + cstPhone;
    QString line5 = "-------------------------------------------------";
    QString line6 = tktReason + " Trouble";
    QString line7 = "Customer Status: " + cstStatus;
    QString line8 = "Reason: " + tktPurpose;
    QString line9 = "";
    QString line10 = "";
    QString line11 = "";

    checkBlank(cstID);

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
        ui->ticketTemplate->append(line4_5);
        ui->ticketTemplate->append(line5);
        ui->ticketTemplate->append(line6);
        ui->ticketTemplate->append(line7);
        ui->ticketTemplate->append(line8);

        // Conditional lines. Based on current or new customers.

        if(ui->cstNew->isChecked())    // New Customer
        {
            if(ui->check_villa->isChecked())
                line9 = "Villa Del Sol: Advised customer of sign up in Front.";

            if(ui->check_leased->isChecked())
                line10 = "Leased Location: Advised customer of contacting manager for WiFi password.";

            if(ui->check_visp->isChecked())
                line11 = "VISP Park: Advised customer of sign up procedures.";
        }

        ui->ticketTemplate->append(line9);
        ui->ticketTemplate->append(line10);
        ui->ticketTemplate->append(line11);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }

}

void Network_MTL::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}

void Network_MTL::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

    foreach(QCheckBox *widget, this->findChildren<QCheckBox *>())
        widget->setChecked(false);

    foreach(QRadioButton *widget, this->findChildren<QRadioButton *>())
    {
        widget->setAutoExclusive(false);
        widget->setChecked(false);
        widget->setAutoExclusive(true);
    }
    ui->group_New_Customer->setDisabled(true);
}

void Network_MTL::checkBlank(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "NA" || string == "na")
        string = "--";
}

bool Network_MTL::checkImportantInfo()
{
    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(ui->cstName->text() == "")
    {
        ui->ticketTemplate->append("Customer's name is needed.");
        return true;
    }
    else if(ui->cstID->text() == "" && !ui->cstNew->isChecked())
    {
        ui->ticketTemplate->append("Customer's ID is needed.");
        return true;
    }
    else if(ui->cstPhone->text() == "")
    {
        ui->ticketTemplate->append("Customer's phone number is needed.");
        return true;
    }
    else if(!ui->cstCurrent->isChecked() && !ui->cstNew->isChecked())
    {
        ui->ticketTemplate->append("You need to select if the customer is a current or new customer.");
        return true;
    }
    else if(ui->tktPurpose->toPlainText() == "")
    {
        ui->ticketTemplate->append("Please fill out the reason for the escalation.");
        return true;
    }
    /*else if(ui->cstCurrent->isChecked())
    {
    }*/
    else
    {
        resetColor();
        return false;
    }
}

void Network_MTL::on_cstCurrent_clicked()
{
    if(ui->cstCurrent->isChecked())
    {
        ui->group_New_Customer->setDisabled(true);
        ui->cstID->setEnabled(true);
    }
}

void Network_MTL::on_cstNew_clicked()
{
    if(ui->cstNew->isChecked())
    {
        ui->group_New_Customer->setEnabled(true);
        ui->cstID->setDisabled(true);
    }
}


void Network_MTL::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}
