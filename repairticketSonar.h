#ifndef repairticketSonar_H
#define repairticketSonar_H

#include <QMainWindow>
#include <towers.h>
#include <radios.h>

namespace Ui {
class RepairTicketSonar;
}

class RepairTicketSonar : public QMainWindow, public Towers, public Radios
{
    Q_OBJECT

public:
    explicit RepairTicketSonar(QWidget *parent = 0);
    ~RepairTicketSonar();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkNA(QString &string);

    void on_tktZone_currentTextChanged(const QString &string);

    void on_radioType_currentTextChanged(const QString &arg1);

    bool checkImportantInfo();

    void on_tktType_currentTextChanged(const QString &arg1);

    void on_tktTower_currentTextChanged(const QString &string);

    void on_Clear_clicked();

    void on_cstPackRes_clicked();

    void on_cstPackBus_clicked();

    void on_cstPackOth_clicked();

    void resetColor();

private:
    Ui::RepairTicketSonar *ui;
};

#endif // REPAIRTICKET_H
