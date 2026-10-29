// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: STLport random-access __copy<const T *, T *> for the 32-byte
// Gen_t_003b55d0_p32cd records (the element of ProductionPrerequisite-owner's
// vector at +0x2C in Rva003B6680Assign.cpp), retail 0x003B33C0, 117 bytes,
// reached through ILT 0x000325D3 from that vector's operator= (0x003B55D0) and
// from 0x003B3C90; the symbols.csv pin carries this decorated name. The element
// keeps the generator's address-derived type name.
//
// Same record shape and code as the Elem003AF860 copy at 0x003AEBB0: a vptr
// (never assigned), strings at +0x04/+0x14/+0x18, a two-dword aggregate at
// +0x08 (both cursors are biased to it), a byte at +0x10 and a dword at +0x1C.

#include <algorithm>

#include "ascii_string.h"

struct Gen_t_003b55d0_p32cdPair
{
	int m_value00;
	int m_value04;
};

struct Gen_t_003b55d0_p32cd
{
	virtual ~Gen_t_003b55d0_p32cd();
	AsciiString m_name04;
	Gen_t_003b55d0_p32cdPair m_pair08;
	bool m_flag10;
	AsciiString m_name14;
	AsciiString m_name18;
	int m_value1c;
};

namespace _STL
{
	template Gen_t_003b55d0_p32cd *__copy<const Gen_t_003b55d0_p32cd *, Gen_t_003b55d0_p32cd *, int>(
		const Gen_t_003b55d0_p32cd *, const Gen_t_003b55d0_p32cd *, Gen_t_003b55d0_p32cd *,
		const random_access_iterator_tag &, int *);
}
