#define GETBIT(x,pos)	( ( (x) & ( 0x1 << (pos) ) ) != 0 )
#define SETBIT(x,pos)	( (x) |= ( 0x1 << (pos) ) )
#define UNSETBIT(x,pos)	( (x) &= ~( 0x1 << (pos) ) ) )
