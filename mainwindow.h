#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QHBoxLayout>

#include "managewidget.h"
#include "field.h"
#include "game.h"
#include "snake.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_timer();
    void slot_startTimer(qint32);
    void slot_stopTimer();
    void slot_restart();

protected:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);



private:
    Field* m_field;
    Game* m_game;
    QKeyEvent m_lastKeyEvent;

    QTimer m_timer;
    ManageWidget* m_manage;


};

#endif // MAINWINDOW_H
