/*  main.c  - main */

/* Basic Xinu app for quick start */

#include <xinu.h>


process example0(int nargs, char *args[])
{
//    char *buf = args[0];

	return OK;
}

process	main(void)
{
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
