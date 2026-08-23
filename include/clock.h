/* clock.h */

extern	volatile uint16_t	clktime;	/* current time in secs since boot		*/
extern  volatile uint16_t  count1000; /* ms since last clock tick             */

extern	volatile qid16	sleepq;		/* queue for sleeping processes			*/
extern	int16_t	slnonempty;			/* nonzero if sleepq is nonempty		*/
extern	int16_t	*sltop;				/* ptr to key in first item on sleepq	*/
extern	volatile uint16_t	preempt;	/* preemption counter					*/

