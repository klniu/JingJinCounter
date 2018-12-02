#include "mainwindow.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Klniu");
    QCoreApplication::setOrganizationDomain("klniu.com");
    QCoreApplication::setApplicationName("JingJinCounter");
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
