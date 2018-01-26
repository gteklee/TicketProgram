#ifndef INFODIALOGUE_H
#define INFODIALOGUE_H

#include <QDialog>

namespace Ui {
class Infodialogue;
}

class Infodialogue : public QDialog
{
    Q_OBJECT

public:
    explicit Infodialogue(QWidget *parent = 0);
    ~Infodialogue();

private:
    Ui::Infodialogue *ui;
};

#endif // INFODIALOGUE_H
