#ifndef INSTALL_H
#define INSTALL_H

#include <QMainWindow>
#include <towers.h>

namespace Ui {
class Install;
}

class Install : public QMainWindow, public Towers
{
    Q_OBJECT

public:
    explicit Install(QWidget *parent = 0);
    ~Install();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkNA(QString &string);

    void on_tktZone_currentTextChanged(const QString &string);

    void on_cstPackRes_clicked();

    void on_cstPackOth_clicked();

    void on_cstPackBus_clicked();

    bool checkImportantInfo();

    void on_tkt_other_clicked();

    void on_tkt_am_clicked();

    void on_tkt_pm_clicked();

    void resetColor();

    void on_tktTower_currentTextChanged(const QString &arg1);

    void on_Clear_clicked();

private:
    Ui::Install *ui;
};

#endif // INSTALL_H
