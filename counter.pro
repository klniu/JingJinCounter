TEMPLATE = app

QT += qml quick widgets multimedia
CONFIG += c++11


RESOURCES += \
    rc/qml.qrc \
    rc/audio.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

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
