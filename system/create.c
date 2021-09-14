/* create.c - create, newpid */

#include <stdarg.h>
#include <xinu.h>

local	pid32 newpid();

/*------------------------------------------------------------------------
 *  create  -  create a process to start running a procedure
 *------------------------------------------------------------------------
 */
pid32	create(
	  int		(*procaddr)(),	/* procedure address		*/
	  int	ssize,		/* stack size in bytes		*/
	  int		priority,	/* process priority > 0		*/
	  char		*name,		/* name (for debugging)		*/
	  int	nargs,		/* number of args that follow	*/
	  ...
	)
{
	intmask 	mask;    	/* interrupt mask		*/
	pid32		pid;		/* stores new process id	*/
	struct	procent	*prptr;		/* pointer to proc. table entry */
	int i;
	char		*saddr;		/* stack address		*/

	mask = disable();
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (size_t)roundmb(ssize);
	if (((saddr = (char *)getstk(ssize)) ==
	     (char *)SYSERR ) ||
	     (pid=newpid()) == SYSERR || priority < 1 ) {
		restore(mask);
		return SYSERR;
	}
	
	prcount++;
	prptr = &proctab[pid];

	/* initialize process table entry for new process */
	prptr->prstate = PR_SUSP;	/* initial state is suspended	*/
	prptr->prprio = priority;
	prptr->prstkbase = (char *)saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=name[i])!=NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE;

	int * a = (int *)(&nargs + 1);
    stackinit(prptr, saddr, procaddr, nargs, a);


	restore(mask);
	return pid;
}

/*------------------------------------------------------------------------
 *  newpid  -  Obtain a new (free) process ID
 *------------------------------------------------------------------------
 */
local	pid32	newpid(void)
{
	uint32	i;			/* iterate through all processes*/
//	static	pid32 nextpid = 1;	/* position in table to try or	*/
	static	pid32 nextpid = 0;	/* position in table to try or	*/
					/*  one beyond end of table	*/

	/* check all NPROC slots */

	for (i = 0; i < NPROC; i++) {
		nextpid %= NPROC;	/* wrap around to beginning */
		if (proctab[nextpid].prstate == PR_FREE) {
			return nextpid++;
		} else {
			nextpid++;
		}
	}
	return (pid32) SYSERR;
}
