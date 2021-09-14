/*  main.c  - main */

/* Basic Xinu app for quick start */

#include <xinu.h>
#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

typedef struct
{
  uint8 UCSRA;        // USART Control and Status Register A,     offset: 0x00
  uint8 UCSRB;        // USART Control and Status Register B,     offset: 0x01
  uint8 UCSRC;        // USART Control and Status Register C,     offset: 0x02
  uint8 RES1;         // Reserved                                 offset: 0x03
  uint8 UBRRL;        // USART Baud Rate Register Low Byte        offset: 0x04
  uint8 UBRRH;        // USART Baud Rate Register High Byte       offset: 0x05
  uint8 UDR;          // USART I/O Data Register,                 offset: 0x06
} USART_t;

volatile USART_t*       const usart0       = (USART_t*)0xC0;

void usartinit(void)
{
    // Set baud rate
    usart0->UBRRH = (uint8)(UBRR_VALUE >> 8);
    usart0->UBRRL = (uint8)UBRR_VALUE;
    // Set frame format to 8 data bits, no parity, 1 stop bit
    usart0->UCSRC |= (1 << UCSZ01) | (1 << UCSZ00);
    //enable transmission and reception
    usart0->UCSRB |= (1 << RXEN0) | (1 << TXEN0);
}

void usartsendbyte(uint8 data)
{
    //wait while previous byte is completed
    while(!(usart0->UCSRA & (1 << UDRE0))) {};
    // Transmit data
    usart0->UDR = data;
}

uint8 usartreceivebyte()
{
    // Wait for byte to be received
    while(!(usart0->UCSRA & (1 << RXC0))) {};
    // Return received data
    return usart0->UDR;
}

/*------------------------------------------------------------------------
 * kputc - use polled I/O to write a character to the console serial line
 *------------------------------------------------------------------------
 */
syscall kputc(
	  byte	c			/* character to write		*/
	)
{
	intmask mask;

	mask = disable();

	if (c == '\n')
		usartsendbyte('\r');
	usartsendbyte(c);

	restore(mask);
	return OK;
}

/*------------------------------------------------------------------------
 * kprintf  -  use polled I/O to print formatted output on the console
 *------------------------------------------------------------------------
 */
syscall kprintf(char *fmt, ...)
{
	va_list ap;
	char output[81];
	char *c;

	memset(output, 0, 81);
	va_start(ap, fmt);
	vsnprintf(output, 80, fmt, ap);
	va_end(ap);

	c = output;
	while(*c) {
		kputc(*c);
		c++;
	};

        return OK;
}

#define BLKSIZE MINSTK

extern struct	memblk	memlist;	/* List of free memory blocks		*/

process	main(void)
{
    usartinit();

    char *addr1;
    char *addr2;
    char *saddr1;
    char *saddr2;

    kprintf("--------------------------------------------------------------\n");
    kprintf("--------------------------------------------------------------\n");
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Get mem - size: %d\n", BLKSIZE);
    addr1 = getmem(BLKSIZE);
    kprintf("addr1: %X\n", (addr_t)addr1);
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Get mem - size: %d\n", BLKSIZE);
    addr2 = getmem(BLKSIZE);
    kprintf("addr2: %X\n", (addr_t)addr2);
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Free mem - addr1: %X size: %d\n", (addr_t)addr1, BLKSIZE);
    if (freemem(addr1, BLKSIZE) == SYSERR) {
        kprintf("Error\n");
        return 1;
    }
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Get stack - size: %d\n", BLKSIZE);
    saddr1 = getstk(BLKSIZE);
    kprintf("saddr1: %X\n", (addr_t)saddr1);
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Get stack - size: %d\n", BLKSIZE);
    saddr2 = getstk(BLKSIZE);
    kprintf("saddr2: %X\n", (addr_t)saddr2);
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Free stack - saddr1: %X size: %d\n", (addr_t)saddr1, BLKSIZE);
    freestk(saddr1, BLKSIZE);
    kprintf("Free mem: %d\n\n", memlist.mlength);


    kprintf("Free stack - saddr2: %X size: %d\n", (addr_t)saddr2, BLKSIZE);
    freestk(saddr2, BLKSIZE);
    kprintf("Free mem: %d\n\n", memlist.mlength);

    kprintf("Free mem - addr2: %X size: %d\n", (addr_t)addr2, BLKSIZE);
    if (freemem(addr2, BLKSIZE) == SYSERR) {
        kprintf("Error\n");
        return 1;
    }
    kprintf("Free mem: %d\n", memlist.mlength);

	return OK;
}
