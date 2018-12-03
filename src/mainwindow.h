#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QSettings>
#include <QLabel>
#include <QMouseEvent>


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    enum Alert { Bo, Zhou };

    explicit MainWindow(QWidget *parent = nullptr);
    void loadUi();
signals:

public slots:
    void counterReset();
    void setAlert(QAction *a);
    void setSound(Alert a);
private:
    void initLabel();
    void initActions();
    void bindShortcut();
    void loadSettings();
    void saveSettings();
    void loadCounter();
    void saveCounter();
    void quit();
    void increaseCounter();
    int confirmDialog(QString text);
    void adjustWidth();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QMenu *menu;
    QSettings settings;
    uint counter = 0;
    Alert alert = Alert::Bo;
    QString sound;
    int windowWidth;
    const int windowHeight = 40;
    QLabel *label;
    QPoint windowTopLeftPoint;
    QPoint mouseStartPoint;
    bool isDrag = false;
};

#endif // MAINWINDOW_H
