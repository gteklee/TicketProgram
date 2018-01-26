#include "repairticket.h"
#include "ui_repairticket.h"

RepairTicket::RepairTicket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RepairTicket)
{
    ui->setupUi(this);

    // Creating nextDay.
    QDate nextDay = nextDay.currentDate().addDays(1);
    QDate currentDate = currentDate.currentDate();

    // Defaulting date to next system date.
    ui->tktDateText->setDate(nextDay);
    //ui->radioLastCont->setDate(currentDate);

}

RepairTicket::~RepairTicket()
{
    delete ui;
}







/**
 * When generate ticket is clicked - generate ticket.
 */
void RepairTicket::on_pushButton_clicked()
{

    // Clear any data that is already in the ticket field.
    ui->ticketTemplate->clear();

    // Getting our data from the user.
    QString //tktName         = ui->tktName->currentText(),     // Removed per Joey for build 2.0
            tktType         = ui->tktType->currentText(),
            tktZone         = ui->tktZone->currentText(),
            //tktTime         = ui->tktTime->currentText(),     // Removed per Joey for build 2.0
            tktTower        = ui->tktTower->currentText(),
            //tktQ90          = ui->tktQ90->currentText(),      // Removed per Joey for build 2.0
            //tktQConfirm     = ui->tktQConfirm->currentText(), // Removed per Joey for build 2.0
            //tktQAbsent      = ui->tktQAbsent->currentText(),  // Removed per Joey for build 2.0
            //tktQTrip        = ui->tktQTrip->currentText(),    // Removed per Joey for build 2.0
            tktNotes        = ui->tktNotes->toPlainText(),    // Removed per Joey for build 2.0
            //tktPrevJob,                                       // Removed per Joey for build 2.0
            //tktPrevTech,                                      // Removed per Joey for build 2.0
            cstName         = ui->cstName->text(),
            cstID           = ui->cstID->text(),                // Removed per Joey for build 2.0
            cstAddress      = ui->cstAddress->text(),           // Removed per Joey for build 2.0
            cstCty          = ui->cstCty->text(),             // Removed per Joey for build 2.0
            cstZip          = ui->cstZip->text(),
            cstPhone        = ui->cstPhone->text(),           // Removed per Joey for build 2.0
            cstPhoneAlt     = ui->cstPhoneAlt->text(),        // Removed per Joey for build 2.0
            cstPackage      = ui->cstPackage->currentText(),  // Removed per Joey for build 2.0
            cstTest         = ui->cstTest->text(),              // Removed per Joey for build 2.0
            cstTorch        = ui->cstTorch->text(),             // Removed per Joey for build 2.0
            cstUser         = ui->cstUser->text(),            // Removed per Joey for build 2.0
            cstPass         = ui->cstPass->text(),            // Removed per Joey for build 2.0
            radioManaged    = ui->radioIP->text(),
            radioPublic     = ui->radioPublic->text(),
            radioMAC        = ui->radioMAC->text(),
            radioType       = ui->radioType->currentText(),
            radioTypeType   = ui->radioTypeType->currentText(),
            //radioFreq       = ui->radioFreq->text(),          // Removed per Joey for build 2.0
            radioSSID       = ui->radioSSID->text(),
            radioCCQ        = ui->radioCCQ->text(),
            radioQuaCap     = ui->radioQuaCap->text(),
            radioSignal     = ui->radioSignal->text(),
            //radioFirmVer    = ui->radioFirmVer->text(),       // Removed per Joey for build 2.0
            radioLastSignal = ui->radioLastSignal->text(),
            //radioDist       = ui->radioDist->text(),          // Removed per Joey for build 2.0
            radioAPCount    = ui->radioQAPCount->text(),
            radioTest       = ui->radioTest->text();
            //other_trip      = ui->other_tripFeeText->text(),  // Removed per Joey for build 2.0
            //other_absent    = ui->other_absentFeeText->text(),    // Removed per Joey for build 2.0
            //other_confirm   = ui->other_confirmationText->text(); // Removed per Joey for build 2.0

    // Time stamp for the person creating the ticket.
    QString date, time;
    QDate   currentDate;
    QTime   currentTime;

    currentDate = currentDate.currentDate();
    currentTime = currentTime.currentTime();

    date = currentDate.toString();
    time = currentTime.toString();

    //timestamp = "[" + tktName + "::" + date + "::" + time + "]"; // Removed per Joey for build 2.0


    // Getting previous ticket information.
    /*if(ui->R90->isChecked())
    {
        tktPrevJob = ui->tktPrevJob->toPlainText();
        tktPrevTech = ui->tktPrevTech->text();
    }
    else if(ui->I90->isChecked())                       // Removed per Joey for build 2.0
    {
        tktPrevJob = "NA";
        tktPrevTech = ui->tktPrevTech->text();
    }*/


    /** Checkboxes to string and RadioButtons to string.*/
    /*QString radioAPup, radioAPSat, tktDisclosure;
    if(ui->radioQUp->isChecked())
        radioAPup = "Yes";
    else
        radioAPup = "No";

    if(ui->radioQAPSat->isChecked())
        radioAPSat = "Yes";                             // Removed per Joey for build 2.0
    else
        radioAPSat = "NA";

    if(ui->tktQDisclose->isChecked())
        tktDisclosure = "Yes";
    else
        tktDisclosure = "No";*/

    /*QString tktPole;
    if(ui->tktPole_Yes->isChecked())
        tktPole = "Yes";
    else
        tktPole = "No";*/

    // Dates to string.
    QDate tktDate = ui->tktDateText->date();
    QString tktDateText = tktDate.toString("M/d/yyyy");

    /*QDate radioLastContactDate = ui->radioLastCont->date();
    QString radioLastContact = radioLastContactDate.toString("M/d/yyyy");*/


    // Storing user data into each line that needs to be generated.
    //QString timeStampStart = timestamp + "\n\n";

    checkNA(tktType);
    QString line1 = "Fix Ticket Type: " + tktType;

    checkNA(tktZone);
    checkNA(tktDateText);
    //checkNA(tktTime);     // Removed per Joey for build 2.0
    checkNA(tktTower);
    checkNA(cstName);

    // Checking if there needs to be an I90 or R90 from above.
    // Removed tktTime from summary per Joey for build 2.0
    QString line2;
    line2 = "Zone " + tktZone + " - " + tktDateText + " - " + tktTower + " Fix - " + cstName + "\n";

    /*if(!ui->tkt_Group_90days->isEnabled())
    {
        line2 = "Zone " + tktZone + " - " + tktDateText + " - " + tktTower + " Fix - " + cstName + "\n";
    }
    else if(ui->R90->isChecked())
    {
        line2 = "R90 - Zone " + tktZone + " - " + tktDateText + " - " + tktTower + " Fix - " + cstName + "\n";      // Removed per Joey for build 2.0
    }
    else if(ui->I90->isChecked())
    {
        line2 = "I90 - Zone " + tktZone + " - " + tktDateText + " - " + tktTower + " Fix - " + cstName + "\n";
    }
    else if(ui->tkt_Group_90days->isEnabled())
    {
        line2 = "Zone " + tktZone + " - " + tktDateText + " - " + tktTower + " Fix - " + cstName + "\n";
    }*/

    //checkNA(cstName);
    checkNA(cstID);                                                   // Removed per Joey for build 2.0
    QString line3 = cstName + " " + cstID + "\n";

    checkNA(cstAddress);
    QString line4 = cstAddress;

    checkNA(cstCty);
    checkNA(cstZip);
    QString line5 = cstCty + ", TX " + cstZip;

    checkNA(cstPhone);
    QString line6 = cstPhone;

    checkNA(cstPhoneAlt);
    QString line7 = cstPhoneAlt;

    checkNA(cstPackage);
    QString line8 = cstPackage + "\n";

    checkNA(radioManaged);
    QString line9 = "Manage IP: " + radioManaged;

    checkNA(radioPublic);
    QString line10 = "Public IP: " + radioPublic;

    checkNA(radioMAC);
    QString line11 = "MAC of Radio: " + radioMAC;

    checkNA(radioType);
    QString line12 = "Radio Type: " + radioType + " " + radioTypeType;

    /*checkNA(radioFreq);
    QString line13 = "Radio Frequency: " + radioFreq;*/                             // Removed per Joey for build 2.0

    checkNA(radioSSID);
    QString line14 = "SSID: " + radioSSID;

    checkNA(radioCCQ);
    QString line15 = "CCQ: " + radioCCQ;

    checkNA(radioQuaCap);
    QString line16 = "Qual/Cap: " + radioQuaCap;

    checkNA(radioSignal);
    QString line17 = "Radio Signal: " + radioSignal;

    /*checkNA(radioFirmVer);
    QString line18 = "Firmware Version: " + radioFirmVer;*/                         // Removed per Joey for build 2.0

    checkNA(radioLastSignal);
    QString line19 = "Last Known Good Signal: " + radioLastSignal;

    /*checkNA(radioDist);
    QString line20 = "Distance to Tower: " + radioDist;*/                           // Removed per Joey for build 2.0

    /*checkNA(radioLastContact);
    QString line21 = "Last Contact: " + radioLastContact;*/

    //QString line22 = "Is the AP up: " + radioAPup;                                // Removed per Joey for build 2.0

    checkNA(radioAPCount);
    QString line23 = "AP CST Count: " + radioAPCount;

    //QString line24 = "Saturated? " + radioAPSat;                                  // Removed per Joey for build 2.0

    checkNA(cstTorch);
    QString line25 = "Torch Results: " + cstTorch;

    checkNA(radioTest);
    QString line26 = "Radio Speed Test Results: " + radioTest;

    checkNA(cstTest);
    QString line27 = "CST Speed Test Results: " + cstTest + "\n";

    checkNA(cstUser);
    QString line28 = "Login Username: " + cstUser;                                                      // Removed per Joey for build 2.0

    checkNA(cstPass);
    QString line29 = "Login Password: " + cstPass + "\n";                                             // Removed per Joey for build 2.0

    //QString line30 = "Is the equipment on site attached to a tower that is over 30ft tall? " + tktPole + "\n";

    //QString line31 = "Tickets in the last 90 days? " + tktQ90;                                        // Removed per Joey for build 2.0

    //QString line32 = "Animal/Pet Disclosure Read? " + tktDisclosure + "\n";                           // Removed per Joey for build 2.0

    /*checkNA(tktPrevJob);
    QString line33 = "What was done at location? " + tktPrevJob;                                        // Removed per Joey for build 2.0

    checkNA(tktPrevTech);
    QString line34 = "Technician that completed last ticket: " + tktPrevTech + "\n";*/

    //QString line35 = "Confirmation call explained? " + tktQConfirm + " " + other_confirm;

    //QString line36 = "$25 Absent fee explained? " + tktQAbsent + " " + other_absent;

    //QString line37 = "$65 Trip fee explained? " + tktQTrip + " " + other_trip + "\n";

    QString line38 = "Notes: " + tktNotes;                                                            // Removed per Joey for build 2.0

    //QString timeStampEnd = timestamp + "\n\n";



    // Checking for important fields and sending an error message if they are not filled out.
    /** FIELDS THAT MUST BE FILLED OUT:  */
    bool error = false;
    error = checkImportantInfo();


    // Here we generate the ticket.
    if(error == false)
    {
        //ui->ticketTemplate->append(timeStampStart);
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
        //ui->ticketTemplate->append(line13);               // Removed per Joey for build 2.0
        ui->ticketTemplate->append(line14);
        ui->ticketTemplate->append(line15);
        ui->ticketTemplate->append(line16);
        ui->ticketTemplate->append(line17);
        //ui->ticketTemplate->append(line18);               // Removed per Joey for build 2.0
        ui->ticketTemplate->append(line19);
        //ui->ticketTemplate->append(line20);               // Removed per Joey for build 2.0
        //ui->ticketTemplate->append(line21);
        //ui->ticketTemplate->append(line22);               // Removed per Joey for build 2.0
        ui->ticketTemplate->append(line23);
        //ui->ticketTemplate->append(line24);               // Removed per Joey for build 2.0
        ui->ticketTemplate->append(line25);
        ui->ticketTemplate->append(line26);
        ui->ticketTemplate->append(line27);
        //ui->ticketTemplate->append(line28);               // Removed per Joey for build 2.0
        //ui->ticketTemplate->append(line29);               // Removed per Joey for build 2.0
        //ui->ticketTemplate->append(line30);
        //ui->ticketTemplate->append(line31);               // Removed per Joey for build 2.0
        //ui->ticketTemplate->append(line32);               // Removed per Joey for build 2.0

        //ui->ticketTemplate->append(line33);
        //ui->ticketTemplate->append(line34);

        //ui->ticketTemplate->append(line35);               // Removed per Joey for build 2.0
        //ui->ticketTemplate->append(line36);               // Removed per Joey for build 2.0
        //ui->ticketTemplate->append(line37);               // Removed per Joey for build 2.0
        ui->ticketTemplate->append(line38);
        completeTicket();
        //ui->ticketTemplate->append(timeStampEnd);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }
}







void RepairTicket::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}








