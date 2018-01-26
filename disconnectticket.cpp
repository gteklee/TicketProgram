#include "disconnectticket.h"
#include "ui_disconnectticket.h"

DisconnectTicket::DisconnectTicket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisconnectTicket)
{
    ui->setupUi(this);

    // Setting the Calendar dates.
    QDate nextDay = nextDay.currentDate().addDays(1);
    QDate currentDate = currentDate.currentDate();

    ui->tktDateText->setDate(nextDay);
}

DisconnectTicket::~DisconnectTicket()
{
    delete ui;
}







/**
 * When "Generate Ticket" is clicked() - generate ticket.
 */
void DisconnectTicket::on_pushButton_clicked()
{
    // Clear any data that is already in the ticket field.
    ui->ticketTemplate->clear();

    // Input.
    QString cstName     = ui->cstName->text(),
            cstCity     = ui->cstCty->text(),
            tktZone     = ui->tktZone->currentText(),
            tktContract = ui->tktContract->text(),
            tktStatus   = ui->tktStatus->text(),
            tktSupply   = ui->tktSupply->text(),
            tktRouter   = ui->tktRouter->text(),
            tktNotes    = ui->tktNotes->toPlainText();

    // Ticket date information.
    QDate tktDate = ui->tktDateText->date();
    QString tktDateText = tktDate.toString("M/d/yyyy");

    // Check if lines are blank.
    checkNA(cstName);
    checkNA(cstCity);
    checkNA(tktZone);
    checkNA(tktContract);
    checkNA(tktStatus);
    checkNA(tktSupply);
    checkNA(tktRouter);
    checkNA(tktNotes);
    checkNA(tktDateText);

    // Create ticket lines.
    QString line1 = "Zone " + tktZone + " - " + cstCity + " Disconnect - " + cstName + "\n";

    QString line2 = "Contract Information: " + tktContract;
    QString line3 = "Account Status: " + tktStatus;
    QString line4 = "Date Radio Deactivated: " + tktDateText;
    QString line5 = "Power Supply: " + tktSupply;
    QString line6 = "Managed Router: " + tktRouter + "\n";

    QString line7 = "Notes: " + tktNotes;

    // Generate the ticket.
    ui->ticketTemplate->append(line1);
    ui->ticketTemplate->append(line2);
    ui->ticketTemplate->append(line3);
    ui->ticketTemplate->append(line4);
    ui->ticketTemplate->append(line5);
    ui->ticketTemplate->append(line6);
    ui->ticketTemplate->append(line7);
    completeTicket();

    // Enable, Disable copy to clipboard button.
    if(ui->ticketTemplate->toPlainText() != "")
        ui->Copy->setEnabled(true);
    else
        ui->Copy->setDisabled(true);
}

/**
 * Check for empty fields.
 */
void DisconnectTicket::checkNA(QString &string)
{
    if(string == "")
        string = "--";
    else if(string == "Enter any helpful information that may be important, here.")
        string = "--";
}

/**
 * Complete the ticket.
 */
void DisconnectTicket::completeTicket()
{
    ui->ticketTemplate->append("====================================");
    ui->ticketTemplate->append("Tech Notes:");
    ui->ticketTemplate->append("------------------------------------");
    ui->ticketTemplate->append("PSU: ");
    ui->ticketTemplate->append("Mount: ");
    ui->ticketTemplate->append("Pole: ");
    ui->ticketTemplate->append("Dish: ");
    ui->ticketTemplate->append("Radio: ");
    ui->ticketTemplate->append("Radio MAC: ");
    ui->ticketTemplate->append("Cable: \n");
    ui->ticketTemplate->append("Notes: ");
    ui->ticketTemplate->append("====================================");
}

/**
 * Copy to Clipboard.
 */
void DisconnectTicket::on_Copy_clicked()
{
    ui->ticketTemplate->selectAll();
    ui->ticketTemplate->copy();
}
