#include <stdio.h>

#include "pico/stdio.h"
#include "pico/time.h"
#include "pico/types.h"

#include "stepper_ctrl.hpp"

constexpr uint ENB = 3;
constexpr uint IN4 = 4;
constexpr uint IN3 = 5;
constexpr uint IN2 = 6;
constexpr uint IN1 = 7;
constexpr uint ENA = 8;

int main()
{
    stdio_init_all();
    printf("Hello, world!\r\n");

    Stepper stepper(ENA, ENB, IN1, IN2, IN3, IN4);

    uint freq = 100;
    while (true)
    {
        stepper.setFreq(freq);
        stepper.start();
        sleep_ms(1000);

        stepper.stop();
        sleep_ms(1000);

        stepper.stepFor(1000);
    }
}
