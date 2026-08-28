// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: list<Coord3D>::_M_insert_dispatch over a const-iterator range,
// retail 0x000BF260, 75 bytes. The name was parked on a 5-byte thunk.
//
// STLport's own body out of the real header: one 0x14-byte node per source
// element -- two link pointers and the three Reals -- linked in front of the
// position. Unlike the pointer-element list, the value goes in through an
// out-of-line _Construct, which is what this build does for every element type
// that is not a pointer.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

namespace _STL
{
template <>
void _Construct(Coord3D *p, const Coord3D &val);
}

void BfmeCoord3DListInsertAnchor(_STL::list<Coord3D> &dst, _STL::list<Coord3D>::iterator where, const _STL::list<Coord3D> &src)
{
	dst.insert(where, src.begin(), src.end());
}
