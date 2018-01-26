#include "onsite.h"
#include "ui_onsite.h"

Onsite::Onsite(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Onsite)
{
    ui->setupUi(this);

    ui->tktTower->addItems(towers);
}

Onsite::~Onsite()
{
    delete ui;
}


/**
 *  When this button is clicked - generate ticket.
 */
void Onsite::on_pushButton_clicked()
{
    ui->ticketTemplate->clear(); // Clear data already in ticket.

    // Data from user.
    QString tktType =       "Onsite",
            cstName =       ui->cstName->text(),
            cstPackage      = ui->cstPackage->currentText(),
            tktZone =       ui->tktZone->currentText(),
            tktTower =      ui->tktTower->currentText(),
            cstInternet,
            radioManaged =  ui->radioIP->text(),
            radioPublic =   ui->radioPublic->text(),
            radioType   =   ui->radioType->currentText(),
            radioTypeType = ui->radioTypeType->currentText(),
            tktReason =     ui->tktReason->toPlainText(),
            tktWork =       ui->tktWork->toPlainText(),
            tktSpecial =    ui->tktSpecial->text(),
            tktNotes =      ui->tktNotes->toPlainText();


    if(ui->cstInternet->isChecked())
        cstInternet = "Yes";
    else
        cstInternet = "No";


    // Check for blanks.
    checkBlank(radioManaged);
    checkBlank(radioPublic);
    checkBlank(radioType);
    checkBlank(tktReason);
    checkBlank(tktWork);
    checkBlank(tktSpecial);
    checkBlank(tktNotes);

    // Create appropriate ticket lines.
    QString line1 = "Fix Ticket Type: " + tktType + "\n";

    QString line2 = cstName;
    QString line2_1 = cstPackage;
    QString line3 = "Zone: " + tktZone;
    QString line4 = "Connected/Closest Tower: " + tktTower + "\n";

    QString line5 = "Internet Customer? " + cstInternet;

    QString line9 = "Reason for onsite: " + tktReason + "\n";
    QString line10 = "Expected Work: " + tktWork;
    QString line11 = "Special Equipment: " + tktSpecial + "\n";

    QString line12 = "Notes: " + tktNotes;

    // Check for errors.
    bool error = false;
    error = checkImportantInfo();

    if(error == false)
    {
        resetColor();

        ui->ticketTemplate->append(line1);

        ui->ticketTemplate->append(line2);
        ui->ticketTemplate->append(line2_1);
        ui->ticketTemplate->append(line3);
        ui->ticketTemplate->append(line4);

        ui->ticketTemplate->append(line5);

        if(ui->cstInternet->isChecked())
        {
            QString line6 = "Managed IP: " + radioManaged;
            QString line7 = "Public IP: " + radioPublic;
            QString line8 = "Radio Type: " + radioType + " " + radioTypeType + "\n";

            ui->ticketTemplate->append(line6);
            ui->ticketTemplate->append(line7);
            ui->ticketTemplate->append(line8);
        }
        else
            ui->ticketTemplate->append("");

        ui->ticketTemplate->append(line9);
        ui->ticketTemplate->append(line10);
        ui->ticketTemplate->append(line11);

        ui->ticketTemplate->append(line12);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }
}





void Onsite::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}





void Onsite::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

    foreach(QComboBox *widget, this->findChildren<QComboBox *>())
        widget->setCurrentText("");

    foreach(QCheckBox *widget, this->findChildren<QCheckBox *>())
        widget->setChecked(false);

    checkDisabled();
}





void Onsite::checkDisabled()
{
    if(!ui->cstInternet->isChecked())
    {
        ui->radioIP->setDisabled(true);
        ui->radioPublic->setDisabled(true);
        ui->radioType->setDisabled(true);
    }
}





void Onsite::checkBlank(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "NA" || string == "na")
        string = "--";
}





