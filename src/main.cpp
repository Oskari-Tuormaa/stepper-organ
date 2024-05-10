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

struct NoteMsg
{
    bool onoff;
    uint channel;
    uint freq;
};
std::array<NoteMsg, 128> queue;
uint                     queue_head = 0;
uint                     queue_tail = 0;

void uart_rx()
{
    while (uart_is_readable(uart0))
    {
        uint8_t onoff   = uart_getc(uart0);
        uint8_t idx     = uart_getc(uart0);
        uint8_t channel = uart_getc(uart0);
        uint    freq    = midiNote[idx];

        queue[queue_head].onoff   = (onoff == 'O' ? true : false);
        queue[queue_head].channel = channel;
        queue[queue_head].freq    = freq;
        queue_head                = (queue_head + 1) % queue.size();
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

    while (true)
    {
#if 1
        sleep_ms(1);

        if (queue_head != queue_tail)
        {
            NoteMsg& msg = queue[queue_tail];
            queue_tail   = (queue_tail + 1) % queue.size();

#if 0
            if (msg.onoff)
            {
                pool.start_note_on_channel(msg.freq, msg.channel);
            }
            else
            {
                pool.end_note_on_channel(msg.channel);
            }
#else
            if (msg.onoff)
            {
                pool.start_note(msg.freq);
            }
            else
            {
                pool.end_note(msg.freq);
            }
#endif
        }
#else
        pool.start_note(C1);
        pool.start_note(A2);
        pool.end_note(C1);
        sleep_ms(500);

        constexpr std::array melody {
            C1, D1, E1, F1, 
            C1, D1, E1, F1,
            C1, D1, E1, F1,
            C1, D1, E1, F1,
        };
        for (auto freq : melody)
        {
            pool.start_note(freq);
            sleep_ms(100);
            pool.end_note(freq);
        }
        sleep_ms(500);

        pool.end_note(A2);
        sleep_ms(4000);
#endif
    }
}
