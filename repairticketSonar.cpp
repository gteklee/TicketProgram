#include "repairticketSonar.h"
#include "ui_repairticketSonar.h"

RepairTicketSonar::RepairTicketSonar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RepairTicketSonar)
{
    ui->setupUi(this);

    ui->tktTower->addItems(towers);
}

RepairTicketSonar::~RepairTicketSonar()
{
    delete ui;
}





/**
 * When generate ticket is clicked - generate ticket.
 */
void RepairTicketSonar::on_pushButton_clicked()
{

    // Clear any data that is already in the ticket field.
    ui->ticketTemplate->clear();


    // Getting our data from the user.
    QString tktType         = ui->tktType->currentText(),
            tktZone         = ui->tktZone->currentText(),
            tktTower        = ui->tktTower->currentText(),
            tktNotes        = ui->tktNotes->toPlainText(),
            cstName         = ui->cstName->text(),
            cstTest         = ui->cstTest->text(),
            cstTorch        = ui->cstTorch->text(),
            cstPackage      = ui->cstPackage->currentText(),
            radioManaged    = ui->radioIP->text(),
            radioPublic     = ui->radioPublic->text(),
            radioMAC        = ui->radioMAC->text(),
            radioType       = ui->radioType->currentText(),
            radioTypeType   = ui->radioTypeType->currentText(),
            radioSSID       = ui->radioSSID->text(),
            radioCCQ        = ui->radioCCQ->text(),
            radioQuaCap     = ui->radioQuaCap->text(),
            radioSignal     = ui->radioSignal->text(),
            radioLastSignal = ui->radioLastSignal->text(),
            radioAPCount    = ui->radioQAPCount->text(),
            radioTest       = ui->radioTest->text();


    checkNA(tktType);
    QString line1 = "Fix Ticket Type: " + tktType + "\n";

    checkNA(tktZone);
    checkNA(tktTower);
    checkNA(cstName);

    QString line3 = cstName;// + cstID;

    checkNA(cstPackage);
    QString line4 = cstPackage + "\n";

    checkNA(radioManaged);
    QString line9 = "Manage IP: " + radioManaged;

    checkNA(radioPublic);
    QString line10 = "Public IP: " + radioPublic;

    checkNA(radioMAC);
    QString line11 = "MAC of Radio: " + radioMAC;

    checkNA(radioType);
    QString line12 = "Radio Type: " + radioType + " " + radioTypeType;

    checkNA(radioSSID);
    QString line14 = "SSID: " + radioSSID;

    checkNA(radioCCQ);
    QString line15 = "CCQ: " + radioCCQ;

    checkNA(radioQuaCap);
    QString line16 = "Qual/Cap: " + radioQuaCap;

    checkNA(radioSignal);
    QString line17 = "Radio Signal: " + radioSignal;

    checkNA(radioLastSignal);
    QString line19 = "Last Known Good Signal: " + radioLastSignal;

    checkNA(radioAPCount);
    QString line23 = "AP CST Count: " + radioAPCount;

    checkNA(cstTorch);
    QString line25 = "Torch Results: " + cstTorch;

    checkNA(radioTest);
    QString line26 = "Radio Speed Test Results: " + radioTest;

    checkNA(cstTest);
    QString line27 = "CST Speed Test Results: " + cstTest + "\n";

    QString line38 = "Notes: " + tktNotes;


    // Checking for important fields and sending an error message if they are not filled out.
    /** FIELDS THAT MUST BE FILLED OUT:  */
    bool error = false;
    error = checkImportantInfo();


    // Here we generate the ticket.
    if(error == false)
    {
        resetColor();

        ui->ticketTemplate->append(line1);

        ui->ticketTemplate->append(line3);
        ui->ticketTemplate->append(line4);

        ui->ticketTemplate->append(line9);
        ui->ticketTemplate->append(line10);
        ui->ticketTemplate->append(line11);
        ui->ticketTemplate->append(line12);
        ui->ticketTemplate->append(line14);
        ui->ticketTemplate->append(line15);
        ui->ticketTemplate->append(line16);
        ui->ticketTemplate->append(line17);
        ui->ticketTemplate->append(line19);
        ui->ticketTemplate->append(line23);
        ui->ticketTemplate->append(line25);
        ui->ticketTemplate->append(line26);
        ui->ticketTemplate->append(line27);

        ui->ticketTemplate->append(line38);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }
}





