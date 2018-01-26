#ifndef network_other_H
#define network_other_H

#include <QMainWindow>
#include <towers.h>
#include <radios.h>

namespace Ui {
class Network_Other;
}

class Network_Other : public QMainWindow, public Towers, public Radios
{
    Q_OBJECT

public:
    explicit Network_Other(QWidget *parent = 0);
    ~Network_Other();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkNA(QString &string);

    void on_radioType_currentTextChanged(const QString &arg1);

    bool checkImportantInfo();

    void on_Clear_clicked();

    void on_cstPackRes_clicked();

    void on_cstPackBus_clicked();

    void on_cstPackOth_clicked();

    void resetColor();

private:
    Ui::Network_Other *ui;
};

#endif // REPAIRTICKET_H
