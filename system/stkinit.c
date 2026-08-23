#include <xinu.h>

#define LO(x) (unsigned char)(x & 0x00FF)
#define HI(x) (unsigned char)((x >> 8) & 0x00FF)

uint8_t *stkinit(uint8_t *saddr, void *funcaddr, size_t nargs, int *a)
{
    int i;
    
    *saddr-- = LO((unsigned int)userret);
    *saddr-- = HI((unsigned int)userret);

    *saddr-- = LO((unsigned int)funcaddr);		
    *saddr-- = HI((unsigned int)funcaddr);
 
    *saddr-- = 0x00;        /* R31  */
    *saddr-- = 0x80;        /* SREG, enable interrupt */		
    *saddr-- = 0x00;        /* R30  */
    *saddr-- = 0x00;        /* R29  */
    *saddr-- = 0x00;        /* R28  */
    *saddr-- = 0x00;        /* R27  */
    *saddr-- = 0x00;        /* R26  */
    *saddr-- = 0x00;        /* R25  */
    *saddr-- = 0x00;        /* R24  */
    *saddr-- = 0x00;        /* R23  */
    *saddr-- = 0x00;        /* R22  */
    *saddr-- = 0x00;        /* R21  */
    *saddr-- = 0x00;        /* R20  */
    *saddr-- = 0x00;        /* R19  */
    *saddr-- = 0x00;        /* R18  */
    *saddr-- = 0x00;        /* R17  */
    *saddr-- = 0x00;        /* R16  */
    *saddr-- = 0x00;        /* R15  */
    *saddr-- = 0x00;        /* R14  */
    *saddr-- = 0x00;        /* R13  */
    *saddr-- = 0x00;        /* R12  */
    *saddr-- = 0x00;        /* R11  */
    *saddr-- = 0x00;        /* R10  */
    *saddr-- = 0x00;        /* R9  */
    int * args = (int *)saddr;
    *saddr-- = 0x00;        /* R8  */
    *saddr-- = 0x00;        /* R7  */
    *saddr-- = 0x00;        /* R6  */
    *saddr-- = 0x00;        /* R5  */
    *saddr-- = 0x00;        /* R4  */
    *saddr-- = 0x00;        /* R3  */
    *saddr-- = 0x00;        /* R2  */
    *saddr-- = 0x00;        /* R1  */
    *saddr-- = 0x00;        /* R0  */

    for (i = 0; i < nargs; i++)
        args[8-i] = a[i];

    return saddr;
}

