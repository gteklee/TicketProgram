#ifndef NETWORK_KEY_H
#define NETWORK_KEY_H

#include <QMainWindow>

namespace Ui {
class Network_Key;
}

class Network_Key : public QMainWindow
{
    Q_OBJECT

public:
    explicit Network_Key(QWidget *parent = 0);
    ~Network_Key();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void on_Clear_clicked();

    void checkBlank(QString &string);

    bool checkImportantInfo();

    void resetColor();

private:
    Ui::Network_Key *ui;
};

#endif // NETWORK_Key_H
