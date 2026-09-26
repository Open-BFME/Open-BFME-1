// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Everything that moves Object's status mask at +0x90:
//
//   setStatus     0x001C7370  the one mutator; set or clear a whole mask
//   setStatusBit  0x000D3EB0  build a one-bit mask and forward
//   rva001CE6F0   0x001CE6F0  set bit 73, then store a value at +0x338
//   rva001CE740   0x001CE740  set bit 4,  then store a value at +0x33C
//
// plus the two out-of-line template bodies setStatus' own compiland emits,
// BitFlags<86>::clear (0x001C60B0) and _STL::bitset<86>::operator~ (0x001C4BF0).
//
// The mask is 86 bits in three dwords, and retail says so in the open: every
// clear path sanitises the top word with 0x3FFFFF, which is 22 bits, and
// 64 + 22 = 86.  All four bodies agreed on that much.  What they did not agree on
// was BitFlags itself -- three files, three class definitions, no two alike:
//
//   setStatus     operator!=, set(const BitFlags&), clear(const BitFlags&), test(Int)
//   setStatusBit  a default ctor and set(Int) over bitset::_Unchecked_set
//   rva001CE6F0   a default ctor and a kInit ctor that sets one index
//
// They are one class, defined once in ObjectStatusBits.h with all six members.
// Each body uses the members it needs; MSVC emits a COMDAT only for what is
// used, so merging them adds no body the ledger has no row for.
//
// Object drifted too. setStatus places m_status at +0x90 and reaches
// m_repulsorHelper (+0x1D4) and m_partitionData (+0x3B0); all five members and
// their intervening padding are defined in ObjectStatusBits.h.
//
// The bit indices are retail's, read off the masks the two small bodies build:
// `or eax,0x200` into word 2 is bit 73, `or eax,0x10` into word 0 is bit 4.

#include "ObjectStatusBits.h"

// ?setStatusBit@Object@@QAEXH_N@Z
//
// The single bit goes in with bitset::_Unchecked_set, which is one
// `or [mem],reg`; the checked spelling costs a load, an or and a store.
void Object::setStatusBit(Int bit, Bool set)
{
	ObjectStatusMaskType mask;
	mask.set(bit);
	setStatus(mask, set);
}

// ?rva001CE6F0@Object@@QAEXH@Z
void Object::rva001CE6F0(Int value)
{
	setStatus(MAKE_OBJECT_STATUS_MASK(73), true);
	m_338 = value;
}

// ?rva001CE740@Object@@QAEXH@Z
void Object::rva001CE740(Int value)
{
	setStatus(MAKE_OBJECT_STATUS_MASK(4), true);
	m_33c = value;
}