/**
 * Checking if text for ticket generation should be changed to "NA".
 * @param string
 */
void RepairTicket::checkNA(QString &string)
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
bool RepairTicket::checkImportantInfo()
{
    // Check all important informtion that needs to be filled out.
    // If something is not filled out, the error message will appear
    // where the ticket normally would.
    QDate currentDate = currentDate.currentDate();


    if(ui->tktType->currentText() == "")
    {
        // Change color of tktType to red.


        ui->ticketTemplate->append("\"Fix Ticket Type:\" Needs to be selected.");
        return true;
    }
    //else


    if(ui->tktZone->currentText() == "")
    {
        ui->ticketTemplate->append("\"Zone:\" Needs to be selected.");
        return true;
    }

    if(ui->tktDateText->date() < currentDate)
    {
        ui->ticketTemplate->append("You cannot schedule the ticket before today's date.");
    }

    /*else if(ui->tktTime->currentText() == "")
    {
        ui->ticketTemplate->append("\"Time Block Assigned:\" Needs to be selected.");               // Removed per Joey for build 2.0
        return true;
    }*/
    /*else if(!ui->tktPole_Yes->isChecked() && !ui->tktPole_No->isChecked())
    {
        ui->ticketTemplate->append("\"Pole over 30ft tall?\" Needs to be selected.");
        return true;
    }*/
    /*else if(ui->tktQ90->currentText() != "0" && !ui->I90->isChecked() && !ui->R90->isChecked())
    {
        ui->ticketTemplate->append("\"I90\" or \"R90\" needs to be selected.");                     // Removed per Joey for build 2.0
        return true;
    }
    else if(ui->I90->isChecked() && ui->tktPrevTech->text() == "")
    {
        ui->ticketTemplate->append("\"Technician's Name:\" Needs to be filled out.");
        return ;
    }
    else if(ui->R90->isChecked())
    {
        if(ui->tktPrevJob->toPlainText() == "")
        {true
            ui->ticketTemplate->append("\"What was done at previous location?\" Needs to be filled out.");
            return true;
        }
        else if(ui->tktPrevTech->text() == "")
        {
            ui->ticketTemplate->append("\"Technician's Name:\" Needs to be filled out.");
            return true;
        }
    }*/
    /*else if(ui->tktQConfirm->currentText() == "")
    {
        if(ui->other_confirmation->isChecked() && ui->other_confirmationText->text() == "")
        {
            ui->ticketTemplate->append("\"Other\" for confirmation call was selected, but not filled out.");
            return true;
        }
        else
        {
            ui->ticketTemplate->append("\"Confirmation call was explained?\" Needs to be selected.");
            return true;
        }
    }*/
    else if(!ui->tktQConfirm->isChecked())
    {
        ui->ticketTemplate->append("\"Confirmation call was explained\" Needs to be checked. Make sure you explain the confirmation call process.");
        return true;
    }
    /*else if(ui->tktQAbsent->currentText() == "")
    {
        if(ui->other_absentFee->isChecked() && ui->other_absentFeeText->text() == "")
        {
            ui->ticketTemplate->append("\"Other\" for absent fee was selected, but not filled out.");
            return true;
        }
        else
        {
            ui->ticketTemplate->append("\"$25 absent fee explained?\" Needs to be selected.");
            return true;
        }
    }*/
    else if(!ui->tktQAbsent->isChecked())
    {
        ui->ticketTemplate->append("\"$25 absent fee explained\" Needs to be checked. Make sure you explain the possible absent fee.");
    }
    /*else if(ui->tktQTrip->currentText() == "")
    {
        if(ui->other_tripFee->isChecked() && ui->other_tripFeeText->text() == "")
        {
            ui->ticketTemplate->append("\"Other\" for trip fee was selected, but not filled out.");
            return true;
        }
        else
        {
            ui->ticketTemplate->append("\"$65 trip fee explained?\" Needs to be selected.");
            return true;
        }
    }*/
    else if(!ui->tktQTrip->isChecked())
    {
        ui->ticketTemplate->append("\"$65 trip fee explained\" Needs to be checked. Make sure you explain the possible trip fee.");
    }
    else if(!ui->tktQDisclose->isChecked())
    {
        ui->ticketTemplate->append("\"Disclosure Read.\" Needs to be checked. Make sure you read the disclosure to the customer.");
        return true;
    }
    else if(ui->cstID->text() == "")
    {
        ui->ticketTemplate->append("Customer ID is needed.");
        return true;
    }
    else if(!ui->cstID->text().data()->isDigit())
    {
        ui->ticketTemplate->append("The customer ID must contain numbers, not characters.");
        return true;
    }
    else if(ui->cstName->text() == "") /** Customer Section... **/                         // Removed per Joey for build 2.0
    {
        ui->ticketTemplate->append("Customer's name is needed.");
        return true;
    }
    else if(ui->cstAddress->text() == "")
    {
        ui->ticketTemplate->append("Customer's address is needed.");
        return true;
    }
    else if(ui->cstCty->text() == "")
    {
        ui->ticketTemplate->append("The city for the address is needed.");
        return true;
    }
    else if(ui->cstZip->text() == "")
    {
        ui->ticketTemplate->append("The zip for the city is needed.");
        return true;
    }
    else if(ui->cstPhone->text() == "")
    {
        ui->ticketTemplate->append("A phone number will be needed to contact the customer.");
        return true;
    }
    else if(!ui->cstPhone->text().data()->isDigit())
    {
        ui->ticketTemplate->append("The phone number entered does not contain numerical values.");
        return true;
    }
    else if(ui->cstCheckPhoneAlt->isChecked() && ui->cstPhoneAlt->text() == "")
    {
        ui->ticketTemplate->append("An alternate phone number was selected, but not filled out.");
        return true;
    }
    else if(!ui->cstPhoneAlt->text().data()->isDigit() && ui->cstPhoneAlt->text() != "")
    {
        ui->ticketTemplate->append("The alternative phone number entered does not contain numerical values.");
        return true;
    }
    else if(!ui->cstPackRes->isChecked() && !ui->cstPackBus->isChecked() && !ui->cstPackOth->isChecked())
    {
        ui->ticketTemplate->append("A package must be chosen.");
        return true;
    }
    else if(ui->cstUser->text() == "")
    {
        ui->ticketTemplate->append("Authentication username is needed.");
        return true;
    }
    else if(ui->cstPass->text() == "")
    {
        ui->ticketTemplate->append("Authentication password is needed.");
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
        ui->ticketTemplate->append("Radio's Firmware version needs to be checked. Make sure the radio has the correct firmware.");
        return true;
    }
    else if(ui->radioType->currentText() == "")
    {
        ui->ticketTemplate->append("Radio Type needs to be selected.");
        return true;
    }
    /*else if(ui->radioFreq->text() == "" && ui->tktType->currentText() != "Radio down")
    {
        ui->ticketTemplate->append("Radio's Frequency needs to be filled out.");                        // Removed per Joey for build 2.0
        return true;
    }*/
    else if(ui->radioSSID->text() == "")
    {
        ui->ticketTemplate->append("Radio's SSID needs to be filled out.");
        return true;
    }
    /*else if(!ui->radioQUp->isChecked())
    {
        ui->ticketTemplate->append("\"Is the AP up?\" Needs to be checked.");                           // Removed per Joey for build 2.0
        return true;
    }*/
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
    /*else if(ui->radioDist->text() == "")
    {
        ui->ticketTemplate->append("Radio's Distance to Tower is needed. If it is not documented, or cannot be found, put NA.");                // Removed per Joey for build 2.0
        return true;
    }*/
    /*else if(ui->radioLastCont->date() > currentDate)
    {
        ui->ticketTemplate->append("Last Known Contact Date cannot be after today's date.");
    }*/
    else if(ui->radioTest->text() == "" && ui->tktType->currentText() != "Radio down")
    {
        ui->ticketTemplate->append("Radio's Speed Test is needed. If it cannot be done put NA.");
        return true;
    }
    else
        return false;
}







