#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QSettings>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *qmlObj, QObject *parent = nullptr);
    void loadUi();
signals:

public slots:
private:
    void bindShortcut();
    void loadSettings();
    void saveSettings();
    void loadCounter();
    void saveCounter();

private:
    QSettings settings;
    int counter = 0;
    QObject *qmlObj;
};

#endif // MAINWINDOW_H
