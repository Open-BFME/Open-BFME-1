// Open-BFME5 conversions.

// The string field setter this body calls is retail 0x00887C90, defined as
// StringBase<char>::set (game/Libraries/Source/WWVegas/WWLib/string_base.h).
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef StringBase<char> BfmeStrVOX;

struct BfmeElemVOX
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	BfmeStrVOX m_bfme0c;
};

BfmeElemVOX *bfmeCopyBackVOX(const BfmeElemVOX *first, const BfmeElemVOX *last, BfmeElemVOX *dest)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			--last;
			--dest;
			dest->m_bfme00 = last->m_bfme00;
			dest->m_bfme04 = last->m_bfme04;
			dest->m_bfme08 = last->m_bfme08;
			dest->m_bfme0c.set(last->m_bfme0c);
		} while (--i);
	}
	return dest;
}
