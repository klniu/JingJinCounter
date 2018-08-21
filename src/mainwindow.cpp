#include "mainwindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QHotkey>
#include <QSettings>

MainWindow::MainWindow(QObject *qmlObj, QObject *parent) : QObject(parent), qmlObj(qmlObj)
{
}

void MainWindow::loadUi() {
    bindShortcut();
    loadSettings();
    qmlObj->setProperty("counterValue", counter);
}

void MainWindow::bindShortcut()
{
    auto hotkey = new QHotkey(QKeySequence("F22"), true, qApp);//The hotkey will be automatically registered
    qDebug() << "Is Registered: " << hotkey->isRegistered();
    QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
        qmlObj->setProperty("counterValue", ++counter);
        saveCounter();
    });
}

void MainWindow::loadSettings()
{
    counter = settings.value("counter", "").toInt();
}

void MainWindow::saveSettings()
{
    settings.setValue("text", "");
}

void MainWindow::saveCounter()
{
    settings.setValue("counter", counter);
}
