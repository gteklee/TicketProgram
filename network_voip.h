#ifndef NETWORK_VOIP_H
#define NETWORK_VOIP_H

#include <QMainWindow>

namespace Ui {
class Network_Voip;
}

class Network_Voip : public QMainWindow
{
    Q_OBJECT

public:
    explicit Network_Voip(QWidget *parent = 0);
    ~Network_Voip();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void on_Clear_clicked();

    void checkBlank(QString &string);

    bool checkImportantInfo();

    void resetColor();

    void on_other_line1_clicked();

    void on_ported_assignment_clicked();

    void on_cstCurrent_clicked();

    void on_cstNew_clicked();

private:
    Ui::Network_Voip *ui;
};

#endif // NETWORK_VOIP_H
