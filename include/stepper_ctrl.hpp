#pragma once

#include <cstdint>

#include "pico/types.h"

class Stepper
{
public:
    Stepper(uint8_t gpioEnableA, uint8_t gpioEnableB, uint8_t gpio1,
            uint8_t gpio2, uint8_t gpio3, uint8_t gpio4);

    void setFreq(uint freq);
    void step();
    void stepN(uint N);
    void stepFor(uint timeMs);
    void enable();
    void disable();

private:
    uint8_t m_gpioEnableA;
    uint8_t m_gpioEnableB;
    uint8_t m_gpio1;
    uint8_t m_gpio2;
    uint8_t m_gpio3;
    uint8_t m_gpio4;

    uint64_t m_stepDelayUs;

    std::size_t m_currentStep;
};
