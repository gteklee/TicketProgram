#ifndef ONSITE_H
#define ONSITE_H

#include <QMainWindow>
#include <towers.h>
#include <radios.h>

namespace Ui {
class Onsite;
}

class Onsite : public QMainWindow, public Towers, public Radios
{
    Q_OBJECT

public:
    explicit Onsite(QWidget *parent = 0);
    ~Onsite();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkDisabled();

    void checkBlank(QString &string);

    bool checkImportantInfo();

    void on_radioType_currentTextChanged(const QString &string);

    void on_cstInternet_clicked();

    void on_tktZone_currentTextChanged(const QString &string);

    void on_Clear_clicked();

    void on_tktTower_currentTextChanged(const QString &arg1);

    void on_cstPackRes_clicked();

    void on_cstPackBus_clicked();

    void on_cstPackOth_clicked();

    void resetColor();

private:
    Ui::Onsite *ui;
};

#endif // ONSITE_H
