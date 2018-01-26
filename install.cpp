#include "install.h"
#include "ui_install.h"

Install::Install(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Install)
{
    ui->setupUi(this);

    // Creating nextDay.
    QDate nextDay = nextDay.currentDate().addDays(1);
    QDate currentDate = currentDate.currentDate();

    // Defaulting date to next system date.
    ui->tktDateText->setDate(nextDay);

    ui->tktTower->addItems(towers);

}

Install::~Install()
{
    delete ui;
}


/**
 * When generate ticket is clicked - generate ticket.
 */
void Install::on_pushButton_clicked()
{

    // Clear any data that is already in the ticket field.
    ui->ticketTemplate->clear();

    // Getting our data from the user.
    QString tktZone         = ui->tktZone->currentText(),
            tktTower        = ui->tktTower->currentText(),
            tktTime,
            tktQStatic,
            tktQInstall,
            tktQHolder,
            tktQConfirm,
            tktQDisclose,
            tktQPayment,
            tktNotes        = ui->tktNotes->toPlainText(),
            cstName         = ui->cstName->text(),
            cstBuilding     = ui->cstBuilding->text(),
            cstRoof         = ui->cstRoof->text(),
            cstFloorCount   = ui->cstFloorCount->text(),
            cstVoip,
            cstRouter,
            cstMaint,
            cstStatement,
            cstAttic,
            cstPackage      = ui->cstPackage->currentText(),
            cstContract,
            cstContractPrice = ui->cstContractPrice->text();

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
        tktTime = "8:00AM - 12:00PM";
    }
    else if(ui->tkt_pm->isChecked())
    {
        tktTime = "12:00PM - 4:00PM";
    }
    else if(ui->tkt_other->isChecked())
    {
        tktTime = ui->tkt_other_time->text();
    }


    // VoIP Service to String.
    if(ui->cstVoipContract->isChecked())
    {
        cstVoip = "No Contract";
    }
    else if(ui->cstVoipYear->isChecked())
    {
        cstVoip = "1 Year";
    }
    else if(ui->cstVoipNo->isChecked())
    {
        cstVoip = "Not Interested";
    }


    // Router to String.
    if(ui->cstRouterManaged->isChecked())
    {
        cstRouter = "Managed Router";
    }
    else if(ui->cstRouterPurchase->isChecked())
    {
        cstRouter = "Purchase Router";
    }
    else if(ui->cstRouterOwn->isChecked())
    {
        cstRouter = "Providing Own Router";
    }


    // Service Maintenance Plan to String.
    if(ui->cstMaintYes->isChecked())
    {
        cstMaint = "Interested";
    }
    else if(ui->cstMaintNo->isChecked())
    {
        cstMaint = "Not Interested";
    }


    // Statements to String.
    if(ui->cstStatePaper->isChecked())
    {
        cstStatement = "Paper";
    }
    else if(ui->cstStateEmail->isChecked())
    {
        cstStatement = "Email";
    }


    // Attic Run to String.
    if(ui->cstAtticYes->isChecked())
    {
        cstAttic = "Yes";
    }
    else if(ui->cstAtticNo->isChecked())
    {
        cstAttic = "No";
    }


    // Customer Contract to String
    if(ui->cstContract150->isChecked())
    {
        cstContract = "1 Year Agreement (" + cstContractPrice  + ")";
    }
    else if(ui->cstContract75->isChecked())
    {
        cstContract = "2 Year Agreement (" + cstContractPrice  + ")";
    }
    else if(ui->cstContractNo->isChecked())
    {
        cstContract = "No Contract (" + cstContractPrice  + ")";
    }


    // Dates to string.
    QDate tktDate = ui->tktDateText->date();
    QString tktDateText = tktDate.toString("M/d/yyyy");

    checkNA(tktDateText);

    QString line1 = "Zone " + tktZone + " - " + tktDateText + " - " + tktTower + " Install - " + cstName + "\n",
            line2 = "======================================",
            line3 = "Installation Date: " + tktDateText + " " + tktTime + "\n",

            line4 = cstName,

            line5 = "Building Type: " + cstBuilding,
            line6 = "Roof Type: " + cstRoof,
            line7 = "Number of Floors: " + cstFloorCount,
            line8 = "Attic Run: " + cstAttic + "\n",

            line9 = "Installation Agreement: " + cstContract,
            line10 = "Internet Service: " + cstPackage,
            line11 = "Service Maintenance Plan: " + cstMaint,
            line12 = "Statements: " + cstStatement,
            line13 = "VoIP Terms: " + cstVoip,
            line14 = "Router Terms: " + cstRouter + "\n",

            line15 = "Notes: " + tktNotes;


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


