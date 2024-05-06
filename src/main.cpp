#include <array>
#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/uart.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "pico/types.h"

#include "notes.hpp"
#include "stepper_ctrl.hpp"
#include "stepper_pool.hpp"

constexpr uint ENB = 3;
constexpr uint IN4 = 4;
constexpr uint IN3 = 5;
constexpr uint IN2 = 6;
constexpr uint IN1 = 7;
constexpr uint ENA = 8;

#define UART_ID   uart0
#define BAUD_RATE 115200

#define UART_TX_PIN 0
#define UART_RX_PIN 1

constexpr std::array midiNote {
    8,    9,    9,    10,   10,    11,    12,    12,   13,   14,   15,   15,
    16,   17,   18,   19,   21,    22,    23,    24,   26,   28,   29,   31,
    33,   35,   37,   39,   41,    44,    46,    49,   52,   55,   58,   62,
    65,   69,   73,   78,   82,    87,    92,    98,   104,  110,  117,  123,
    131,  139,  147,  156,  165,   175,   185,   196,  208,  220,  233,  247,
    262,  277,  294,  311,  330,   349,   370,   392,  415,  440,  466,  494,
    523,  554,  587,  622,  659,   698,   740,   784,  831,  880,  932,  988,
    1047, 1109, 1175, 1245, 1319,  1397,  1480,  1568, 1661, 1760, 1865, 1976,
    2093, 2217, 2349, 2489, 2637,  2794,  2960,  3136, 3322, 3520, 3729, 3951,
    4186, 4435, 4699, 4978, 5274,  5588,  5920,  6272, 6645, 7040, 7459, 7902,
    8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544
};
uint currentFreq = 0;

StepperPool<1>* pPool;

void uart_rx()
{
    while (uart_is_readable(uart0))
    {
        uint8_t idx  = uart_getc(uart0);
        uint    freq = midiNote[idx] / 2;

        if (freq == currentFreq)
        {
            pPool->end_note(freq);
            currentFreq = 0;
        }
        else if (currentFreq == 0)
        {
            pPool->start_note(freq);
            currentFreq = freq;
        }
    }
}

int main()
{
    stdio_init_all();

    irq_set_exclusive_handler(UART0_IRQ, uart_rx);
    irq_set_enabled(UART0_IRQ, true);

    uart_set_irq_enables(uart0, true, false);

    Stepper        stepper(ENA, ENB, IN1, IN2, IN3, IN4);
    StepperPool<1> pool { stepper };
    pPool = &pool;

    while (true)
    {
        sleep_ms(1000);
    }
}