void RepairTicketSonar::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

    foreach(QComboBox *widget, this->findChildren<QComboBox *>())
        widget->setCurrentText("");

    foreach(QCheckBox *widget, this->findChildren<QCheckBox *>())
        widget->setChecked(false);

    resetColor();
}





void RepairTicketSonar::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}





/**
 * Checking if text for ticket generation should be changed to "NA".
 * @param string
 */
void RepairTicketSonar::checkNA(QString &string)
{
    if(string == "")
        string = "--";
}







/**
 * Checks all information that must at least have some type of data before
 * ticket is generated.
 */
bool RepairTicketSonar::checkImportantInfo()
{
    // Check all important informtion that needs to be filled out.
    // If something is not filled out, the error message will appear
    // where the ticket normally would.
    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(ui->tktType->currentText() == "")
    {
        ui->ticketTemplate->append("\"Fix Ticket Type:\" Needs to be selected.");
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
    }
    else if(!ui->tktQTrip->isChecked())
    {
        ui->ticketTemplate->append("\"$65 trip fee explained\" Needs to be checked. Make sure you explain the possible trip fee.");
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
    else if(ui->cstName->text() == "") /** Customer Section... **/                         // Removed per Joey for build 2.0
    {
        ui->ticketTemplate->append("Customer's name is needed.");
        return true;
    }
    else if(!ui->cstPackRes->isChecked() && !ui->cstPackBus->isChecked() && !ui->cstPackOth->isChecked())
    {
        ui->ticketTemplate->append("A package must be chosen.");
        return true;
    }
    else if(ui->radioIP->text() == "") /** Radio Information Section... **/
    {
        ui->ticketTemplate->append("Radio's Managed IP needs to be filled out.");
        return true;
    }
    else if(ui->radioPublic->text() == "")
    {
        ui->ticketTemplate->append("Customer's Public IP needs to be filled out.");
        return true;
    }
    else if(ui->radioMAC->text() == "")
    {
        ui->ticketTemplate->append("Radio's MAC Address needs to be filled out.");
        return true;
    }
    else if(!ui->radioFirmware->isChecked() && ui->tktType->currentText() != "Radio down")
    {
        ui->ticketTemplate->append("Radio's Firmware version needs to be up to date needs to be checked. Make sure the radio has the correct firmware.");
        return true;
    }
    else if(ui->radioType->currentText() == "")
    {
        ui->ticketTemplate->append("Radio Type needs to be selected.");
        return true;
    }
    else if(ui->radioSSID->text() == "")
    {
        ui->ticketTemplate->append("Radio's SSID needs to be filled out.");
        return true;
    }
    else if(ui->tktType->currentText() != "Radio down")
    {
        if(ui->radioType->currentText() == "UBNT")
        {
            if(ui->radioCCQ->text() == "")
            {
                ui->ticketTemplate->append("Radio's CCQ must be filled out.");
                return true;
            }
            else if(ui->radioQuaCap->text() == "")
            {
                ui->ticketTemplate->append("Radio's Quailty / Capacity needs to be filled out.");
                return true;
            }
            else if(ui->radioSignal->text() == "")
            {
                ui->ticketTemplate->append("Radio's Signal Strength needs to be filled out.");
                return true;
            }
        }
        else if(ui->radioType->currentText() == "ePMP")
        {
            if(ui->radioQuaCap->text() == "")
            {
                ui->ticketTemplate->append("Radio's Quailty / Capacity needs to be filled out.");
                return true;
            }
            else if(ui->radioSignal->text() == "")
            {
                ui->ticketTemplate->append("Radio's Signal Strength needs to be filled out.");
                return true;
            }
        }
        else if(ui->radioType->currentText() == "Canopy")
        {
            if(ui->radioSignal->text() == "")
            {
                ui->ticketTemplate->append("Radio's Signal Strength needs to be filled out.");
                return true;
            }
        }
    }
    else if(ui->radioLastSignal->text() == "")
    {
        ui->ticketTemplate->append("Radio's Last Known Signal is needed. If it is not documented, or cannot be found, put NA.");
        return true;
    }
    else if(ui->radioTest->text() == "" && ui->tktType->currentText() != "Radio down" && ui->tktType->currentText() != "No connection")
    {
        ui->ticketTemplate->append("Radio's Speed Test is needed. If it cannot be done put NA.");
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
void RepairTicketSonar::on_tktZone_currentTextChanged(const QString &string)
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

void RepairTicketSonar::on_tktTower_currentTextChanged(const QString &string)
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





/*/**
 * When tktQ90 is set to a value other than 0, enable the group box that contains       // Removed per Joey for build 2.0
 * the selection for I90 or R90.
 * @param string
 *
void RepairTicket::on_tktQ90_currentTextChanged(const QString &string)
{
    if(string != "0") ui->tkt_Group_90days->setEnabled(true);
    else
    {
        if(ui->I90->isChecked())
        {
            ui->I90->setAutoExclusive(false);
            ui->I90->setChecked(false);
            ui->I90->setAutoExclusive(true);
            ui->tktPrevTech->setDisabled(true);
        }
        else if(ui->R90->isChecked())
        {
            ui->R90->setAutoExclusive(false);
            ui->R90->setChecked(false);
            ui->R90->setAutoExclusive(true);
            ui->tktPrevJob->setDisabled(true);
            ui->tktPrevTech->setDisabled(true);
        }
        ui->tktPrevTech->clear();
        ui->tktPrevJob->clear();
        ui->tkt_Group_90days->setDisabled(true);
    }
}*/







/*/**
 * When checkbox is checked, it enables the alternative cell to
 * be entered.
 * @param string
 *
void RepairTicket::on_cstCheckPhoneAlt_stateChanged(int state)              // Removed per Joey for build 2.0
{
    if(state != 0) ui->cstPhoneAlt->setEnabled(true);
    else
    {
        ui->cstPhoneAlt->clear();
        ui->cstPhoneAlt->setDisabled(true);
    }
}*/







/*/**
 * BEGIN: The following three functions are for the package group.
 *
/**
 * When checked - set the list for the Package drop down.
 *
void RepairTicket::on_cstPackRes_clicked()
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


void RepairTicket::on_cstPackOth_clicked()
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

void RepairTicket::on_cstPackBus_clicked()
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






/**
 * When the radio type is selected, the drop down changes to the brands of the type.
 * @param string
 */
void RepairTicketSonar::on_radioType_currentTextChanged(const QString &string)
{
    // Clearing list.
    ui->radioTypeType->clear();

    // Enabling list.
    ui->radioTypeType->setEnabled(true);

    // Change the list of the brand based on the type selected.
    if(string == "UBNT")
    {
        ui->radioTypeType->addItems(ubnt);
        ui->radioCCQ->setEnabled(true);
    }
    else if(string == "Canopy")
    {
        ui->radioTypeType->addItems(canopy);
        ui->radioCCQ->setDisabled(true);
    }
    else if(string == "LTE - Telrad")
    {
        ui->radioTypeType->addItems(telrad);
        ui->radioCCQ->setDisabled(true);
    }
    else
    {
        ui->radioTypeType->setDisabled(true);
        ui->radioCCQ->setDisabled(true);
    }
}








/*/**
 * When I90 is selected only enable the tech's name box.
 *
void RepairTicket::on_I90_clicked()
{
    ui->tktPrevJob->clear();
    if(ui->I90->isChecked())
    {
        ui->tktPrevJob->setDisabled(true);
        ui->tktPrevTech->setEnabled(true);
    }
}



                                                                // Removed per Joey for build 2.0



/**
 * When R90 is selected enable both boxes.
 */
/*void RepairTicket::on_R90_clicked()
{
    if(ui->R90->isChecked())
    {
        ui->tktPrevJob->setEnabled(true);
        ui->tktPrevTech->setEnabled(true);
    }
}*/







/**
 * When radio down is selected, disable the information that is not needed.
 * @param string
 */
void RepairTicketSonar::on_tktType_currentTextChanged(const QString &string)
{

    // IF "Radio Down" is selected.
    if(string == "Radio down")
    {
        // Disable cst speed test.
        ui->cstTest->setDisabled(true);

        // Disable cst torch.
        ui->cstTorch->setDisabled(true);

        // Disable radio speed test.
        ui->radioTest->setDisabled(true);

        /*// Disable radio frequency input.
        ui->radioFreq->setDisabled(true);*/                         // Removed per Joey for build 2.0

        // Disable CCQ
        ui->radioCCQ->setDisabled(true);

        // Disable Qual/CAP
        ui->radioQuaCap->setDisabled(true);

        // Disable Signal Level
        ui->radioSignal->setDisabled(true);

        // Disable Firmware Version
        ui->radioFirmware->setDisabled(true);

        // Disable AP CST Count
        ui->radioQAPCount->setDisabled(true);

        /*// Disable AP Saturated
        ui->radioQAPSat->setDisabled(true);*/                       // Removed per Joey for build 2.0
    }
    else if(string == "No connection")
    {
        // Disable cst speed test.
        ui->cstTest->setDisabled(true);

        // Disable radio speed test.
        ui->radioTest->setDisabled(true);

        // Enable if going from radio down to no connection.
        ui->cstTorch->setEnabled(true);
        //ui->radioFreq->setEnabled(true);                          // Removed per Joey for build 2.0
        ui->radioSSID->setEnabled(true);
        ui->radioCCQ->setEnabled(true);
        ui->radioQuaCap->setEnabled(true);
        ui->radioSignal->setEnabled(true);
        ui->radioFirmware->setEnabled(true);
        ui->radioLastSignal->setEnabled(true);
        ui->radioQAPCount->setEnabled(true);
        //ui->radioQAPSat->setEnabled(true);                        // Removed per Joey for build 2.0
    }
    else if(string == "Poor Signal")
    {
        // Poor signal disables.
        ui->cstTest->setDisabled(true);
        ui->radioTest->setDisabled(true);

        // Enable going from radio down to poor signal.
        ui->cstTorch->setEnabled(true);
        ui->radioSSID->setEnabled(true);
        ui->radioCCQ->setEnabled(true);
        ui->radioQuaCap->setEnabled(true);
        ui->radioSignal->setEnabled(true);
        ui->radioFirmware->setEnabled(true);
        ui->radioLastSignal->setEnabled(true);
        ui->radioQAPCount->setEnabled(true);
    }
    else if(string == "Conversion")
    {
        // Conversion disables.
        ui->cstTest->setDisabled(true);
        ui->radioTest->setDisabled(true);

        // Enable going from radio down to conversion.
        ui->cstTorch->setEnabled(true);
        ui->radioSSID->setEnabled(true);
        ui->radioCCQ->setEnabled(true);
        ui->radioQuaCap->setEnabled(true);
        ui->radioSignal->setEnabled(true);
        ui->radioFirmware->setEnabled(true);
        ui->radioLastSignal->setEnabled(true);
        ui->radioQAPCount->setEnabled(true);
    }
    else
    {
        ui->cstTorch->setEnabled(true);
        ui->cstTest->setEnabled(true);
        ui->radioTest->setEnabled(true);
        //ui->radioFreq->setEnabled(true);                          // Removed per Joey for build 2.0
        ui->radioSSID->setEnabled(true);
        ui->radioCCQ->setEnabled(true);
        ui->radioQuaCap->setEnabled(true);
        ui->radioSignal->setEnabled(true);
        ui->radioFirmware->setEnabled(true);
        ui->radioLastSignal->setEnabled(true);
        ui->radioQAPCount->setEnabled(true);
        //ui->radioQAPSat->setEnabled(true);                        // Removed per Joey for build 2.0
    }
}





/**
 * BEGIN: The following three functions are for the package group.
 *
/**
 * When checked - set the list for the Package drop down.
 */
void RepairTicketSonar::on_cstPackRes_clicked()
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


void RepairTicketSonar::on_cstPackOth_clicked()
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

void RepairTicketSonar::on_cstPackBus_clicked()
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






void RepairTicketSonar::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));

    /*ui->tktType_label->setText("<font color = 'black'>" + ui->tktType_label->text() + "</font>");
    ui->tktZone_label->setText("<font color = 'black'>" + ui->tktZone_label->text() + "</font>");*/
}
