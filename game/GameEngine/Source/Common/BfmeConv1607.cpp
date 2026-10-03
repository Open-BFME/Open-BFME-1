// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

// The element's vtable is retail's 0x010EC784, named by the pin
// `??_7BfmeEntVTB@@6B@` (symbols.csv). The slot-0 body it points at is the
// five-byte ILT thunk at 0x000389AB, `?j_000389ab@@YAXXZ` in
// game/gen_small/gthunks_063.cpp; declaring the virtual here would leave that
// slot unresolved, so the element keeps the vftable as the data reference
// BfmeConv1325.cpp and BfmeConv1772.cpp use.
extern "C" void *__identifier("??_7BfmeEntVTB@@6B@")[];

// The 8-byte member at +0x0C is retail's AsciiString: the inline AsciiString
// copy constructor forwards straight to StringBase<char>'s copy body at
// 0x00887B60, which game/Libraries/Source/string/StringBase.cpp defines as
// `??0?$StringBase@D@@AAE@ABV0@@Z` (see ascii_string.h).
class BfmeEntVTB
{
public:
	__forceinline BfmeEntVTB(const BfmeEntVTB &other)
		: m_bfmeVft(__identifier("??_7BfmeEntVTB@@6B@")),
		  m_bfme04(other.m_bfme04), m_bfme08(other.m_bfme08),
		  m_bfme0c(other.m_bfme0c), m_bfme10(other.m_bfme10)
	{
	}

	void *m_bfmeVft;
	int m_bfme04;
	int m_bfme08;
	AsciiString m_bfme0c;
	char m_bfme10;
};

void bfmeConstructVTB(BfmeEntVTB *dest, const BfmeEntVTB *source)
{
	new (dest) BfmeEntVTB(*source);
}