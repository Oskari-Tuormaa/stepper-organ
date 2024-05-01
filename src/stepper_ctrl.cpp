#include "stepper_ctrl.hpp"

#include "hardware/gpio.h"
#include "pico/time.h"

#include <array>
#include <cstdio>

constexpr std::array<std::array<bool, 4>, 4> sequence {
    { { 1, 0, 0, 1 },
      { 0, 1, 0, 1 },
      { 0, 1, 1, 0 },
      { 1, 0, 1, 0 } }
};

Stepper::Stepper(uint8_t gpioEnableA, uint8_t gpioEnableB, uint8_t gpio1,
                 uint8_t gpio2, uint8_t gpio3, uint8_t gpio4)
    : m_gpioEnableA { gpioEnableA }
    , m_gpioEnableB { gpioEnableB }
    , m_gpio1 { gpio1 }
    , m_gpio2 { gpio2 }
    , m_gpio3 { gpio3 }
    , m_gpio4 { gpio4 }
    , m_currentStep { 0 }
{
    printf("Initializing stepper...\r\n");

    gpio_init(m_gpioEnableA);
    gpio_set_dir(m_gpioEnableA, GPIO_OUT);

    gpio_init(m_gpioEnableB);
    gpio_set_dir(m_gpioEnableB, GPIO_OUT);

    gpio_init(m_gpio1);
    gpio_set_dir(m_gpio1, GPIO_OUT);

    gpio_init(m_gpio2);
    gpio_set_dir(m_gpio2, GPIO_OUT);

    gpio_init(m_gpio3);
    gpio_set_dir(m_gpio3, GPIO_OUT);

    gpio_init(m_gpio4);
    gpio_set_dir(m_gpio4, GPIO_OUT);

    gpio_put(m_gpioEnableA, false);
    gpio_put(m_gpioEnableB, false);
}

void Stepper::setFreq(uint freq)
{
    m_stepDelayUs = 1'000'000 / freq;
}

void Stepper::step()
{
    printf("Stepping... ");
    for (std::size_t i = 0; i < m_currentStep; i++)
    {
        printf("  ");
    }
    printf("%d\r\n", m_currentStep);

    auto [v1, v2, v3, v4] = sequence[m_currentStep];
    m_currentStep         = (m_currentStep + 1) % sequence.size();

    gpio_put(m_gpio1, v1);
    gpio_put(m_gpio2, v2);
    gpio_put(m_gpio3, v3);
    gpio_put(m_gpio4, v4);
    sleep_us(m_stepDelayUs);
}

void Stepper::stepN(uint N)
{
    enable();
    for (std::size_t i = 0; i < N; i++)
    {
        step();
    }
    disable();
}

void Stepper::stepFor(uint timeMs)
{
    uint nSteps = 1000 * timeMs / m_stepDelayUs;
    stepN(nSteps);
}

void Stepper::enable()
{
    gpio_put(m_gpioEnableA, true);
    gpio_put(m_gpioEnableB, true);
}

void Stepper::disable()
{
    gpio_put(m_gpioEnableA, false);
    gpio_put(m_gpioEnableB, false);
}
