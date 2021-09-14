/* memory.h - roundmb, truncmb, freestk */

/*----------------------------------------------------------------------
 * roundmb, truncmb - Round or truncate address to memory block size
 *----------------------------------------------------------------------
 */
#define	roundmb(x)	(char *)( ((sizeof(struct memblk)-1) 			\
                  + (addr_t)(x)) & (~(sizeof(struct memblk)-1)) )
#define	truncmb(x)	(char *)( ((addr_t)(x)) & (~(sizeof(struct memblk)-1)) )

/*----------------------------------------------------------------------
 *  freestk  --  Free stack memory allocated by getstk
 *----------------------------------------------------------------------
 */

struct	memblk	{					/* See roundmb & truncmb			*/
	struct	memblk	*mnext;			/* Ptr to next free memory blk		*/
	size_t	mlength;				/* Size of blk (includes memblk)	*/
	};

#define	freestk(p,len)	freemem((char *)((addr_t)(p)		\
				- ((addr_t)roundmb(len))					\
				+ (addr_t)sizeof(addr_t)),					\
				(addr_t)roundmb(len) )

extern	struct	memblk	memlist;	/* Head of free memory list			*/
extern	void	*minheap;			/* Start of heap					*/
extern	void	*maxheap;			/* Highest valid heap address		*/
