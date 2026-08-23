/* meminit.c - meminit */

#include <xinu.h>

extern uint8_t __bss_end;

void	*minheap;	/* Start address of heap	*/
void	*maxheap;	/* End address of heap		*/

/*------------------------------------------------------------------------
 * meminit - Initialize the free memory list for BeagleBone Black
 *------------------------------------------------------------------------
 */

void	meminit(void)
{
	struct	memblk *memptr;	/* Memory block pointer	*/

	/* Initialize the minheap and maxheap variables */

    minheap = &__bss_end+1;
	maxheap = (void *)(RAMEND - NULLSTK);	/* AVR atmega328p stack pointer when booting */
											/* QUITAMOS 16 bytes para workaround */

	/* Initialize the memory list as one big block */

	memlist.mnext = (struct memblk *)minheap;
	memptr = memlist.mnext;

	memptr->mnext = (struct memblk *)NULL;
	memlist.mlength = memptr->mlength =
		(uint16_t)maxheap - (uint16_t)minheap;
}
