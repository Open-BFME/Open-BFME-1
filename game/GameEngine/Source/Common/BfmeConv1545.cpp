// Open-BFME5 conversions.

// The +4 string member is retail's StringBase<char> (4-byte Header*), and the
// per-element copy at 0x00887C90 is the matched StringBase<char>::set body
// (StringBase.cpp), so this TU calls that body under its own name.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeElemVOT
{
	int m_bfme00;
	StringBase<char> m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
};

BfmeElemVOT *bfmeCopyBackVOT(const BfmeElemVOT *first, const BfmeElemVOT *last, BfmeElemVOT *dest)
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
