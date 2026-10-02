// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct BfmeElemVMV
{
	StringBase<char> m_bfme00;
	StringBase<char> m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfme10;
	char m_bfme11;
	char m_bfmePad12[2];
};

BfmeElemVMV *bfmeCopyVMV(const BfmeElemVMV *first, const BfmeElemVMV *last, BfmeElemVMV *dest)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			dest->m_bfme00.set(first->m_bfme00);
			dest->m_bfme04.set(first->m_bfme04);
			dest->m_bfme08 = first->m_bfme08;
			dest->m_bfme0c = first->m_bfme0c;
			dest->m_bfme10 = first->m_bfme10;
			dest->m_bfme11 = first->m_bfme11;
			++first;
			++dest;
		} while (--i);
	}
	return dest;
}
