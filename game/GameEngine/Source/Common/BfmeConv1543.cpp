// Open-BFME5 conversions.

// The +4 string member is retail's StringBase<char> (4-byte Header*), and the
// per-element copy at 0x00887C90 is the matched StringBase<char>::set body
// (StringBase.cpp), so this TU calls that body under its own name.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeElemVOS
{
	char m_bfme00;
	char m_bfmePad01[3];
	StringBase<char> m_bfme04;
	int m_bfme08;
};

BfmeElemVOS *bfmeCopyBackVOS(const BfmeElemVOS *first, const BfmeElemVOS *last, BfmeElemVOS *dest)
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
			dest->m_bfme04.set(last->m_bfme04);
			dest->m_bfme08 = last->m_bfme08;
		} while (--i);
	}
	return dest;
}
