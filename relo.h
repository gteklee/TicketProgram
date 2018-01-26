#ifndef RELO_H
#define RELO_H

#include <QMainWindow>
#include <towers.h>

namespace Ui {
class Relo;
}

class Relo : public QMainWindow, public Towers
{
    Q_OBJECT

public:
    explicit Relo(QWidget *parent = 0);
    ~Relo();

private slots:

    void on_pushButton_clicked();

    void on_Copy_clicked();

    void checkNA(QString &string);

    bool checkImportantInfo();

    void resetColor();

    void on_Clear_clicked();

private:
    Ui::Relo *ui;
};

#endif // RELO_H
