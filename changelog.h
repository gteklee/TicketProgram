#ifndef CHANGELOG_H
#define CHANGELOG_H

#include <QDialog>

namespace Ui {
class Changelog;
}

class Changelog : public QDialog
{
    Q_OBJECT

public:
    explicit Changelog(QWidget *parent = 0);
    ~Changelog();

private slots:
    void on_Close_clicked();

private:
    Ui::Changelog *ui;
};

#endif // CHANGELOG_H
