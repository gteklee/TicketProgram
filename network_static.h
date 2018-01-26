#ifndef NETWORK_STATIC_H
#define NETWORK_STATIC_H

#include <QMainWindow>

namespace Ui {
class Network_Static;
}

class Network_Static : public QMainWindow
{
    Q_OBJECT

public:
    explicit Network_Static(QWidget *parent = 0);
    ~Network_Static();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void on_Clear_clicked();

    void checkBlank(QString &string);

    bool checkImportantInfo();

    void resetColor();

private:
    Ui::Network_Static *ui;
};

#endif // NETWORK_STATIC_H
