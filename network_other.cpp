#include "network_other.h"
#include "ui_network_other.h"

Network_Other::Network_Other(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Network_Other)
{
    ui->setupUi(this);
}

Network_Other::~Network_Other()
{
    delete ui;
}





/**
 * When generate ticket is clicked - generate ticket.
 */
void Network_Other::on_pushButton_clicked()
{

    // Clear any data that is already in the ticket field.
    ui->ticketTemplate->clear();


    // Getting our data from the user.
    QString cstEscalation   = ui->cstEscalation->toPlainText(),
            tktNotes        = ui->tktNotes->toPlainText(),
            radioType       = ui->radioType->currentText(),
            radioTypeType   = ui->radioTypeType->currentText(),
            radioManaged    = ui->radioIP->text(),
            radioPublic     = ui->radioPublic->text(),
            routerMAC       = ui->routerMAC->text(),
            radioSSID       = ui->radioSSID->text(),
            routerMicrotik  = ui->routerMicrotik->text(),
            radioSignal     = ui->radioSignal->text(),
            radioHorVer     = ui->radioHorVert->text(),
            radioLAN        = ui->radioLAN->text(),
            radioMacWinbox  = ui->radioMACWin->text(),
            cstName         = ui->cstName->text(),
            cstTorch        = ui->cstTorch->text(),
            cstPackage      = ui->cstPackage->currentText(),
            cstPing         = ui->cstPing->text(),
            cstQueue        = ui->cstQueue->text(),
            radioMAC        = ui->radioMAC->text(),
            radioCCQ        = ui->radioCCQ->text(),
            radioQuaCap     = ui->radioQuaCap->text();



    checkNA(cstName);
    checkNA(cstPackage);
    checkNA(radioManaged);
    checkNA(radioPublic);
    checkNA(radioMAC);
    checkNA(radioType);
    checkNA(radioSSID);
    checkNA(radioCCQ);
    checkNA(radioQuaCap);
    checkNA(radioSignal);
    checkNA(cstTorch);
    checkNA(radioHorVer);

    QString line1 = "Other Assistance";
    QString name = cstName;

    QString line2 = "Reason For Escalation: " + cstEscalation + "\n";

    QString line3 = "Radio Type: " + radioType + " " + radioTypeType;
    QString line4 = "Current Managed IP: " + radioManaged;
    QString line5 = "Current Public IP: " + radioPublic;
    QString line6 = "Router MAC: " + routerMAC;
    QString line7 = "Connected AP: " + radioSSID;
    QString line8 = "Mikrotik Router: " + routerMicrotik;
    QString line9 = "Radio Signal: " + radioSignal;
    QString line10 = "Horizontal/Vertical: " + radioHorVer;
    QString line11 = "CCQ: " + radioCCQ;
    QString line12 = "Quality/Capacity: " + radioQuaCap;
    QString line13 = "LAN Connection: " + radioLAN;
    QString line14 = "Radio MAC Address: " + radioMAC;
    QString line15 = "Radio MAC in Winbox: " + radioMacWinbox;
    QString line16 = "Package/Speed: " + cstPackage;
    QString line17 = "Ping Stats: " + cstPing;
    QString line18 = "Queue: " + cstQueue;
    QString line19 = "Torch Results: " + cstTorch;
    QString line20 = "Notes: " + tktNotes;
    QString dash = "-------------------------------------------";


    // Checking for important fields and sending an error message if they are not filled out.
    /** FIELDS THAT MUST BE FILLED OUT:  */
    bool error = false;
    error = checkImportantInfo();


    // Here we generate the ticket.
    if(error == false)
    {
        resetColor();

        ui->ticketTemplate->append(line1);
        ui->ticketTemplate->append(name);
        ui->ticketTemplate->append(dash);
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
        ui->ticketTemplate->append(line16);
        ui->ticketTemplate->append(line17);
        ui->ticketTemplate->append(line18);
        ui->ticketTemplate->append(line19);
        ui->ticketTemplate->append(line20);

        if(ui->ticketTemplate->toPlainText() != "")
            ui->Copy->setEnabled(true);
        else
            ui->Copy->setDisabled(true);
    }
}





void Network_Other::on_Clear_clicked()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit *>())
        widget->clear();

    foreach(QTextEdit *widget, this->findChildren<QTextEdit *>())
        widget->clear();

    foreach(QComboBox *widget, this->findChildren<QComboBox *>())
        widget->setCurrentText("");

    foreach(QRadioButton *widget, this->findChildren<QRadioButton *>())
    {
        widget->setAutoExclusive(false);
        widget->setChecked(false);
        widget->setAutoExclusive(true);
    }

    resetColor();
}





