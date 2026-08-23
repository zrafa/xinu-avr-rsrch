#include <xinu.h>
#include <avr/interrupt.h>

char semaforo[4];

void sync_set(uint8_t n, char v)
{
	uint8_t x;

	x = disable();
	semaforo[n] = v;
	restore(x);
}

void sync_wait(uint8_t n)
{
	uint8_t x;

	inicio:
	x = disable();
	if (semaforo[n] <= 0) {
		restore(x);
		sleepms(1);
		goto inicio;
	} 
	semaforo[n]--;
	restore(x);
}

void sync_signal(uint8_t n)
{
	uint8_t x;

	x = disable();
	semaforo[n]++;
	restore(x);
}
