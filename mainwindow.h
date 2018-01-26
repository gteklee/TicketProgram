#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <install.h>
#include <relo.h>
#include <repairticket.h>
#include <repairticketSonar.h>
#include <disconnectticket.h>
#include <network_static.h>
#include <network_key.h>
#include <network_voip.h>
#include <network_mtl.h>
#include <network_other.h>
#include <onsite.h>
#include <changelog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_3_triggered();

    void on_ticketButton_clicked();

    void on_radioNetwork_clicked();

    void on_radioSonar_clicked();

    void on_radioRepair_clicked();

    void on_onsite_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::MainWindow *ui;

    Install *install;
    Relo *relo;
    RepairTicket *repairTicket;
    RepairTicketSonar *repairTicketSonar;
    DisconnectTicket *disconnectTicket;
    Network_Static *network_Static;
    Network_Key *network_Key;
    Network_Voip *network_Voip;
    Network_MTL *network_MTL;
    Network_Other *network_Other;
    Onsite *onsite;
    Changelog *changelog;
};

#endif // MAINWINDOW_H
