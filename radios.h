#ifndef RADIOS_H
#define RADIOS_H

#include <QString>
#include <QList>

class Radios
{

protected:

    // UBNT, CANOPY, & TELRAD list.
    QList<QString> ubnt, canopy, telrad;

public:
    Radios();
    ~Radios();
};

#endif // RADIOS_H
