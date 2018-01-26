#include "relo.h"
#include "ui_relo.h"

Relo::Relo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Relo)
{
    ui->setupUi(this);

    // Creating nextDay.
    QDate nextDay = nextDay.currentDate().addDays(1);
    QDate currentDate = currentDate.currentDate();

    // Defaulting date to next system date.
    ui->tktDateText_D->setDate(nextDay);
    ui->tktDateText_R->setDate(nextDay);

    ui->tktTower->addItems(towers);
}

Relo::~Relo()
{
    delete ui;
}


/**
 * When generate ticket is clicked - generate ticket.
 */
void Relo::on_pushButton_clicked()
{

    // Clear any data that is already in the ticket field.
    ui->ticketTemplate->clear();

    // Getting our data from the user.
    QString tktZone         = ui->tktZone->currentText(),
            tktTower        = ui->tktTower->currentText(),
            tktTime,
            cstAddress_D    = ui->cstAddress_D->text(),
            cstAddress_R    = ui->cstAddress_R->text(),
            cstCity_D       = ui->cstCity_D->text(),
            cstCity_R       = ui->cstCity_R->text(),
            tktNotes        = ui->tktNotes->toPlainText();

    // Time stamp for the person creating the ticket.
    QString date, time;
    QDate   currentDate;
    QTime   currentTime;

    currentDate = currentDate.currentDate();
    currentTime = currentTime.currentTime();

    date = currentDate.toString();
    time = currentTime.toString();


    /** Checkboxes to string and RadioButtons to string.*/

    // Time Block to String.
    if(ui->tkt_am->isChecked())
    {
        tktTime = "AM";
    }
    else if(ui->tkt_pm->isChecked())
    {
        tktTime = "PM";
    }


    // Dates to string.
    QDate tktDate_D = ui->tktDateText_D->date(),
          tktDate_R = ui->tktDateText_R->date();
    QString tktDateText_D = tktDate_D.toString("M/d/yyyy"),
            tktDateText_R = tktDate_R.toString("M/d/yyyy");

    checkNA(tktDateText_D);
    checkNA(tktDateText_R);

    QString line1 = "Relocation Ticket",
            line2 = "=======================================",

            line3 = "\nDisconnect Zone: " + tktZone,
            line4 = "Disconnect Date: " + tktDateText_D,
            line5 = "Physical Address (Disconnect): " + cstAddress_D,
            line6 = "City, State Zip (Disconnect): " + cstAddress_R,

            line7 = "\nReinstall Date: " + tktDateText_R + " " + tktTime,
            line8 = "Physical Address (Reinstall): " + cstCity_D,
            line9 = "City, State Zip (Reinstall): " + cstCity_R,

            line10 = "\nClosest Tower to Reinstall: " + tktTower,

            line11 = "\nNotes: " + tktNotes,

            line12 = "\n=======================================";


    // Checking for important fields and sending an error message if they are not filled out.
    /** FIELDS THAT MUST BE FILLED OUT:  */
    bool error = false;
    error = checkImportantInfo();


    // Here we generate the ticket.
    if(error == false)
    {
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


void Relo::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}


/**
 * Checking if text for ticket generation should be changed to "NA".
 * @param string
 */
void Relo::checkNA(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "What was done on the call? Include the customer's attitude. Were they tech savy or not?")
        string = "--";
}







/**
 * Checks all information that must at least have some type of data before
 * ticket is generated.
 */
bool Relo::checkImportantInfo()
{
    // Check all important informtion that needs to be filled out.
    // If something is not filled out, the error message will appear
    // where the ticket normally would.
    QDate currentDate = currentDate.currentDate();

    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(ui->tktZone->currentText() == "")
    {
        ui->ticketTemplate->append("\"Zone:\" Needs to be selected.");
        return true;
    }
    else if(ui->tktDateText_D->date() < currentDate)
    {
        ui->ticketTemplate->append("You are not able to schedule the ticket before today's date.");
        return true;
    }
    else if(ui->tktDateText_R->date() < currentDate)
    {
        ui->ticketTemplate->append("You are not able to schedule the ticket before today's date.");
        return true;
    }
    else if(!ui->tkt_am->isChecked() && !ui->tkt_pm->isChecked())
    {
        ui->ticketTemplate->append("You need to select a time block assigned to the install.");
        return true;
    }
    else if(ui->cstAddress_D->text() == "")
    {
        ui->ticketTemplate->append("You must provide the disconnect address.");
        return true;
    }
    else if(ui->cstAddress_R->text() == "")
    {
        ui->ticketTemplate->append("You must provide the installation address.");
        return true;
    }
    else if(ui->cstCity_D->text() == "")
    {
        ui->ticketTemplate->append("You must provide the city, state, and zip of the disconnect address.");
        return true;
    }
    else if(ui->cstCity_R->text() == "")
    {
        ui->ticketTemplate->append("You must provide the city, state, and zip of the installation address.");
        return true;
    }
    else if(ui->tktTower->currentText() == "")
    {
        ui->ticketTemplate->append("The nearest tower to the customer needs to be selected.");
        return true;
    }
    else if(!ui->tktQHolder->isChecked())
    {
        ui->ticketTemplate->append("You need to inform the customer that the account holder must be onsite.");
    }
    else if(!ui->tktQConfirm->isChecked())
    {
        ui->ticketTemplate->append("You need to infhorm the customer that we need a confirmation before heading out.");
        return true;
    }
    else if(!ui->tktQDisclose->isChecked())
    {
        ui->ticketTemplate->append("The animal disclosure needs to be read to the customer.");
        return true;
    }
    else
    {
        resetColor();
        return false;
    }
}


void Relo::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}

void Relo::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

    foreach(QComboBox *widget, this->findChildren<QComboBox *>())
        widget->setCurrentText("");

    foreach(QCheckBox *widget, this->findChildren<QCheckBox *>())
        widget->setChecked(false);

    foreach(QRadioButton *widget, this->findChildren<QRadioButton *>())
    {
        widget->setAutoExclusive(false);
        widget->setChecked(false);
        widget->setAutoExclusive(true);
    }


    resetColor();
}
