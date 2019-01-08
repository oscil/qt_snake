#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_lastKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier),
      m_manage(nullptr)
{
    qint32 w = 50;
    qint32 h = 25;
    quint32 side = 20;
    quint32 managWidth = 300;
    m_field = new Field(w, h, side);
    m_field->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_game = new Game(w, h);
    m_field->setSnake(m_game->getSnake());
    m_field->setMap(m_game->getMap());
    this->resize(w*side+managWidth+50, h*side+50);

    m_manage = new ManageWidget;
    m_manage->resize(managWidth, this->height());
    m_manage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    connect(m_manage, &ManageWidget::signal_startTimer,
            this, &MainWindow::slot_startTimer);
    connect(m_manage, &ManageWidget::signal_stopTimer,
            this, &MainWindow::slot_stopTimer);

    QWidget* central = new QWidget;
    QHBoxLayout* hlo = new QHBoxLayout;
    hlo->addWidget(m_field);
    hlo->addWidget(m_manage);
    central->setLayout(hlo);
    this->setCentralWidget(central);
    m_field->setFocus();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slot_timer()));
    m_timer.start(300);
}


MainWindow::~MainWindow()
{

}


void MainWindow::slot_timer()
{
    m_game->update(&m_lastKeyEvent);
    m_lastKeyEvent = QKeyEvent(QEvent::None, 0, 0);
    m_field->update();
}

void MainWindow::slot_startTimer(qint32 interval)
{
    m_timer.start(interval);
}

void MainWindow::slot_stopTimer()
{
    m_timer.stop();
}

void MainWindow::slot_restart()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    m_lastKeyEvent = *event;
    if (event->key() == Qt::Key_Space){
        m_timer.stop();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "CLOSE!";
    if (m_manage)
        delete m_manage;
}



