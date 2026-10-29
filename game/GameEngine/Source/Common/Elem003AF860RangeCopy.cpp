// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: STLport random-access __copy for the 32-byte Elem003AF860 records,
// retail 0x003AEBB0, 117 bytes, reached through ILT 0x00011B8F from the matched
// vector<Elem003AF860>::erase (0x003AF860, PAVectorEraseRangeFamily003AF.cpp)
// and from 0x003AF430. The element class name stays the erase family's
// address-derived placeholder (its real name is unproven).
//
// Layout from the copy: a vptr (never assigned), AsciiString +0x04, an 8-byte
// two-dword aggregate +0x08, a byte +0x10, AsciiStrings +0x14/+0x18 and a dword
// +0x1C. The +0x08 aggregate is material: both cursors are biased to it
// (lea esi/edi,[p+8]) and the result end is computed up front.

#include <algorithm>

#include "ascii_string.h"

struct Elem003AF860Pair
{
	int m_value00;
	int m_value04;
};

struct Elem003AF860
{
	virtual ~Elem003AF860();
	AsciiString m_name04;
	Elem003AF860Pair m_pair08;
	bool m_flag10;
	AsciiString m_name14;
	AsciiString m_name18;
	int m_value1c;
};

namespace _STL
{
	template Elem003AF860 *__copy<Elem003AF860 *, Elem003AF860 *, int>(
		Elem003AF860 *, Elem003AF860 *, Elem003AF860 *,
		const random_access_iterator_tag &, int *);
}
