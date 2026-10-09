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

class Open2Rec14BBC0;
void Open2Construct14BBC0(Open2Rec14BBC0 *place, const Open2Rec14BBC0 &value);

namespace _STL
{
template <>
__forceinline void _Construct(Rva0014C4C0Element *p, const Rva0014C4C0Element &value)
{
	Open2Construct14BBC0(reinterpret_cast<Open2Rec14BBC0 *>(p),
		reinterpret_cast<const Open2Rec14BBC0 &>(value));
}
}

void Rva0014C5A0ListInsertAnchor(
	_STL::list<Rva0014C4C0Element> &destination,
	_STL::list<Rva0014C4C0Element>::iterator where,
	const _STL::list<Rva0014C4C0Element> &source)
{
	destination.insert(where, source.begin(), source.end());
}
