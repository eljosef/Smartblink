#include "gpio.h"

#include <lgpio.h>

/// GPIO
Gpio::Gpio(QObject *parent) : QObject(parent)
{
    m_handle = lgGpiochipOpen(0); /* get a handle to the GPIO */
    int init_lvl = 0;
    for(int pin : LEDS)
        lgGpioClaimOutput(m_handle, LFLAGS, pin, init_lvl); /* initial level = init_lvl */
}

// Destructor
Gpio::~Gpio()
{
    // LED's Ausschalten
        int state = 0;
        for (int pin : LEDS)
            lgGpioWrite(m_handle, pin, state);
        lgGpiochipClose(m_handle);
}

// Set LEDS pin and value
void Gpio::set(int pin,bool value)
{
    lgGpioWrite(m_handle, pin, value); /* initial level = init_lvl */
}


void Gpio::set(unsigned int pattern)
{
    int n = 0;
    bool value;
    unsigned int check = 0b0001;
    for(auto pin : LEDS)
    {
        // n stelle von pattern ausmaskieren, value =
        value = check & pattern>>n;
        lgGpioWrite(m_handle, pin, value);
        n++;
    }
}
