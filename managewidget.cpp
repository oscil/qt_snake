#include "managewidget.h"

ManageWidget::ManageWidget(QWidget* parent):
    QWidget(parent),
    m_stepsCount(0)
{
    createInterface();
}

void ManageWidget::slot_recv_len(quint32 len)
{
    m_wg_lbl_len->setText(QString::number(len));
}

void ManageWidget::slot_recv_stepEvent()
{
    m_stepsCount+=1;
    m_wg_lbl_stepCount->setText(QString::number(m_stepsCount));
}

void ManageWidget::createInterface()
{
    m_wg_btn_startTimer = new QPushButton("Start");
    connect(m_wg_btn_startTimer, &QPushButton::clicked, [this]{
        emit this->signal_startTimer(this->m_wg_spin_interval->value());
    });
    m_wg_spin_interval = new QSpinBox();
    m_wg_spin_interval->setMinimum(1);
    m_wg_spin_interval->setMaximum(5000);
    m_wg_spin_interval->setValue(300);
    QHBoxLayout* hlo = new QHBoxLayout();
    hlo->addWidget(m_wg_btn_startTimer);
    hlo->addWidget(m_wg_spin_interval);

    m_wg_btn_stopTimer = new QPushButton("Stop");
    connect(m_wg_btn_stopTimer, &QPushButton::clicked, [this]{emit this->signal_stopTimer();
    });
    m_wg_btn_restart = new QPushButton("Restart");
    connect(m_wg_btn_stopTimer, &QPushButton::clicked, [this]{emit this->signal_restart();
    });
    QHBoxLayout* hlo2 = new QHBoxLayout();
    hlo2->addWidget(m_wg_btn_stopTimer);
    hlo2->addWidget(m_wg_btn_restart);

    m_wg_lbl_len = new QLabel("0");
    QFont font = m_wg_lbl_len->font();
    font.setPointSize(font.pointSize()*4);
    font.setBold(true);
    m_wg_lbl_len->setFont(font);

    m_wg_lbl_stepCount = new QLabel("0");
    m_wg_lbl_stepCount->setFont(font);
    QHBoxLayout* hlo3 = new QHBoxLayout();
    hlo3->addWidget(m_wg_lbl_stepCount);
    hlo3->addWidget(m_wg_lbl_len);

    QVBoxLayout* vlo = new QVBoxLayout();
    vlo->addLayout(hlo3);
    vlo->addLayout(hlo);
    vlo->addLayout(hlo2);

    m_wg_btn_step = new QPushButton("Step");
    connect(m_wg_btn_stopTimer, &QPushButton::clicked, [this]{emit this->signal_step();
    });
    m_wg_btn_step->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    QHBoxLayout* main_hlo = new QHBoxLayout(this);
    main_hlo->addLayout(vlo);
    main_hlo->addWidget(m_wg_btn_step);

    this->setLayout(main_hlo);
}