void Install::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}


/**
 * Checking if text for ticket generation should be changed to "NA".
 * @param string
 */
void Install::checkNA(QString &string)
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
bool Install::checkImportantInfo()
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
    else if(ui->tktTower->currentText() == "")
    {
        ui->ticketTemplate->append("The nearest tower to the customer needs to be selected.");
        return true;
    }
    else if(ui->tktDateText->date() < currentDate)
    {
        ui->ticketTemplate->append("You are not able to schedule the ticket before today's date.");
        return true;
    }
    else if(!ui->tkt_am->isChecked() && !ui->tkt_pm->isChecked() && !ui->tkt_other->isChecked())
    {
        ui->ticketTemplate->append("You need to select a time block assigned to the install.");
        return true;
    }
    else if(ui->tkt_other->isChecked() && ui->tkt_other_time->text() == "")
    {
        ui->ticketTemplate->append("You need to fill out the time if you select 'Other'.");
        return true;
    }
    else if(ui->cstName->text() == "")
    {
        ui->ticketTemplate->append("The customer's name is needed.");
        return true;
    }
    else if(ui->cstBuilding->text() == "")
    {
        ui->ticketTemplate->append("The type of building that we will install on is needed.");
        return true;
    }
    else if(ui->cstRoof->text() == "")
    {
        ui->ticketTemplate->append("The type of roof that we will install on is needed.");
        return true;
    }
    else if(ui->cstPackage->currentText() == "")
    {
        ui->ticketTemplate->append("The type of service plan the customer wants is needed.");
        return true;
    }
    else if(!ui->cstContract150->isChecked() && !ui->cstContract75->isChecked() && !ui->cstContractNo->isChecked())
    {
        ui->ticketTemplate->append("What type of contract is the customer wanting to agree with?");
        return true;
    }
    else if(ui->cstContractPrice->text() == "")
    {
        ui->ticketTemplate->append("What price is the contract agreement? i.e. \"150\", \"75\", etc.");
        return true;
    }
    else if(!ui->cstVoipContract->isChecked() && !ui->cstVoipYear->isChecked() && !ui->cstVoipNo->isChecked())
    {
        ui->ticketTemplate->append("Is the customer interested in VoIP service or not?");
        return true;
    }
    else if(!ui->cstRouterManaged->isChecked() && !ui->cstRouterOwn->isChecked() && !ui->cstRouterPurchase->isChecked())
    {
        ui->ticketTemplate->append("Is the customer interested in getting a router or providing their own?");
        return true;
    }
    else if(!ui->cstMaintYes->isChecked() && !ui->cstMaintNo->isChecked())
    {
        ui->ticketTemplate->append("Is the customer interested in the Service Maintenance Plan?");
        return true;
    }
    else if(!ui->cstStateEmail->isChecked() && !ui->cstStatePaper->isChecked())
    {
        ui->ticketTemplate->append("How does the customer want to receive their billing statments?");
        return true;
    }
    else if(!ui->cstAtticNo->isChecked() && !ui->cstAtticYes->isChecked())
    {
        ui->ticketTemplate->append("Is an attic run going to be required for installation?");
        return true;
    }
    else if(!ui->tktQStatic->isChecked())
    {
        ui->ticketTemplate->append("You need to inform the customer about our Static IP.");
        return true;
    }
    else if(!ui->tktQInstall->isChecked())
    {
        ui->ticketTemplate->append("You need to inform the customer about our Standard Installation Process.");
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
    else if(!ui->tktQPayment->isChecked())
    {
        ui->ticketTemplate->append("The payment disclosure needs to be read to the customer.");
        return true;
    }
    else
    {
        resetColor();
        return false;
    }
}







/**
 * Whatever zone is selected, add list to the tower drop down selection.
 * @param string
 */
void Install::on_tktZone_currentTextChanged(const QString &string)
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


void Install::on_tktTower_currentTextChanged(const QString &string)
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


void Install::on_tkt_other_clicked()
{
    ui->tkt_other_time->setEnabled(true);
}


void Install::on_tkt_am_clicked()
{
    ui->tkt_other_time->setDisabled(true);
}

void Install::on_tkt_pm_clicked()
{
    ui->tkt_other_time->setDisabled(true);
}



/**
 * BEGIN: The following three functions are for the package group.
 *
/**
 * When checked - set the list for the Package drop down.
 */
void Install::on_cstPackRes_clicked()
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


void Install::on_cstPackOth_clicked()
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

void Install::on_cstPackBus_clicked()
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


void Install::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));
}

void Install::on_Clear_clicked()
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
