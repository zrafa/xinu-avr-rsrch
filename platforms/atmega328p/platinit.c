/* platinit.c - platinit */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>


/*------------------------------------------------------------------------
 * platinit - platform specific initialization
 *------------------------------------------------------------------------
 */

void platinit(void)
{
#if CLK_TIMER0
	/* 
         * AVR atmega328p timer/clock init: interrupt every 1ms 
	 * The AVR TIMER interrupt rutine is in clkhandler.c
         */
	TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
	TCCR0A |= (1<<WGM01);              //sets mode to CTC
	OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable
#else
	TCCR1B |= (1<<CS11) | (1<<CS10);   //clock select is divided by 64.
    TCCR1B |= (1<<WGM12);              //sets mode to CTC
	OCR1A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 10 ms.    
	TIMSK1 |= (1<<OCIE1A);             //Output Compare Match A Interrupt Enable
#endif // CLK_TIMER0
}

#if CLK_TIMER0
ISR(TIMER0_COMPA_vect)
#else
ISR(TIMER1_COMPA_vect)
#endif // CLK_TIMER0
{
    clkhandler();
}

