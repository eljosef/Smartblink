#include "gui.h"

// define at begining of gui
Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    m_leds = new Gpio(this);
    m_state = 0;
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Gui::toggle);
    m_timer->start(TIMEOUT);
}

// take slider value
void Gui::on_speedSlider_valueChanged(int value)
{
    m_timer->start(1000/value);
}
// if blink selected
void Gui::on_blinkButton_clicked()
{
    m_blinkrun = 1;
}

// if Lauflicht selected
void Gui::on_lauflichtButton_clicked()
{
    m_blinkrun = 0;
    count = 1;
}

// toggle mode
void Gui::toggle()
{
    m_state = !m_state;
    if(m_blinkrun == 1)
    {
        if(m_state == 1)
        {
            count = 15;
        }else {
            count = 0;
        }
        m_leds->set(count);
    }
    if(m_blinkrun == 0)
    {
        m_leds->set(count);
        if(count < 8)
        {
            count = count * 2;
        }
        else {
            count = 1;
        }
    }
}
