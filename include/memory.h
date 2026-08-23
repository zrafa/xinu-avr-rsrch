/* memory.h - roundmb, truncmb, freestk */

/*----------------------------------------------------------------------
 * roundmb, truncmb - Round or truncate address to memory block size
 *----------------------------------------------------------------------
 */
#define	roundmb(x)	(char *)( (3 + (uint16_t)(x)) & (~3) )
#define	truncmb(x)	(char *)( ((uint16_t)(x)) & (~3) )

/*----------------------------------------------------------------------
 *  freestk  --  Free stack memory allocated by getstk
 *----------------------------------------------------------------------
 */
#define	freestk(p,len)	freemem((char *)((uint16_t)(p)		\
				- ((uint16_t)roundmb(len))	\
				+ (uint16_t)sizeof(uint16_t)),	\
				(uint16_t)roundmb(len) )

struct	memblk	{					/* See roundmb & truncmb		*/
	struct	memblk	*mnext;			/* Ptr to next free memory blk	*/
	uint16_t	mlength;				/* Size of blk (includes memblk)*/
	};
extern	struct	memblk	memlist;	/* Head of free memory list		*/
extern	void	*minheap;			/* Start of heap				*/
extern	void	*maxheap;			/* Highest valid heap address	*/
/* RAFA */
extern uint16_t  free_mem;            /* Total amount of free memory  */
/* FIN de RAFA */


