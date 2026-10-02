// Open-BFME5 conversions.

// The out-of-line member this TU reaches is the retail body at 0x00887B60,
// StringBase<char>'s copy constructor (StringBase.cpp, 121 bytes).  AsciiString
// is the real class that inherits it -- its copy constructor is inline and
// emits a direct `call StringBase<char>::StringBase`, which is the single call
// retail's bytes carry.  It is four bytes wide, so the member offset below is
// unchanged.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

struct BfmeHeadVTI
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

struct BfmeEntVTI
{
	__forceinline BfmeEntVTI(const BfmeEntVTI &other)
		: m_bfme00(other.m_bfme00), m_bfme18(other.m_bfme18)
	{
	}

	BfmeHeadVTI m_bfme00;
	AsciiString m_bfme18;
};

void bfmeConstructVTI(BfmeEntVTI *dest, const BfmeEntVTI *source)
{
	new (dest) BfmeEntVTI(*source);
}
