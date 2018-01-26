#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T14:32:43
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicketCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    confirmationexit.cpp \
    repairticket.cpp \
    repairticketSonar.cpp \
    disconnectticket.cpp \
    network_static.cpp \
    onsite.cpp \
    towers.cpp \
    radios.cpp \
    network_key.cpp \
    network_voip.cpp \
    network_mtl.cpp \
    install.cpp \
    network_other.cpp \
    changelog.cpp \
    relo.cpp

HEADERS  += mainwindow.h \
    confirmationexit.h \
    repairticket.h \
    repairticketSonar.h \
    disconnectticket.h \
    network_static.h \
    onsite.h \
    towers.h \
    radios.h \
    network_key.h \
    network_voip.h \
    network_mtl.h \
    install.h \
    network_other.h \
    changelog.h \
    relo.h

FORMS    += mainwindow.ui \
    confirmationexit.ui \
    repairticket.ui \
    repairticketSonar.ui \
    disconnectticket.ui \
    network_static.ui \
    onsite.ui \
    network_key.ui \
    network_voip.ui \
    network_mtl.ui \
    install.ui \
    network_other.ui \
    changelog.ui \
    relo.ui

RESOURCES += \
    images.qrc
