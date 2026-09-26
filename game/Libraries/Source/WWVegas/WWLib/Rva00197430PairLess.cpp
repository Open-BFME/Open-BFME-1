// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

struct Rva00197430Pair
{
	AsciiString first;
	AsciiString second;
};

typedef int Rva00197430Bool;

// ?rva00197430PairLess@@YAHABURva00197430Pair@@0@Z
Rva00197430Bool rva00197430PairLess(
	const Rva00197430Pair &left, const Rva00197430Pair &right)
{
	return left.first.compare( right.first ) < 0
		|| ( !( right.first.compare( left.first ) < 0 )
			&& left.second.compare( right.second ) < 0 );
}
