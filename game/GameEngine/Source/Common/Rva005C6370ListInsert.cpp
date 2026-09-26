// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: list<Rva005C5580Element>::_M_insert_dispatch over a
// const-iterator range, retail 0x005C6370, 75 bytes. Twin of 0x000BF260
// (Coord3DListInsert.cpp) with a different 12-byte element and a different
// pinned _Construct callee (0x00030549 -> Rva005C5580Element).
// Address-derived element — owning type is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef float Real;

struct Rva005C5580Element
{
	Real x;
	Real y;
	Real z;
};

namespace _STL
{
template <>
void _Construct(Rva005C5580Element *p, const Rva005C5580Element &val);
}

void Rva005C6370ListInsertAnchor(
	_STL::list<Rva005C5580Element> &dst,
	_STL::list<Rva005C5580Element>::iterator where,
	const _STL::list<Rva005C5580Element> &src)
{
	dst.insert(where, src.begin(), src.end());
}
