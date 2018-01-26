#include "network_voip.h"
#include "ui_network_voip.h"
#include <QDate>

Network_Voip::Network_Voip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Network_Voip)
{
    ui->setupUi(this);
}

Network_Voip::~Network_Voip()
{
    delete ui;
}

void Network_Voip::on_pushButton_clicked()
{
    ui->ticketTemplate->clear(); // Clear data already in ticket.

    QDate today = today.currentDate();

    // Data from user.
    QString tktReason       =       "VOIP / Nextiva",
            cstName         =       ui->cstName->text(),
            cstID           =       ui->cstID->text(),
            cstStatus,
            tktPurpose      =       ui->tktPurpose->toPlainText(),
            tktManaged      =       ui->tktIP->text(),
            tktMAC          =       ui->tktVoipMAC->text(),
            tktQFirmware    =       ui->tktQFirmware->text(),
            genPlugged,
            genRegistered,
            genLine1,
            genPaying,
            genAssignment,
            cstEmail        =       ui->cstEmail->text(),
            cstCallerID     =       ui->cstCallerID->text();

    // Current Customer?
    if(ui->cstCurrent->isChecked())
        cstStatus = "Current Customer";
    else if(ui->cstNew->isChecked())
        cstStatus = "New Customer";
    else
        cstStatus = "ERROR -- Please take a screen shot and report this to Lee.";


    // Firmware / Config updated?
    if(ui->tktQFirmware->isChecked())
    {
        tktQFirmware = "Completed";
    }
    else
        tktQFirmware = "Not Completed";


    // Plugged in First?
    if(ui->yes_Plugged->isChecked())
    {
        genPlugged = "Yes";
    }
    else if(ui->no_Plugged->isChecked())
    {
        genPlugged = "No";
    }
    else
        genPlugged = "";


    // Registered State?
    if(ui->yes_registered->isChecked())
    {
        genRegistered = "Yes";
    }
    else if(ui->no_registered->isChecked())
    {
        genRegistered = "No";
    }
    else
        genRegistered = "";


    // Plugged into Line 1?
    if(ui->yes_line1->isChecked())
        genLine1 = "Yes";
    else if(ui->no_line1->isChecked())
        genLine1 = "No";
    else if(ui->other_line1->isChecked())
        genLine1 = ui->other_line1Text->text();
    else
        genLine1 = "";



    // Paying?
    if(ui->yes_paying->isChecked())
        genPaying = "Yes";
    else if(ui->no_paying->isChecked())
        genPaying = "No";
    else
        genPaying = "";


    // Number Assignemnt
    if(ui->new_assignment->isChecked())
    {
        genAssignment = "New";
    }
    else if(ui->ported_assignment->isChecked())
    {
        genAssignment = "Ported";
    }
    else
        genAssignment = "";




    // Create appropriate template lines without conditions.
    QString line1 = "Escalating Reason: " + tktReason;
    QString line2 = "Date: " + today.toString();
    QString line3 = "Customer Name: " + cstName;
    QString line4 = "Customer ID: " + cstID;
    QString line5 = "-------------------------------------------------";
    QString line6 = tktReason + " Trouble";
    QString line7 = "Customer Status: " + cstStatus;
    QString line8 = "Reason: " + tktPurpose;
    QString line9 = "Router MAC Address: " + tktMAC;
    QString line10 = "Public or Private IP Address of Adapter: " + tktManaged;
    QString line11 = "Firmware / Config Updated?: " + tktQFirmware;
    QString line12 = "";
    QString line13 = "";
    QString line14 = "";
    QString line15 = "";



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

        // Conditional lines. Based on current or new customer.s
        if(ui->cstCurrent->isChecked())     // Current Customer
        {
            line12 = "Is the VoIP Adapter Plugged in First?: " + genPlugged;
            line13 = "Is the VoIP Line in a Registered State?: " + genRegistered;
            line14 = "Phone Plugged into Line 1?: " + genLine1;
        }
        else if(ui->cstNew->isChecked())    // New Customer
        {
            line12 = "Is the Customer Currently Paying for VoIP?: " + genPaying;
            line13 = "Number Assignment: " + genAssignment;

            if(ui->ported_assignment->isChecked())
            {
                line14 = "      Email Address: " + cstEmail;
                line15 = "Caller ID: " + cstCallerID;
            }
            else
            {
                line14 = "Caller ID: " + cstCallerID;
                line15 = "";
            }
        }

        ui->ticketTemplate->append(line12);
        ui->ticketTemplate->append(line13);
        ui->ticketTemplate->append(line14);
        ui->ticketTemplate->append(line15);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }

}