bool Onsite::checkImportantInfo()
{
    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(ui->cstName->text() == "")
    {
        ui->ticketTemplate->append("Customer's name is needed.");
        return true;
    }
    else if(!ui->cstPackRes->isChecked() && !ui->cstPackBus->isChecked() && !ui->cstPackOth->isChecked())
    {
        ui->ticketTemplate->append("A package must be chosen.");
        return true;
    }
    else if(ui->cstInternet->isChecked() && ui->radioIP->text() == "")
    {
        ui->ticketTemplate->append("Radio's Managed IP needs to be filled out.");
        return true;
    }
    else if(ui->cstInternet->isChecked() && ui->radioPublic->text() == "")
    {
        ui->ticketTemplate->append("Customer's Public IP needs to be filled out.");
        return true;
    }
    else if(ui->cstInternet->isChecked() && ui->radioType->currentText() == "")
    {
        ui->ticketTemplate->append("Radio Type needs to be selected.");
        return true;
    }
    else if(ui->tktZone->currentText() == "")
    {
        ui->ticketTemplate->append("\"Zone:\" Needs to be selected.");
        return true;
    }
    else if(!ui->tktQConfirm->isChecked())
    {
        ui->ticketTemplate->append("\"Confirmation call was explained\" Needs to be checked. Make sure you explain the confirmation call process.");
        return true;
    }
    else if(!ui->tktQAbsent->isChecked())
    {
        ui->ticketTemplate->append("\"$25 absent fee explained\" Needs to be checked. Make sure you explain the possible absent fee.");
        return true;
    }
    else if(!ui->tktQTrip->isChecked())
    {
        ui->ticketTemplate->append("\"$65 trip fee explained\" Needs to be checked. Make sure you explain the possible trip fee.");
        return true;
    }
    else if(!ui->tktQDueDate->isChecked())
    {
        ui->ticketTemplate->append("\"Due date is correct in Sonar ticket.\" Needs to be checked. Make sure the due date in Sonar is updated and correct.");
        return true;
    }
    else if(!ui->tktQDisclose->isChecked())
    {
        ui->ticketTemplate->append("\"Disclosure Read.\" Needs to be checked. Make sure you read the disclosure to the customer.");
        return true;
    }
    else if(ui->tktReason->toPlainText() == "")
    {
        ui->ticketTemplate->append("\"Reason for onsite:\" needs to be filled out.");
        return true;
    }
    else if(ui->tktWork->toPlainText() == "")
    {
        ui->ticketTemplate->append("\"Expected work to be done:\" needs to be filled out.");
        return true;
    }
    else
    {
        resetColor();
        return false;
    }

}





/**
 * Whatever radio type is selected, add list to the radio type type drop down.
 */
void Onsite::on_radioType_currentTextChanged(const QString &string)
{
   // Clear the list.
   ui->radioTypeType->clear();

   // Enabling the list.
   ui->radioTypeType->setEnabled(true);

   // Change the list of the brand based on the type selected.
   if(string == "UBNT")
       ui->radioTypeType->addItems(ubnt);
   else if(string == "Canopy")
       ui->radioTypeType->addItems(canopy);
   else if(string == "LTE - Telrad")
       ui->radioTypeType->addItems(telrad);
   else
       ui->radioTypeType->setDisabled(true);
}





/**
 * Whatever zone is selected, add list to the tower drop down selection.
 * @param string
 */
