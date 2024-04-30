#include <array>
#include <stdio.h>

#include "pico/stdio.h"
#include "pico/time.h"

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

int main()
{
    stdio_init_all();
    printf("Hello, world!\r\n");

    std::array<StepperData, 1> steppers { {
        { -1000, 1,  2,   3 },
    } };

    for (auto& stepper : steppers)
    {
        add_repeating_timer_ms(stepper.delayMs, stepper_callback,
                               &stepper.cbData, &stepper.timer);
    }

    // TimerCallbackData cbData = { .stepper = stepper };
    // repeating_timer_t timer;
    // add_repeating_timer_ms(-1000, stepper_callback, &cbData, &timer);

    while (true)
    {
        sleep_ms(1000);
    }
}
