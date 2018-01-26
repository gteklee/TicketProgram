#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

    QPlainTextEdit* infoDialog_Job();

    QLineEdit* infoDialog_Tech();

public slots:
    void disableTextBox();

private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
