/* clock.h */

extern	uint32	clktime;	/* current time in secs since boot	*/
extern  volatile uint32  count100;      /* 10 ms since last clock tick             */

extern	qid16	sleepq;		/* queue for sleeping processes		*/
extern	int32	slnonempty;	/* nonzero if sleepq is nonempty	*/
extern	uint32	preempt;	/* preemption counter			*/

