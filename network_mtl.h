#ifndef NETWORK_MTL_H
#define NETWORK_MTL_H

#include <QMainWindow>

namespace Ui {
class Network_MTL;
}

class Network_MTL : public QMainWindow
{
    Q_OBJECT

public:
    explicit Network_MTL(QWidget *parent = 0);
    ~Network_MTL();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void on_Clear_clicked();

    void checkBlank(QString &string);

    bool checkImportantInfo();

    void resetColor();

    void on_cstCurrent_clicked();

    void on_cstNew_clicked();

private:
    Ui::Network_MTL *ui;
};

#endif // NETWORK_VOIP_H
