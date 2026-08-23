#include <xinu.h>
#include <avr/interrupt.h>
#include "gpio.h"
#include "encoders.h"

/*-----------------------------------------------------------------------
 * Encoder
 *-----------------------------------------------------------------------
 */

/*
 * D2 -> Encoder1 A -> INT0
 * D3 -> Encoder2 A -> INT1
 */
volatile int16_t left_encoder_count = 0;
volatile int16_t right_encoder_count = 0;

/*
 * Interrupción por flanco ascendente en canal A
 */
ISR(INT0_vect)
{
    if (gpio_pin(ENC1_B, GET)) {
        left_encoder_count--;
    } else {
        left_encoder_count++;
    }
}

ISR(INT1_vect)
{
    if (gpio_pin(ENC2_B, GET)) {
        right_encoder_count--;
    } else {
        right_encoder_count++;
    }
}

static inline void encoders_init(void)
{
    gpio_input(ENC1_A);
    gpio_input(ENC1_B);
    gpio_input(ENC2_A);
    gpio_input(ENC2_B);

    /*
     * Pull-ups internas (quitar si el encoder ya tiene pull-up externas)
     */
    gpio_pin(ENC1_A, ON);
    gpio_pin(ENC1_B, ON);
    gpio_pin(ENC2_A, ON);
    gpio_pin(ENC2_B, ON);

    /**
     * D2 = PD2 = INT0 flanco ascendente
     * D3 = PD3 = INT1 flanco ascendente
     */
    EICRA |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);
    EIMSK |= (1 << INT0) | (1 << INT1);

    sei();
}

void encoders(void)
{
    int16_t left_steps, right_steps;

    encoders_init();

    while (1) {
        cli();
        left_steps = left_encoder_count;
        right_steps = right_encoder_count;
        sei();

//        hodor_st_set(LENC_STEPS, left_steps);
//        hodor_st_set(RENC_STEPS, right_steps);
        sleepms(20);//probar cada 10-20ms
    }
}