void Network_Other::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}





/**
 * Checking if text for ticket generation should be changed to "NA".
 * @param string
 */
void Network_Other::checkNA(QString &string)
{
    if(string == "")
        string = "--";
}







/**
 * Checks all information that must at least have some type of data before
 * ticket is generated.
 */
bool Network_Other::checkImportantInfo()
{
    // Check all important informtion that needs to be filled out.
    // If something is not filled out, the error message will appear
    // where the ticket normally would.
    ui->ticketTemplate->setTextColor(QColor(255, 0, 0));

    if(ui->radioType->currentText() == "")
    {
        ui->ticketTemplate->append("Radio Type needs to be selected.");
        return true;
    }
    else if(ui->radioIP->text() == "")
    {
        ui->ticketTemplate->append("Radio's Managed IP needs to be filled out.");
        return true;
    }
    else if(ui->radioPublic->text() == "")
    {
        ui->ticketTemplate->append("Customer's Public IP needs to be filled out.");
        return true;
    }
    else if(ui->radioSignal->text() == "")
    {
        ui->ticketTemplate->append("Radio's Signal Strength needs to be filled out.");
        return true;
    }
    else if(ui->radioCCQ->text() == "")
    {
        ui->ticketTemplate->append("Radio's CCQ must be filled out.");
        return true;
    }
    else if(ui->radioQuaCap->text() == "")
    {
        ui->ticketTemplate->append("Radio's Quailty / Capacity needs to be filled out.");
        return true;
    }
    else if(ui->radioLAN->text() == "")
    {
        ui->ticketTemplate->append("Does the router show a 100Mbps Full-Duplex connection?");
        return true;
    }
    else if(ui->radioMAC->text() == "")
    {
        ui->ticketTemplate->append("Radio's MAC Address needs to be filled out.");
        return true;
    }
    else if(ui->radioMACWin->text() == "")
    {
        ui->ticketTemplate->append("Radio's MAC in Winbox needs to be filled out.");
        return true;
    }
    else if(ui->radioSSID->text() == "")
    {
        ui->ticketTemplate->append("Radio's SSID needs to be filled out.");
        return true;
    }
    else if(!ui->cstPackRes->isChecked() && !ui->cstPackBus->isChecked() && !ui->cstPackOth->isChecked())
    {
        ui->ticketTemplate->append("A package must be chosen.");
        return true;
    }
    else if(ui->routerMAC->text() == "")
    {
        ui->ticketTemplate->append("The router's MAC Address is needed.");
        return true;
    }
    else if(ui->routerMicrotik->text() == "")
    {
        ui->ticketTemplate->append("What Microtik Router is the customer connected to?");
        return true;
    }
    else if(ui->cstPing->text() == "")
    {
        ui->ticketTemplate->append("Make sure to ping the customer's radio and check for any loss.");
        return true;
    }
    else if(ui->cstEscalation->toPlainText() == "")
    {
        ui->ticketTemplate->append("A reason for the escalation is needed.");
        return true;
    }
    else
    {
        resetColor();
        return false;
    }
}







/*/**
 * When tktQ90 is set to a value other than 0, enable the group box that contains       // Removed per Joey for build 2.0
 * the selection for I90 or R90.
 * @param string
 *
void Network_Other::on_tktQ90_currentTextChanged(const QString &string)
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
void Network_Other::on_cstCheckPhoneAlt_stateChanged(int state)              // Removed per Joey for build 2.0
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
void Network_Other::on_cstPackRes_clicked()
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


void Network_Other::on_cstPackOth_clicked()
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

void Network_Other::on_cstPackBus_clicked()
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
void Network_Other::on_radioType_currentTextChanged(const QString &string)
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








/*/**
 * When I90 is selected only enable the tech's name box.
 *
void Network_Other::on_I90_clicked()
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
/*void Network_Other::on_R90_clicked()
{
    if(ui->R90->isChecked())
    {
        ui->tktPrevJob->setEnabled(true);
        ui->tktPrevTech->setEnabled(true);
    }
}*/






/**
 * BEGIN: The following three functions are for the package group.
 *
/**
 * When checked - set the list for the Package drop down.
 */
void Network_Other::on_cstPackRes_clicked()
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


void Network_Other::on_cstPackOth_clicked()
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

void Network_Other::on_cstPackBus_clicked()
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






void Network_Other::resetColor()
{
    ui->ticketTemplate->setTextColor(QColor(0, 0, 0));

    /*ui->tktType_label->setText("<font color = 'black'>" + ui->tktType_label->text() + "</font>");
    ui->tktZone_label->setText("<font color = 'black'>" + ui->tktZone_label->text() + "</font>");*/
}
