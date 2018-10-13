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
}

void MainWindow::counterResetSlot()
{
   counter = 0;
   qmlObj->setProperty("counterValue", counter);
   saveCounter();
}

void MainWindow::bindShortcut()
{
    auto hotkey = new QHotkey(QKeySequence("F13"), true, qApp);//The hotkey will be automatically registered
    QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
        qmlObj->setProperty("counterValue", ++counter);
        QSound::play("qrc:/audio/bo1.wav");
        saveCounter();
    });
}

void MainWindow::loadSettings()
{
    counter = settings.value("counter", "").toUInt();
}

void MainWindow::saveSettings()
{
    settings.setValue("text", "");
}

void MainWindow::saveCounter()
{
    settings.setValue("counter", counter);
}
