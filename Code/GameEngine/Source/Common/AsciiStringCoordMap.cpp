// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: map<AsciiString, Coord3D>'s tree copy, _M_copy at 0x000BFF50,
// 171 bytes. The name was parked on the 5-byte thunk at 0x0002E15E, which
// jumps here.
//
// A copy walks the source tree and never compares, so AsciiString needs no
// more than its size here.
//
// The node is 0x20 bytes -- sixteen of header and sixteen of value, which is
// AsciiString's pointer plus Coord3D's three Reals -- and the value is built by
// an out-of-line _Construct call rather than inline stores, which is what this
// build does for every element type that is not a pointer.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	// Only the size matters here: the comparison is a call, not inline code.
	void *m_data;
};

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
// Not inlined in this build: the pair is built through a call.
template <>
void _Construct(pair<const AsciiString, Coord3D> *p, const pair<const AsciiString, Coord3D> &val);
}

typedef _STL::map<AsciiString, Coord3D> BfmeCoordMap;

void BfmeAsciiStringCoordMapAnchor(BfmeCoordMap &out, const BfmeCoordMap &in)
{
	out = in;
}
