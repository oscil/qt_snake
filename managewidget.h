#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QFont>


class ManageWidget : public QWidget
{
    Q_OBJECT
public:
    ManageWidget(QWidget* parent = 0);


signals:
    void signal_startTimer(qint32);
    void signal_stopTimer();
    void signal_step();
    void signal_restart();


public slots:
    void slot_recv_len(quint32);
    void slot_recv_stepEvent();


private:
    QPushButton* m_wg_btn_startTimer;
    QPushButton* m_wg_btn_step;
    QPushButton* m_wg_btn_stopTimer;
    QPushButton* m_wg_btn_restart;
    QSpinBox* m_wg_spin_interval;
    QLabel* m_wg_lbl_len;
    QLabel* m_wg_lbl_stepCount;

    void createInterface();
    quint32 m_stepsCount;
};

#endif // MANAGEWIDGET_H
