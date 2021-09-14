/* platdefs.h */

/* avr specific values. Original saved under orig/ folder */

/* General type declarations used throughout the kernel */

typedef	unsigned char       byte;
typedef	unsigned char       uint8;
typedef	unsigned long       uint32;
typedef	unsigned int        uint16;
typedef	int                 int16;
typedef	long                int32;

typedef uint16 size_t;
typedef uint16 addr_t;         /* address type          */
typedef uint8  intmask;        /* saved interrupt mask  */

#define hibyte(x) (unsigned char)(((int)(x)>>8)&0xff)
#define lobyte(x) (unsigned char)(((int)(x))&0xff)