void Network_Voip::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}

void Network_Voip::on_Clear_clicked()
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
    ui->group_Current_Customer->setDisabled(true);
    ui->group_New_Customer->setDisabled(true);
}

void Network_Voip::checkBlank(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "NA" || string == "na")
        string = "--";
}

bool Network_Voip::checkImportantInfo()
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
    else if(!ui->cstCurrent->isChecked() && !ui->cstNew->isChecked())
    {
        ui->ticketTemplate->append("You need to select if the customer is a current or new customer.");
        return true;
    }
    else if(!ui->tktQFirmware->isChecked())
    {
        ui->ticketTemplate->append("Firmware / Config must be updated. Check the box if or when this is done.");
        return true;
    }
    else if(ui->tktVoipMAC->text() == "")
    {
        ui->ticketTemplate->append("The router's MAC address is needed.");
        return true;
    }
    else if(ui->tktIP->text() == "")
    {
        ui->ticketTemplate->append("The IP of the adapter is needed.");
        return true;
    }
    else if(ui->tktPurpose->toPlainText() == "")
    {
        ui->ticketTemplate->append("Please fill out the reason for the escalation.");
        return true;
    }
    else if(ui->cstCurrent->isChecked())
    {
        if(!ui->yes_Plugged->isChecked() && !ui->no_Plugged->isChecked())
        {
            ui->ticketTemplate->append("Please check if the VoIP adapter is plugged in first.");
            return true;
        }
        else if(!ui->yes_registered->isChecked() && !ui->no_registered->isChecked())
        {
            ui->ticketTemplate->append("Please check if the VoIP line is in a registered state or not.");
            return true;
        }
        else if(!ui->yes_line1->isChecked() && !ui->no_line1->isChecked() && !ui->other_line1->isChecked())
        {
            ui->ticketTemplate->append("Please check that the phone is plugged into line 1.");
            return true;
        }
        else if(ui->other_line1->isChecked() && ui->other_line1Text->text() == "")
        {
            ui->ticketTemplate->append("Please fill out why you selected 'other'.");
            return true;
        }
        else
            return false;
    }
    else if(ui->cstNew->isChecked())
    {
        if(!ui->yes_paying->isChecked() && !ui->no_paying->isChecked())
        {
            ui->ticketTemplate->append("Check if the customer is paying for the VoIP service or not.");
            return true;
        }
        else if(ui->no_paying->isChecked())
        {
            ui->ticketTemplate->append("If the customer is not paying, then transfer them to the billing department.");
            return true;
        }
        else if(!ui->new_assignment->isChecked() && !ui->ported_assignment->isChecked())
        {
            ui->ticketTemplate->append("The number assignment information is needed.");
            return true;
        }
        else if(ui->ported_assignment->isChecked() && ui->cstEmail->text() == "")
        {
            ui->ticketTemplate->append("A current email address is needed if the number is going to be ported.");
            return true;
        }
        else if(ui->cstCallerID->text() == "")
        {
            ui->ticketTemplate->append("The caller ID is needed.");
            return true;
        }
        else
            return false;
    }
    else
    {
        resetColor();
        return false;
    }
}

void Network_Voip::on_other_line1_clicked()
{
    if(ui->other_line1->isChecked())
    {
        ui->other_line1Text->setEnabled(true);
    }
}

void Network_Voip::on_ported_assignment_clicked()
{
    if(ui->ported_assignment->isChecked())
    {
        ui->cstEmail->setEnabled(true);
    }
}

void Network_Voip::on_cstCurrent_clicked()
{
    if(ui->cstCurrent->isChecked())
    {
        ui->group_Current_Customer->setEnabled(true);
        ui->group_New_Customer->setDisabled(true);

        ui->cstID->setEnabled(true);
    }
}

void Network_Voip::on_cstNew_clicked()
{
    if(ui->cstNew->isChecked())
    {
        ui->group_New_Customer->setEnabled(true);
        ui->group_Current_Customer->setDisabled(true);

        ui->cstID->setDisabled(true);
    }
}


void Network_Voip::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}
