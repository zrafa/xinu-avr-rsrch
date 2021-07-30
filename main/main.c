/*  main.c  - main */

/* Basic Xinu app for quick start */

#include <xinu.h>
#include <avr/io.h>

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

process example0(int nargs, char *args[])
{
    char *buf = args[0];
    int i = 0;
    char ch;

    for (;;)
    {
        ch = buf[i++];
        if (ch == '\0') {
            usartsendbyte('\r');
            usartsendbyte('\n');
            break;       
        }
        usartsendbyte(ch);

        sleep(10);
    }

	return OK;
}

process	main(void)
{
    usartinit();

	/* We create() a new process. Arguments:
	 *         process code: example0()
	 *         stack size: 128 bytes
	 *         priority: 50
	 * 	   name: "ex0"
	 *         arguments: 2
	 * 	   first argument: 3 (int)
	 * 	   second argument: "hello world"
	 */

	resume(create(example0, 128, 50, "ex_0", 1, "hello world"));

	/* Wait for example0 to exit */

	receive();

	return OK;
}
