/* create.c - create, newpid */

#include <xinu.h>
#include <stdarg.h>

local	pid16 newpid();
 
pid16 create(
		void * funcaddr,	/* Address of the function		*/
		size_t ssize,		/* Stack size 					*/
		pri16 priority,		/* Process priority > 0			*/
		char *name,			/* Name (for debugging)			*/
		size_t nargs,		/* Number of args that follow	*/
		...
	  )
{
	intmask 	mask;    	/* interrupt mask				*/
	pid16 pid;				/* Stores new process id		*/
	struct	procent	*prptr;	/* pointer to proc. table entry */
	int i;
	uint8_t		*saddr;		/* stack address				*/

	mask = disable();
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (size_t)roundmb(ssize);
	if (((saddr = getstk(ssize)) ==
	     (uint8_t *)SYSERR ) ||
	     (pid=newpid()) == SYSERR || priority < 1 ) {
		restore(mask);
		return SYSERR;
	}

	prcount++;
	prptr = &proctab[pid];

	/* initialize process table entry for new process */
	prptr->prstate = PR_SUSP;	/* initial state is suspended	*/
	prptr->prprio = priority;
	prptr->prstkbase = saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=name[i])!=NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid16)getpid();
	prptr->prhasmsg = FALSE;

	/* Initialize stack as if the process was called		*/

	int * a = (int *)(&nargs + 1);
    prptr->prstkptr = (uint8_t *)stkinit(saddr, funcaddr, nargs, a);
	restore(mask);
	return pid;
}

/*------------------------------------------------------------------------
 *  newpid  -  Obtain a new (free) process ID
 *------------------------------------------------------------------------
 */
local	pid16	newpid(void)
{
	int	i;						/* iterate through all processes	*/
	static	pid16 nextpid = 1;	/* position in table to try or		*/
								/*  one beyond end of table			*/

	/* check all NPROC slots */

	for (i = 0; i < NPROC; i++) {
		nextpid %= NPROC;		/* wrap around to beginning 		*/
		if (proctab[nextpid].prstate == PR_FREE) {
			return nextpid++;
		} else {
			nextpid++;
		}
	}
	return (pid16) SYSERR;
}
