/* clkinit.c */

#include <xinu.h>

uint32	clktime;		/* Seconds since boot			*/
unsigned long  count1000;	/* ms since last clock tick             */
qid16	sleepq;			/* Queue of sleeping processes		*/
unsigned long preempt;		/* Preemption counter			*/

/*------------------------------------------------------------------------
 * clkinit  -  Initialize the clock and sleep queue at startup
 *------------------------------------------------------------------------
 */
void clkinit(void)
{
	sleepq = newqueue();	/* Allocate a queue to hold the delta	*/
				/*   list of sleeping processes		*/
	preempt = QUANTUM;	/* Set the preemption time		*/
	clktime = 0;		/* Start counting seconds		*/
    count1000 = 0;

	return;
}