/**
 * Whatever zone is selected, add list to the tower drop down selection.
 * @param string
 */
void RepairTicket::on_tktZone_currentTextChanged(const QString &string)
{

    // Clearing the tower drop downs if the zone combo box is updated.
    ui->tktTower->clear();

    // Set the drop down for the tower combo box.
    if(string == "1")
    {
        ui->tktTower->addItems(zone1);
    }
    else if(string == "2")
    {
        ui->tktTower->addItems(zone2);
    }
    else if(string == "3")
    {
        ui->tktTower->addItems(zone3);
    }
    else if(string == "4")
    {
        ui->tktTower->addItems(zone4);
    }
    else if(string == "5")
    {
        ui->tktTower->addItems(zone5);
    }
    else if(string == "6")
    {
        ui->tktTower->addItems(zone6);
    }
    else if(string == "7")
    {
        ui->tktTower->addItems(zone7);
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







/**
 * When checkbox is checked, it enables the alternative cell to
 * be entered.
 * @param string
 */
void RepairTicket::on_cstCheckPhoneAlt_stateChanged(int state)              // Removed per Joey for build 2.0
{
    if(state != 0) ui->cstPhoneAlt->setEnabled(true);
    else
    {
        ui->cstPhoneAlt->clear();
        ui->cstPhoneAlt->setDisabled(true);
    }
}







/**
 * BEGIN: The following three functions are for the package group.
 *
/**
 * When checked - set the list for the Package drop down.
 */
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
void RepairTicket::on_radioType_currentTextChanged(const QString &string)
{
    // Clearing list.
    ui->radioTypeType->clear();

    // Enabling list.
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
 * This generates the last part of the ticket.
 */
void RepairTicket::completeTicket()
{
    ui->ticketTemplate->append("========================================");
    ui->ticketTemplate->append("INTERNET FIX: UPDATE");
    ui->ticketTemplate->append("------------------------");
    ui->ticketTemplate->append("Initial reason for going to fix (Mandatory): ");
    ui->ticketTemplate->append("What was done at location(Mandatory): ");

    ui->ticketTemplate->append("Radio Frequency: ");
    ui->ticketTemplate->append("Type of Dish: ");
    ui->ticketTemplate->append("Type of Radio: ");
    ui->ticketTemplate->append("Radio Mac: ");
    ui->ticketTemplate->append("Manage IP: ");
    ui->ticketTemplate->append("Signal Lvl: ");
    ui->ticketTemplate->append("Current AP: ");
    ui->ticketTemplate->append("Mount Type: ");
    ui->ticketTemplate->append("Pole Size: ");
    ui->ticketTemplate->append("Guy Wire: ");
    ui->ticketTemplate->append("Ground Stakes? ");
    ui->ticketTemplate->append("Cable Type:");
    ui->ticketTemplate->append("========================================\n");
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
void RepairTicket::on_tktType_currentTextChanged(const QString &string)
{
    if(string == "Radio down") // IF "Radio Down" is selected.
    {
        // Radio Down disables
        ui->cstTest->setDisabled(true);
        ui->cstTorch->setDisabled(true);
        ui->radioTest->setDisabled(true);
        /*// Disable radio frequency input.
        ui->radioFreq->setDisabled(true);*/                         // Removed per Joey for build 2.0
        ui->radioCCQ->setDisabled(true);
        ui->radioQuaCap->setDisabled(true);
        ui->radioSignal->setDisabled(true);
        ui->radioFirmware->setDisabled(true);                      // Removed per Joey for build 2.0
        ui->radioQAPCount->setDisabled(true);
        /*// Disable AP Saturated
        ui->radioQAPSat->setDisabled(true);*/                       // Removed per Joey for build 2.0
    }
    else if(string == "No connection")
    {
        // No connection disables
        ui->cstTest->setDisabled(true);

        // Enable if going from radio down to no connection.
        ui->cstTorch->setEnabled(true);
        //ui->radioFreq->setEnabled(true);                          // Removed per Joey for build 2.0
        ui->radioSSID->setEnabled(true);
        ui->radioCCQ->setEnabled(true);
        ui->radioQuaCap->setEnabled(true);
        ui->radioSignal->setEnabled(true);
        ui->radioTest->setEnabled(true);
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
        ui->radioFirmware->setEnabled(true);                       // Removed per Joey for build 2.0
        ui->radioLastSignal->setEnabled(true);
        ui->radioQAPCount->setEnabled(true);
        //ui->radioQAPSat->setEnabled(true);                        // Removed per Joey for build 2.0
    }
}
