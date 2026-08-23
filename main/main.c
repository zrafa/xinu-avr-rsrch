#include <xinu.h>

#include "serial.h"
#include "adc.h"

void motors(void);

void main(void)
{
    size_t count = 0;
    
    adc_init();
    
    serial_init();
    
    serial_put_str("Hello World!\r\n");
    
    resume(create(motors, 128, 20, "motors", 0));

    while (1) {
        serial_put_int(count++, 4);
        serial_put_str("\r\n");
        sleepms(500);
    }
}
