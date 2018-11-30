#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QSettings>


class MainWindow : public QObject
{
    Q_OBJECT
public:
    enum Alert { Bo, Zhou };

    explicit MainWindow(QObject *qmlObj, QObject *parent = nullptr);
    void loadUi();
signals:

public slots:
    void counterResetSlot();
    void setAlertSlot(int alert);
private:
    void bindShortcut();
    void loadSettings();
    void saveSettings();
    void loadCounter();
    void saveCounter();

private:
    QSettings settings;
    uint counter = 0;
    QObject *qmlObj;
    Alert alert = Alert::Bo;
    QString sound;
};

#endif // MAINWINDOW_H
