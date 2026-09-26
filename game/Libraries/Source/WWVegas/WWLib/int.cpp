// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include	"always.h"
#include	"int.h"
#include	"mpmath.h"
#include	"rng.h"

int bignum::Error = 0;
bool bignum::Carry = false;
bool bignum::Borrow = false;
bignum bignum::Remainder;


//BigInt Gcd(const BigInt & a, const BigInt & n);
#ifdef _MSC_VER
BigInt Generate_Prime(RandomNumberGenerator & rng, int pbits, BigInt const * dummy);
#endif

