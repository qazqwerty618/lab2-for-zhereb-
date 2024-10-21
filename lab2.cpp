// main.cpp
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTimer();
    void startTimer();
    void stopTimer();
    void timerFinished();
    void updateTimerList();
    
private:
    Ui::MainWindow *ui;
    QList<QTimer*> timers;
};

#endif // MAINWINDOW_H
// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    // З'єднання сигналів і слотів
    connect(ui->addTimerButton, &QPushButton::clicked, this, &MainWindow::addTimer);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addTimer() {
    // Додаємо новий таймер
    QTimer *timer = new QTimer(this);
    timer->setInterval(ui->timeInput->value() * 1000); // Конвертація в мілісекунди
    timers.append(timer);
    
    // Оновлюємо список таймерів
    updateTimerList();
    
    connect(timer, &QTimer::timeout, this, &MainWindow::timerFinished);
}

void MainWindow::startTimer() {
    for (QTimer* timer : timers) {
        timer->start();
    }
}

void MainWindow::stopTimer() {
    for (QTimer* timer : timers) {
        timer->stop();
    }
}

void MainWindow::timerFinished() {
    QMessageBox::information(this, "Таймер", "Таймер завершився!");
    updateTimerList();
}

void MainWindow::updateTimerList() {
    ui->timerListWidget->clear();
    for (int i = 0; i < timers.size(); ++i) {
        ui->timerListWidget->addItem("Таймер " + QString::number(i + 1));
    }
}
// timer.h
#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer : public QTimer {
    Q_OBJECT
public:
    Timer(QObject *parent = nullptr);
    ~Timer();
};

#endif // TIMER_H
// timer.cpp
#include "timer.h"

Timer::Timer(QObject *parent) : QTimer(parent) {
    // Налаштування таймера
}

Timer::~Timer() {
}
// timerlist.h
#ifndef TIMERLIST_H
#define TIMERLIST_H

#include <QListWidget>

class TimerList : public QListWidget {
    Q_OBJECT
public:
    TimerList(QWidget *parent = nullptr);
    ~TimerList();
};

#endif // TIMERLIST_H
// timerlist.cpp
#include "timerlist.h"

TimerList::TimerList(QWidget *parent) : QListWidget(parent) {
    // Налаштування списку таймерів
}

TimerList::~TimerList() {
}
