/* clkhandler.c - clkhandler */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int avr_ticks=0;

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */

/* void clkhandler() */
#if CLK_TIMER0
ISR(TIMER0_COMPA_vect)
#else
ISR(TIMER1_COMPA_vect)
#endif // CLK_TIMER0
{
	/* Increment 100ms counter */

	count100++;

	/* After 1 sec, increment clktime */

	if(count100 >= 100) {	/* previous was: if(count100 >= 100) */
		clktime++;
		count100 = 0;
	}

	/* check if sleep queue is empty every 100ms */

    if(!isempty(sleepq)) {

			/* sleepq nonempty, decrement the key of */
			/* topmost process on sleepq             */

			if((--queuetab[firstid(sleepq)].qkey) == 0) {

				wakeup();
			}
	}

    /* Decrement the preemption counter */
    /* Reschedule if necessary          */
    if((--preempt) == 0) {
        preempt = QUANTUM;
        resched();
    }
}

