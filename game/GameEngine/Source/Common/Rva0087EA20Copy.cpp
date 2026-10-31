// cl: /O2 /Ob0 /G6

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeCoordA2
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElemA2
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoordA2 m_10;
	StringBase<char> m_1C;
	char m_20;
	char m_pad[3];
};

BfmeElemA2 *bfmeCopyA2(BfmeElemA2 *first, BfmeElemA2 *last, BfmeElemA2 *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int m = n;
		do
		{
			dest->m_00 = first->m_00;
			dest->m_04 = first->m_04;
			dest->m_08 = first->m_08;
			dest->m_0C = first->m_0C;
			dest->m_10 = first->m_10;
			dest->m_1C.set(first->m_1C);
			dest->m_20 = first->m_20;
			++first;
			++dest;
		} while (--m);
	}
	return dest;
}

// 0x0087F090: unreferenced 32-byte cdecl forwarder after the fill helpers,
// the same shape as the matched rva0087F0D0FillBE: it reserves a stack slot
// for an empty tag and passes its address plus a null pointer behind the three
// iterators (STLport's copy -> __copy(first, last, result, iterator tag,
// distance*) dispatch).  bfmeCopyA2 reads only the three iterators, so the
// call goes through a five-parameter view of that body.  Address-derived name;
// identity unproven.
struct BfmeTagA2
{
};

BfmeElemA2 *rva0087F090CopyA2(BfmeElemA2 *first, BfmeElemA2 *last, BfmeElemA2 *dest)
{
	typedef BfmeElemA2 *(*FullCopy)(BfmeElemA2 *, BfmeElemA2 *, BfmeElemA2 *, const BfmeTagA2 &, int *);
	BfmeTagA2 tag;
	return ((FullCopy)&bfmeCopyA2)(first, last, dest, tag, 0);
}
