// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: list<Rva0009F200Element>::_M_insert_dispatch over a
// const-iterator range, retail 0x0009F340, 75 bytes. Twin of 0x000801C0
// (AsciiStringListClear.cpp's list<AsciiString> instantiation) with a
// different 4-byte element and a different pinned _Construct callee
// (0x00026503 -> Rva0009F200Element).
// Address-derived element — owning type is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0009F200Element
{
	void *m_a;
};

namespace _STL
{
template <>
void _Construct(Rva0009F200Element *p, const Rva0009F200Element &val);
}

void Rva0009F340ListInsertAnchor(
	_STL::list<Rva0009F200Element> &dst,
	_STL::list<Rva0009F200Element>::iterator where,
	const _STL::list<Rva0009F200Element> &src)
{
	dst.insert(where, src.begin(), src.end());
}
