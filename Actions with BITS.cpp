#define ISBIT(x,pos)	( ( (x) & ( 0x1 << (pos) ) ) != 0 )
#define GETBIT(x,pos)	( (x) & ( 0x1 << (pos) ) )
#define GETBITS(x,y,pos)	( (x) & ( y << (pos) ) )
#define SETBIT(x,pos)	( (x) |= ( 0x1 << (pos) ) )
#define UNSETBIT(x,pos)	( (x) &= (~( 0x1 << (pos) ) ) )
#define SETBITS(x,y,pos)	( (x) |= ( y << (pos) ) )
#define UNSETBITS(x,y,pos)	( (x) &= (~( y << (pos) ) ) )

int XX = 0;
::std::cout << "0XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;

int RES = 0;
SETBIT(XX, 5);
RES = ISBIT(XX, 5);
::std::cout << "1XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;
::std::cout << "1RES - " << ::std::bitset<sizeof(decltype(RES)) * 8>(RES) << ::std::endl;
UNSETBIT(XX, 5);
RES = ISBIT(XX, 5);
::std::cout << "1XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;
::std::cout << "1RES - " << ::std::bitset<sizeof(decltype(RES)) * 8>(RES) << ::std::endl;

RES = 0;
SETBIT(XX, 7);
RES = GETBIT(XX, 7);
::std::cout << "2XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;
::std::cout << "2RES - " << ::std::bitset<sizeof(decltype(RES)) * 8>(RES) << ::std::endl;
UNSETBIT(XX, 7);
RES = GETBIT(XX, 7);
::std::cout << "2XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;
::std::cout << "2RES - " << ::std::bitset<sizeof(decltype(RES)) * 8>(RES) << ::std::endl;

RES = 0;
SETBITS(XX, 0b111, 25);
RES = GETBITS(XX, 0b111, 25);
::std::cout << "3XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;
::std::cout << "3RES - " << ::std::bitset<sizeof(decltype(RES)) * 8>(RES) << ::std::endl;
UNSETBITS(XX, 0b111, 25);
RES = GETBITS(XX, 0b111, 25);
::std::cout << "3XX - " << ::std::bitset<sizeof(decltype(XX)) * 8>(XX) << ::std::endl;
::std::cout << "3RES - " << ::std::bitset<sizeof(decltype(RES)) * 8>(RES) << ::std::endl;
