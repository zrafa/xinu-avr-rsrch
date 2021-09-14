/* freemem.c - freemem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  freemem  -  Free a memory block, returning the block to the free list
 *------------------------------------------------------------------------
 */
syscall	freemem(
	  char		*blkaddr,	/* Pointer to memory block	*/
	  size_t	nbytes		/* Size of block in bytes	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*next, *prev, *block;
	addr_t	top;

	mask = disable();
	if ((nbytes == 0) || ((addr_t) blkaddr < (addr_t) minheap)
			  || ((addr_t) blkaddr > (addr_t) maxheap)) {
		restore(mask);
		return SYSERR;
	}

	nbytes = (size_t) roundmb(nbytes);	/* Use memblk multiples	*/
	block = (struct memblk *)blkaddr;

	prev = &memlist;			/* Walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	if (prev == &memlist) {		/* Compute top of previous block*/
		top = (addr_t) NULL;
	} else {
		top = (addr_t) prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (addr_t) block < top)
	    || ((next != NULL)	&& (addr_t) block+nbytes>(addr_t)next)) {
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (addr_t) block) { 	/* Coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	} else {			/* Link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((addr_t) block + block->mlength) == (addr_t) next) {
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
	restore(mask);
	return OK;
}
