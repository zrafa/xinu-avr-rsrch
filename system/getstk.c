/* getstk.c - getstk */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getstk  -  Allocate stack memory, returning highest word address
 *------------------------------------------------------------------------
 */
uint8_t  	*getstk(
	  size_t	nbytes		/* Size of memory requested	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*prev, *curr;	/* Walk through memory list	*/
	struct	memblk	*fits, *fitsprev; /* Record block that fits	*/

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (uint8_t *)SYSERR;
	}

	nbytes = (uint16_t) roundmb(nbytes);	/* Use mblock multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	fits = NULL;
	fitsprev = NULL;  /* Just to avoid a compiler warning */

	while (curr != NULL) {			/* Scan entire list	*/
		if (curr->mlength >= nbytes) {	/* Record block address	*/
			fits = curr;		/*   when request fits	*/
			fitsprev = prev;
		}
		prev = curr;
		curr = curr->mnext;
	}

	if (fits == NULL) {			/* No block was found	*/
		restore(mask);
		return (uint8_t *)SYSERR;
	}
	if (nbytes == fits->mlength) {		/* Block is exact match	*/
		fitsprev->mnext = fits->mnext;
	} else {				/* Remove top section	*/
		fits->mlength -= nbytes;
		fits = (struct memblk *)((uint16_t)fits + fits->mlength);
	}
	memlist.mlength -= nbytes;
	restore(mask);
	return (uint8_t *)((uint16_t) fits + nbytes - sizeof(uint16_t));
}
