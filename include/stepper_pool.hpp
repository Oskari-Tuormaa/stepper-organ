#pragma once

#include <array>

#include "stepper_ctrl.hpp"

template <std::size_t NStepper>
class StepperPool
{
public:
    template <typename... Args>
    StepperPool(Args&&... args)
        : m_steppers { std::forward<Args>(args)... }
    { }

    void start_note(uint freq)
    {
        for (Stepper& stepper : m_steppers)
        {
            if (!stepper.isRunning())
            {
                stepper.setFreq(freq);
                stepper.start();
                return;
            }
        }
    }

    void end_note(uint freq)
    {
        for (Stepper& stepper : m_steppers)
        {
            if (stepper.isRunning() && (stepper.freq() == freq))
            {
                stepper.stop();
                return;
            }
        }
    }

private:
    std::array<Stepper, NStepper> m_steppers;
};
