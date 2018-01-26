#ifndef CONFIRMATIONEXIT_H
#define CONFIRMATIONEXIT_H

#include <QDialog>

namespace Ui {
class ConfirmationExit;
}

class ConfirmationExit : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationExit(QWidget *parent = 0);
    ~ConfirmationExit();

private slots:
    void on_exitButton_clicked();

private:
    Ui::ConfirmationExit *ui;
};

#endif // CONFIRMATIONEXIT_H
