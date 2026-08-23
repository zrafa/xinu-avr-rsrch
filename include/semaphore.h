/* semaphore.h - isbadsem */

#ifndef	NSEM
#define	NSEM		4	/* Number of semaphores, if not defined	*/
#endif

/* Semaphore state definitions */

#define	S_FREE	0		/* Semaphore table entry is available	*/
#define	S_USED	1		/* Semaphore table entry is in use	*/

/* Semaphore table entry */
struct	sentry	{
	int8_t	sstate;		/* Whether entry is S_FREE or S_USED	*/
	int16_t	scount;		/* Count for the semaphore		*/
	qid16	squeue;		/* Queue of processes that are waiting	*/
						/*     on the semaphore			*/
};

extern	struct	sentry semtab[];

#define	isbadsem(s)	((int16_t)(s) < 0 || (s) >= NSEM)
