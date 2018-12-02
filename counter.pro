TEMPLATE = app

QT += widgets multimedia
CONFIG += c++11


RESOURCES += \
    rc/audio.qrc

# Default rules for deployment.
#include(deployment.pri)

include(QHotkey/qhotkey.pri)

DISTFILES += \
    REMODE.md

HEADERS += \
    src/mainwindow.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp
