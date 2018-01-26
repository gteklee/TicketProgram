#ifndef REPAIRTICKET_H
#define REPAIRTICKET_H

#include <QMainWindow>
#include <towers.h>
#include <radios.h>

namespace Ui {
class RepairTicket;
}

class RepairTicket : public QMainWindow, public Towers, public Radios
{
    Q_OBJECT

public:
    explicit RepairTicket(QWidget *parent = 0);
    ~RepairTicket();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkNA(QString &string);

    void on_tktZone_currentTextChanged(const QString &string);

    //void on_tktQ90_currentTextChanged(const QString &arg1);

    void on_cstCheckPhoneAlt_stateChanged(int arg1);

    void on_cstPackRes_clicked();

    void on_cstPackOth_clicked();

    void on_cstPackBus_clicked();

    void on_radioType_currentTextChanged(const QString &arg1);

    void completeTicket();

    //void on_I90_clicked();

    //void on_R90_clicked();

    bool checkImportantInfo();

    void on_tktType_currentTextChanged(const QString &arg1);

    //void on_other_confirmation_clicked();

    //void on_other_absentFee_clicked();

    //void on_other_tripFee_clicked();

private:
    Ui::RepairTicket *ui;
};

#endif // REPAIRTICKET_H
