/* platdefs.h */

/* avr specific values. Original saved under orig/ folder */

/* General type declarations used throughout the kernel */

typedef	unsigned char       byte;
typedef	unsigned char       uint8;
typedef	long                int32;
typedef	int                 int16;
typedef	unsigned long       uint32;
typedef	unsigned int        uint16;
typedef	unsigned long long  uint64;

typedef unsigned int size_t;
typedef uint8  intmask;        /* saved interrupt mask                 */

#define hibyte(x) (unsigned char)(((int)(x)>>8)&0xff)
#define lobyte(x) (unsigned char)(((int)(x))&0xff)


