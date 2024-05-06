#pragma once

#include <cstdint>

#include "pico/time.h"
#include "pico/types.h"

class Stepper
{
public:
    Stepper(uint8_t gpioEnableA, uint8_t gpioEnableB, uint8_t gpio1,
            uint8_t gpio2, uint8_t gpio3, uint8_t gpio4);

    void setFreq(uint freq);
    uint freq();

    void step();
    void stepN(uint N);
    void stepFor(uint timeMs);

    void start();
    void stop();
    bool isRunning();

    void enable();
    void disable();

private:
    bool        timerCallback();
    static bool timerDispatcher(repeating_timer_t* timer);

    uint8_t m_gpioEnableA;
    uint8_t m_gpioEnableB;
    uint8_t m_gpio1;
    uint8_t m_gpio2;
    uint8_t m_gpio3;
    uint8_t m_gpio4;

    uint     m_currentFreq { 100 };
    uint64_t m_stepDelayUs { 10'000 };

    bool              m_isRunning { false };
    repeating_timer_t m_timer;

    std::size_t m_currentStep { 0 };
};
