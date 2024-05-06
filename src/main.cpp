#include <array>
#include <stdio.h>

#include "pico/stdio.h"
#include "pico/time.h"
#include "pico/types.h"

#include "stepper_ctrl.hpp"
#include "notes.hpp"

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

    std::array song {
        C1,
        Db1,
        E1,
        F1,
        G1,
        Ab1,
        B1,
        C2,
    };

    while (true)
    {
        stepper.setFreq(song[0]);
        stepper.start();

        for (uint note : song)
        {
            stepper.setFreq(note);
            sleep_ms(100);
        }

        stepper.stop();
        sleep_ms(1000);
    }
}
