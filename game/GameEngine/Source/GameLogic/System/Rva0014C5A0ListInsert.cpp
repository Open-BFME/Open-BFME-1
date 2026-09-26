// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: list<Rva0014C4C0Element>::_M_insert_dispatch over a
// const-iterator range, retail 0x0014C5A0, 75 bytes. Twin of 0x00379C60
// (CrateCreationEntryListInsert.cpp) with a different 8-byte element and a
// different pinned _Construct callee (0x0004031D).
// Address-derived element — owning type is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0014C4C0Element
{
	void *m_a;
	unsigned m_b;
};

namespace _STL
{
template <>
void _Construct(Rva0014C4C0Element *p, const Rva0014C4C0Element &value);
}

void Rva0014C5A0ListInsertAnchor(
	_STL::list<Rva0014C4C0Element> &destination,
	_STL::list<Rva0014C4C0Element>::iterator where,
	const _STL::list<Rva0014C4C0Element> &source)
{
	destination.insert(where, source.begin(), source.end());
}
