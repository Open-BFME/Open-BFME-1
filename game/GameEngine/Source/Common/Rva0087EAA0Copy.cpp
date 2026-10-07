// cl: /O2 /Ob0 /G6 /Igame/Libraries/Source/WWVegas/WWLib

// The +0x1C tail is a StringBase<char>: retail calls
// ?set@?$StringBase@D@@QAEXABV1@@Z (0x00887C90) on it.
#include "string_base.h"

struct BfmeCoordAA
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElemAA
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoordAA m_10;
	StringBase<char> m_1C;
	char m_20;
	char m_pad[3];
};

BfmeElemAA *bfmeCopyAA(BfmeElemAA *first, BfmeElemAA *last, BfmeElemAA *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int m = n;
		do
		{
			--last;
			--dest;
			dest->m_00 = last->m_00;
			dest->m_04 = last->m_04;
			dest->m_08 = last->m_08;
			dest->m_0C = last->m_0C;
			dest->m_10 = last->m_10;
			dest->m_1C.set(last->m_1C);
			dest->m_20 = last->m_20;
		} while (--m);
	}
	return dest;
}
