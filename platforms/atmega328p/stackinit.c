#include <xinu.h>
/* avr specific */
#define	MAGIC		0xaa	/* unusual value for top of stk	*/


void stackinit(struct procent *prptr, unsigned char *saddr, int (*procaddr)(), int	nargs, int *a)
{
	int i;

	/* Initialize stack as if the process was called		*/
	*saddr-- = (char)MAGIC;		/* Bottom of stack */

	prptr->pargs = nargs;

	for (i=0 ; i<PNREGS ; i++)		// VER TAMANIO PARA AVR
		prptr->pregs[i] = INITREG;
	
	prptr->paddr = (int *)procaddr;

	prptr->pregs[SPC_L] = lobyte((unsigned) procaddr); // GUARDAR SPC_L
	prptr->pregs[SPC_H] = hibyte((unsigned) procaddr);
	prptr->pregs[SSREG] = INITPS;
	// POR AHORA NO  (usado en kill.c en avr orig : prptr->pnxtkin = BADPID;
	// POR AHORA NO prptr->pdevs[0] = prptr->pdevs[1] = BADDEV;
	
	/* machine/compiler dependent pass arguments to created process */
	prptr->pregs[24] = lobyte((unsigned)prptr->pargs);	/*r24*/
	prptr->pregs[25] = hibyte((unsigned)prptr->pargs);
	prptr->pregs[22] = lobyte((unsigned)&prptr->parg[0]);	/*r22*/
	prptr->pregs[23] = hibyte((unsigned)&prptr->parg[0]);

	*saddr-- = lobyte((unsigned)INITRET);	/* push on initial return address*/
	*saddr-- = hibyte((unsigned)INITRET);
	*saddr-- = lobyte((unsigned)procaddr);	/* push on procedure address	*/
	*saddr-- = hibyte((unsigned)procaddr);
	prptr->pregs[SSP_L] = lobyte((unsigned) saddr);
	prptr->pregs[SSP_H] = hibyte((unsigned) saddr);

	for (i = 0; i < nargs; i++) {
		prptr->parg[i] = (int) *a++;
	}
	prptr->parg[nargs] = 0;
	
}


