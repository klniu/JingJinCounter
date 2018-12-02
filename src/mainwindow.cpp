#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QHotkey>
#include <QSettings>
#include <QSound>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint|Qt::Popup|Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    menu = new QMenu();
    loadSettings();
    adjustWidth();
    QRect rec = QApplication::desktop()->screenGeometry();
    move(rec.width() - width(), rec.height() - height() - 50);
    initActions();
    initLabel();
    bindShortcut();
}

void MainWindow::counterReset()
{
    if (confirmDialog(tr("Are you sure to reset the counter?")) == QMessageBox::Ok) {
        counter = 0;
        saveCounter();
    }
}

void MainWindow::setAlert(QAction *action)
{
    Alert a = static_cast<Alert>(action->data().toUInt());
    if (a == alert) {
        return;
    }
    alert = a;
    setSound(alert);
    saveSettings();
}

void MainWindow::setSound(Alert a)
{
    if (a == Alert::Zhou) {
        this->sound = "qrc:/audio/zhou.wav";
    } else {
        this->sound = "qrc:/audio/bo.wav";
    }
}

void MainWindow::initLabel()
{
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    label = new QLabel(QString::number(counter), this);
    label->setStyleSheet("QLabel { background-color : green; color : white; font-size: 26px; font-weight: bold; border-radius: 10px;}");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

void MainWindow::initActions()
{
    // reset action
    QAction *resetAct = new QAction(tr("Reset"), this);
    resetAct->setStatusTip(tr("Reset Counter Value"));
    connect(resetAct, &QAction::triggered, this, &MainWindow::counterReset);
    menu->addAction(resetAct);

    // set audio
    QAction *boAct = new QAction(tr("Bo"), this);
    resetAct->setStatusTip(tr("Bo sound"));
    resetAct->setData(Alert::Bo);
    resetAct->setCheckable(true);

    QAction *zhouAct = new QAction(tr("Zhou"), this);
    zhouAct->setStatusTip(tr("Zhou sound"));
    zhouAct->setData(Alert::Zhou);
    zhouAct->setCheckable(true);

    QActionGroup *aGroup = new QActionGroup(this);
    aGroup->setExclusive(true);
    aGroup->addAction(boAct);
    aGroup->addAction(zhouAct);
    boAct->setChecked(alert == Alert::Bo);
    zhouAct->setChecked(alert == Alert::Zhou);
    connect(aGroup, &QActionGroup::triggered, this, &MainWindow::setAlert);

    QMenu *alertMenu = new QMenu(tr("Alert"), this);
    alertMenu->addAction(boAct);
    alertMenu->addAction(zhouAct);
    menu->addMenu(alertMenu);

    // quit action
    QAction *quitAct = new QAction(tr("Quit"), this);
    quitAct->setStatusTip(tr("Quit application"));
    connect(quitAct, &QAction::triggered, this, &MainWindow::quit);
    menu->addAction(quitAct);
}

void MainWindow::bindShortcut()
{
    auto hotkey = new QHotkey(QKeySequence("F13"), true, qApp);//The hotkey will be automatically registered
    connect(hotkey, &QHotkey::activated, qApp, [&](){ increaseCounter(); } );
}

void MainWindow::loadSettings()
{
    counter = settings.value("counter", "").toUInt();
    alert = static_cast<Alert>(settings.value("alert", Alert::Bo).toUInt());
    setSound(alert);
//    paintValue(counter);
}

void MainWindow::saveSettings()
{
    settings.setValue("alert", this->alert);
}

void MainWindow::saveCounter()
{
    settings.setValue("counter", counter);
}

void MainWindow::quit()
{
    if (confirmDialog(tr("Are you sure to quit application?")) == QMessageBox::Ok) {
        qApp->quit();
    }
}

void MainWindow::increaseCounter()
{
    label->setText(QString::number(++counter));
    adjustWidth();
    QSound::play(this->sound);
    saveCounter();
}

int MainWindow::confirmDialog(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    return msgBox.exec();
}

void MainWindow::adjustWidth()
{
    int w = 12 * QString::number(counter).length() + 20;
    windowWidth = w > 50 ? w:50;
    setFixedSize(windowWidth, windowHeight);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button()== Qt::LeftButton) {
        isDrag = true;
        mouseStartPoint=event->globalPos();
        windowTopLeftPoint = frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrag) {
        //获得鼠标移动的距离
        QPoint distance=event->globalPos()-mouseStartPoint;
        //改变窗口的位置
        move(windowTopLeftPoint+distance);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
      isDrag = false;
    } else if (event->button() == Qt::RightButton) {
        menu->popup(QPoint(x() + windowWidth, y() + windowHeight));
    }
}
