/* clkinit.c */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

uint32      clktime;            /* Seconds since boot			*/
volatile    uint32 count100 ;   /* ms since last clock tick     */
qid16       sleepq;             /* Queue of sleeping processes  */
uint32      preempt;            /* Preemption counter			*/

/*------------------------------------------------------------------------
 * clkinit  -  Initialize the clock and sleep queue at startup
 *------------------------------------------------------------------------
 */
void clkinit(void)
{
	
	struct clock_csreg * clockptr;

	sleepq = newqueue();                /* Allocate a queue to hold the delta   */
                                        /*   list of sleeping processes         */
	preempt = QUANTUM;                  /* Set the preemption time              */
	clktime = 0;                        /* Start counting seconds               */
    count100 = 0;


	/* 
         * AVR atmega328p timer/clock init: interrupt every 1ms 
	 * The AVR TIMER interrupt rutine is in clkhandler.c
         */
#if CLK_TIMER0
    kprintf("Using Timer0\n");
//	TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
	TCCR0B |= (1<<CS02) | (1<<CS00);   //clock select is divided by 1024.
	TCCR0A |= (1<<WGM01);              //sets mode to CTC
//	OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	OCR0A = 156;                        //sets TOP to 156 so the timer will overflow every 10 ms.    
	TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable
#else
    kprintf("Using Timer1\n");
	TCCR1B |= (1<<CS11) | (1<<CS10);   //clock select is divided by 64.
    TCCR1B |= (1<<WGM12);              //sets mode to CTC
	OCR1A = 0x9BA;                     //sets TOP to 124 so the timer will overflow every 1 ms.    
	TIMSK1 |= (1<<OCIE1A);             //Output Compare Match A Interrupt Enable
#endif // CLK_TIMER0

	return;
}

