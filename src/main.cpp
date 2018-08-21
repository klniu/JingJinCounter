#include "mainwindow.h"

#include <QApplication>
#include <QQmlComponent>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Klniu");
    QCoreApplication::setOrganizationDomain("klniu.com");
    QCoreApplication::setApplicationName("JingJinCounter");
    QApplication app(argc, argv);
    QQmlEngine engine;
    QQmlComponent component(&engine, "qrc:/main.qml");
    QObject *qmlObj = component.create();

    MainWindow mainWindow(qmlObj);
    mainWindow.loadUi();

//    if ( !globalShortcut.isValid() ) {
//        qDebug() << QString("Error: Failed to set shortcut %1")
//                    .arg(shortcut.toString()) << endl;
//    }

    return app.exec();
}