void Onsite::on_tktZone_currentTextChanged(const QString &string)
{
    QString tower = ui->tktTower->currentText();

    // Clearing the tower drop downs if the zone combo box is updated.
    ui->tktTower->clear();

    // Set the drop down for the tower combo box.
    if(string == "1")
    {
        if(tower == "")
            ui->tktTower->addItems(zone1);
        else
        {
            ui->tktTower->addItems(zone1);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "2")
    {
        if(tower == "")
            ui->tktTower->addItems(zone2);
        else
        {
            ui->tktTower->addItems(zone2);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "3")
    {
        if(tower == "")
            ui->tktTower->addItems(zone3);
        else
        {
            ui->tktTower->addItems(zone3);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "4")
    {
        if(tower == "")
            ui->tktTower->addItems(zone4);
        else
        {
            ui->tktTower->addItems(zone4);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "5")
    {
        if(tower == "")
            ui->tktTower->addItems(zone5);
        else
        {
            ui->tktTower->addItems(zone5);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "6")
    {
        if(tower == "")
            ui->tktTower->addItems(zone6);
        else
        {
            ui->tktTower->addItems(zone6);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "7")
    {
        if(tower == "")
            ui->tktTower->addItems(zone7);
        else
        {
            ui->tktTower->addItems(zone7);
            ui->tktTower->setCurrentText(tower);
        }
    }
    else if(string == "")
        ui->tktTower->addItems(towers);
}

void Onsite::on_tktTower_currentTextChanged(const QString &string)
{

    // Get current tower selection.
    QString currentTower = string;
    QString listTower;

    // Check in zone 1.
    for(int i = 0; i < zone1.size(); i++)
    {
        listTower = zone1[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("1");
            return;
        }
    }

    // Check in zone 2.
    for(int i = 0; i < zone2.size(); i++)
    {
        listTower = zone2[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("2");
            return;
        }
    }

    // Check in zone 3.
    for(int i = 0; i < zone3.size(); i++)
    {
        listTower = zone3[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("3");
            return;
        }
    }

    // Check in zone 4.
    for(int i = 0; i < zone4.size(); i++)
    {
        listTower = zone4[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("4");
            return;
        }
    }

    // Check in zone 5.
    for(int i = 0; i < zone5.size(); i++)
    {
        listTower = zone5[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("5");
            return;
        }
    }

    // Check in zone 6.
    for(int i = 0; i < zone6.size(); i++)
    {
        listTower = zone6[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("6");
            return;
        }
    }

    // Check in zone 7.
    for(int i = 0; i < zone7.size(); i++)
    {
        listTower = zone7[i];

        if(currentTower == listTower)
        {
            ui->tktZone->setCurrentText("7");
            return;
        }
    }

}



// Internet customer.
void Onsite::on_cstInternet_clicked()
{
    if(ui->cstInternet->isChecked())
    {
        ui->radioIP->setEnabled(true);
        ui->radioPublic->setEnabled(true);
        ui->radioType->setEnabled(true);
    }
    else
    {
        ui->radioIP->setDisabled(true);
        ui->radioPublic->setDisabled(true);
        ui->radioType->setDisabled(true);

        // Clear if filled out.
        ui->radioIP->clear();
        ui->radioPublic->clear();
        ui->radioType->setCurrentText("");
    }
}





/**
 * BEGIN: The following three functions are for the package group.
 *
/**
 * When checked - set the list for the Package drop down.
 */
void Onsite::on_cstPackRes_clicked()
{
    // Creating list.
    QList<QString> package_Res;
    package_Res.append("Residential Steel");
    package_Res.append("Residential Bronze");
    package_Res.append("Residential Silver");
    package_Res.append("Residential Gold");
    package_Res.append("Residential Platinum");

    // Clearing any data in the package drop down.
    ui->cstPackage->clear();

    // Adding package list to the drop down.
    ui->cstPackage->addItems(package_Res);
}


void Onsite::on_cstPackOth_clicked()
{
    // Creating list.
    QList<QString> package_other;
    package_other.append("Trade Agreement");
    package_other.append("Point-To-Point");

    // Clearing any data in the package drop down.
    ui->cstPackage->clear();

    // Adding package list to the drop down.
    ui->cstPackage->addItems(package_other);
}

void Onsite::on_cstPackBus_clicked()
{
    // Creating list.
    QList<QString> package_Bus;

    package_Bus.append("Business Steel");
    package_Bus.append("Business Bronze");
    package_Bus.append("Business Silver");
    package_Bus.append("Business Gold");
    package_Bus.append("Business Platinum");

    // Clearing any data in the package drop down.
    ui->cstPackage->clear();

    // Adding package list to the drop down.
    ui->cstPackage->addItems(package_Bus);
}

/** END: package group functions. **/





void Onsite::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}
