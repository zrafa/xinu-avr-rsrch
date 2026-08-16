#include <xinu.h>
#include "serial.h"

/*------------------------------------------------------------------------
 *  _prtl10  -  Converts int to base 10 string.
 *------------------------------------------------------------------------
 */
static void	_prtl10(int num, char *str)
{
    int i;
    char temp[11];

    temp[0] = '\0';
    temp[1] = ((num<0) ? -(num%10) : (num%10)) + '0';
    num /= (num<0) ? -10 : 10;
    for (i = 2; i <= 10; i++) {
        temp[i] = num % 10 + '0';
        num /= 10;
    }
    for (i = 10; temp[i] == '0'; i--);
    if (i == 0)
        i++;
    while (i >= 0)
        *str++ = temp[i--];
}

/*------------------------------------------------------------------------
 *  _prtl16  -  Converts int to lowercase hex string.
 *------------------------------------------------------------------------
 */
static void	_prtl16(
		  int		num,
		  char		*str
		)
{
    int i;
    char temp[9];

    temp[0] = '\0';
    for (i = 1; i <= 4; i++)
    {
        temp[i] = "0123456789abcdef"[num & 0x0F];
        num = num >> 4;
    }
    for (i = 4; temp[i] == '0'; i--);
    if (i == 0)
        i++;
    while (i >= 0)
        *str++ = temp[i--];
}


int main(void)
{
    pid16 pid;
    char buf[8];
	struct procent *prptr;

	serial_init();

    serial_put_str((char *)__func__);
    serial_put_str("\r\n");

    pid = getpid();
    serial_put_str("pid ");
    _prtl10(pid, buf);
    serial_put_str(buf);
    serial_put_str("\r\n");

	prptr = &proctab[pid];
    pid = prptr->prparent;
    serial_put_str("parent pid ");
    _prtl10(pid, buf);
    serial_put_str(buf);
    serial_put_str("\r\n");

	prptr = &proctab[pid];
    serial_put_str("parent name ");
    serial_put_str(prptr->prname);
    serial_put_str("\r\n");

	while(1) {
	}

	return 0;
}

