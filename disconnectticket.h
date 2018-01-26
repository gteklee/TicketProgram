#ifndef DISCONNECTTICKET_H
#define DISCONNECTTICKET_H

#include <QMainWindow>

namespace Ui
{
    class DisconnectTicket;
}

class DisconnectTicket : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisconnectTicket(QWidget *parent = 0);
    ~DisconnectTicket();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkNA(QString &string);

    void completeTicket();

private:
    Ui::DisconnectTicket *ui;

};

#endif // DISCONNECTTICKET_H
