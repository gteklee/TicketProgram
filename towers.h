#ifndef TOWERS_H
#define TOWERS_H

#include <QString>
#include <QList>

class Towers
{

protected:

    // Zone 1 tower list.
    QList<QString> zone1, zone2, zone3, zone4, zone5, zone6, zone7, towers;

public:

    Towers();
    ~Towers();
};

#endif // TOWERS_H
