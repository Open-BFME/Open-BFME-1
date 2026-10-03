// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: the out-of-line STLport _Construct<T,T> at retail 0x003A9110.
//
// The payload type is deliberately anonymous and address-derived: the bytes
// prove a LAYOUT and a LIFECYCLE (a vptr at +0 written as an immediate, and a
// 4-byte member at +4 whose copy constructor is called out of line at the
// retail StringBase<char> copy constructor), never a class identity. Its only
// retail caller is the 8-byte-payload vector push_back at 0x003B1000, which
// game/gen_small/tgrid_113.cpp already carries under the same convention.

#include <memory>

// The 4-byte member at +4 is copied out of line at retail 0x00887B60, the
// StringBase<char> copy constructor the ledger owns as
// ??0?$StringBase@D@@AAE@ABV0@@Z (game/Libraries/Source/string/StringBase.cpp).
// AsciiString's copy constructor is inline and calls exactly that base
// constructor, which is the shape retail's copy sites emit, so the member is
// the real AsciiString rather than a TU-local stand-in.
#include "ascii_string.h"

// 8-byte polymorphic payload: vptr at +0 (the immediate 0x010EC76C, the
// Rva003B7BA0Record vftable), the member above at +4.
struct Gen_t_003a9110_p8vs
{
	// Only shapes the vtable; retail never calls it, so it stays inline and
	// emits no external reference.
	virtual void gen_v0() {}
	AsciiString m_str;
};

template void _STL::_Construct<Gen_t_003a9110_p8vs, Gen_t_003a9110_p8vs>(
	Gen_t_003a9110_p8vs *, const Gen_t_003a9110_p8vs &);
