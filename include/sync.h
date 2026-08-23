#include <xinu.h>

#ifndef _SYNC_H
#define _SYNC_H 

extern char semaforo[];

void sync_wait(uint8_t n);
void sync_signal(uint8_t n);
void sync_set(uint8_t n, char v);

#endif

