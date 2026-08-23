#include <xinu.h>
#include "gpio.h"
#include "adc.h"
#include "timer.h"
#include "motors.h"

static inline void motors_init()
{
    gpio_output(MOT1_A);
    gpio_output(MOT1_B);
    gpio_output(MOT2_A);
    gpio_output(MOT2_B);
    
    timer1_init(0);
}

static inline void set_direction(uint8_t dir)
{
    switch (dir) {
    case DIR_FORWARD:
        gpio_pin(MOT1_A, ON);
        gpio_pin(MOT1_B, OFF);
        gpio_pin(MOT2_A, ON);
        gpio_pin(MOT2_B, OFF);
        break;

    case DIR_REVERSE:
        gpio_pin(MOT1_A, OFF);
        gpio_pin(MOT1_B, ON);
        gpio_pin(MOT2_A, OFF);
        gpio_pin(MOT2_B, ON);
        break;

    case DIR_ROTATE_LEFT:
        gpio_pin(MOT1_A, ON);
        gpio_pin(MOT1_B, OFF);
        gpio_pin(MOT2_A, OFF);
        gpio_pin(MOT2_B, ON);
        break;

    case DIR_ROTATE_RIGHT:
        gpio_pin(MOT1_A, OFF);
        gpio_pin(MOT1_B, ON);
        gpio_pin(MOT2_A, ON);
        gpio_pin(MOT2_B, OFF);
        break;

    default:
        gpio_pin(MOT1_A, OFF);
        gpio_pin(MOT1_B, OFF);
        gpio_pin(MOT2_A, OFF);
        gpio_pin(MOT2_B, OFF);
        break;
    }
}

void motors(void)
{
    uint16_t adc_value;
    int16_t error;
    uint8_t target_pwm = 0;
    uint8_t current_pwm = 0;
    uint8_t target_dir = DIR_STOP;
    uint8_t current_dir = DIR_STOP;
    uint32_t temp;

    motors_init();

    while (1) {
        adc_value = adc_read(ADC7);
        error = (int16_t)adc_value - 512;

        /*
         * Zona muerta
         */
        if (error > -DEADZONE && error < DEADZONE) {
            target_pwm = 0;
            target_dir = DIR_STOP;
        } else {
            /*
             * Determinar dirección
             */
            if (error > 0) {
                target_dir = DIR_ROTATE_LEFT;
            } else {
                target_dir = DIR_ROTATE_RIGHT;
                error = -error;
            }

            /*
             * Mapear:
             * DEADZONE..511 -> MIN_PWM..255
             */
            temp = (uint32_t)(error - DEADZONE) * (MAX_PWM - MIN_PWM);
            temp /= (511 - DEADZONE);
            target_pwm = MIN_PWM + temp;

            if (target_pwm > MAX_PWM)
                target_pwm = MAX_PWM;
        }

        /*
         * Cambio de dirección seguro
         */
        if (current_dir != target_dir) {
            /*
             * Frenar antes de cambiar de dirección
             */
            if (current_pwm > 0) {
                current_pwm -= RAMP_STEP;

                if (current_pwm > 255)
                    current_pwm = 0;
            } else {
                current_dir = target_dir;
                set_direction(current_dir);
            }
        } else {
            /*
             * Rampa de aceleración normal
             */
            if (current_pwm < target_pwm) {
                current_pwm += RAMP_STEP;

                if (current_pwm > target_pwm)
                    current_pwm = target_pwm;
            } else if (current_pwm > target_pwm) {
                current_pwm -= RAMP_STEP;

                if (current_pwm < target_pwm)
                    current_pwm = target_pwm;
            }
        }

        timer1_pulse(current_pwm);
        sleepms(RAMP_DELAY_MS);
    }
}

