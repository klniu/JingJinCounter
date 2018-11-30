#include "mainwindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QHotkey>
#include <QSettings>
#include <QSound>

MainWindow::MainWindow(QObject *qmlObj, QObject *parent) : QObject(parent), qmlObj(qmlObj)
{
}

void MainWindow::loadUi() {
    bindShortcut();
    loadSettings();
    qmlObj->setProperty("counterValue", counter);
    QObject::connect(qmlObj, SIGNAL(counterResetSignal()), this, SLOT(counterResetSlot()));
    QObject::connect(qmlObj, SIGNAL(setAlertSignal(int)), this, SLOT(setAlertSlot(int)));

}

void MainWindow::counterResetSlot()
{
   counter = 0;
   qmlObj->setProperty("counterValue", counter);
   saveCounter();
}

void MainWindow::setAlertSlot(int alert)
{
    this->alert = static_cast<Alert>(alert);
    if (this->alert == Alert::Zhou) {
        this->sound = "qrc:/audio/zhou.wav";
    } else {
        this->sound = "qrc:/audio/bo.wav";
    }
    saveSettings();
}

void MainWindow::bindShortcut()
{
    auto hotkey = new QHotkey(QKeySequence("F13"), true, qApp);//The hotkey will be automatically registered

    QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
        qmlObj->setProperty("counterValue", ++counter);
        QSound::play(this->sound);
        saveCounter();
    });
}

void MainWindow::loadSettings()
{
    counter = settings.value("counter", "").toUInt();
    this->alert = static_cast<Alert>(settings.value("alert", Alert::Bo).toUInt());
}

void MainWindow::saveSettings()
{
    settings.setValue("alert", this->alert);
}

void MainWindow::saveCounter()
{
    settings.setValue("counter", counter);
}
