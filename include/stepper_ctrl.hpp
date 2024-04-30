#pragma once

#include <cstdint>

class Stepper
{
public:
    Stepper(uint8_t gpioEnable, uint8_t gpio1, uint8_t gpio2);

    void step();

private:
    uint8_t m_gpioEnable;
    uint8_t m_gpio1;
    uint8_t m_gpio2;

    std::size_t m_currentStep;
};
