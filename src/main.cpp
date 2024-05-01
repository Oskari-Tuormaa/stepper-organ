#include <array>
#include <optional>
#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "pico/types.h"

#include "notes.hpp"
#include "stepper_ctrl.hpp"

struct TimerCallbackData
{
    Stepper& stepper;
};

bool stepper_callback(repeating_timer_t* timer)
{
    TimerCallbackData& cbData
        = *static_cast<TimerCallbackData*>(timer->user_data);

    Stepper& stepper = cbData.stepper;

    stepper.step();

    return true;
}

struct StepperData
{
    Stepper           stepper;
    TimerCallbackData cbData;
    repeating_timer_t timer;
    int32_t           delayMs;

    template <typename... Args>
    StepperData(int32_t delayMs, Args... args)
        : stepper { static_cast<uint8_t>(args)... }
        , cbData { .stepper = stepper }
        , timer {}
        , delayMs { delayMs }
    { }
};

constexpr uint ENB = 3;
constexpr uint IN4 = 4;
constexpr uint IN3 = 5;
constexpr uint IN2 = 6;
constexpr uint IN1 = 7;
constexpr uint ENA = 8;

struct Note
{
    std::optional<uint> freqHz;
    uint                timeMs;
    uint                timeAfterMs;
};

constexpr uint       noteOn    = 500;
constexpr uint       noteAfter = 500;
constexpr std::array song { std::to_array<Note>({
    { C1, noteOn, noteAfter },
    { D1, noteOn, noteAfter },
    { Eb1, noteOn, noteAfter },
    { F1, noteOn, noteAfter },
    { G1, noteOn, noteAfter },
    { Eb1, noteOn, noteAfter },
    { G1, noteOn * 3, noteAfter },

    { Gb1, noteOn, noteAfter },
    { D1, noteOn, noteAfter },
    { Gb1, noteOn * 3, noteAfter },

    { F1, noteOn, noteAfter },
    { Db1, noteOn, noteAfter },
    { F1, noteOn * 3, noteAfter },
}) };

int main()
{
    stdio_init_all();
    printf("Hello, world!\r\n");

    Stepper stepper(ENA, ENB, IN1, IN2, IN3, IN4);

    // std::array<StepperData, 1> steppers { {
    //     { -1000, 1,  2,   3 },
    // } };

    // for (auto& stepper : steppers)
    // {
    //     add_repeating_timer_ms(stepper.delayMs, stepper_callback,
    //                            &stepper.cbData, &stepper.timer);
    // }

    // TimerCallbackData cbData = { .stepper = stepper };
    // repeating_timer_t timer;
    // add_repeating_timer_ms(-1000, stepper_callback, &cbData, &timer);

    while (true)
    {
#if 0
        for (Note note : song)
        {
            if (note.freqHz)
            {
                stepper.setFreq(note.freqHz.value());
                stepper.stepFor(note.timeMs);
            }
            if (note.timeAfterMs != 0)
            {
                sleep_ms(note.timeAfterMs);
            }
        }
#endif
        sleep_ms(2000);
    }
}
