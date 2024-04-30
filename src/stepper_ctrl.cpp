#include "stepper_ctrl.hpp"

#include "hardware/gpio.h"

#include <array>
#include <cstdio>

constexpr std::array<std::array<bool, 2>, 4> sequence {
    { { 1, 1 }, { 0, 1 }, { 0, 0 }, { 1, 0 } }
};

Stepper::Stepper(uint8_t gpioEnable, uint8_t gpio1, uint8_t gpio2)
    : m_gpioEnable { gpioEnable }
    , m_gpio1 { gpio1 }
    , m_gpio2 { gpio2 }
    , m_currentStep { 0 }
{
    printf("Initializing stepper...\r\n");
    uint32_t gpioOutMask
        = (1 << m_gpioEnable) | (1 << m_gpio1) | (1 << m_gpio2);
    gpio_set_dir_out_masked(gpioOutMask);
}

void Stepper::step()
{
    printf("Stepping... ");
    for (int i = 0; i < m_currentStep; i++)
    {
        printf("  ");
    }
    printf("%d\r\n", m_currentStep);

    auto [v1, v2] = sequence[m_currentStep];
    m_currentStep = (m_currentStep + 1) % sequence.size();

    gpio_put(m_gpio1, v1);
    gpio_put(m_gpio2, v2);
}
