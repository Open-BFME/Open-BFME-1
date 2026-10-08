// Open-BFME5 conversions.

// The +4 string member is retail's StringBase<char> (4-byte Header*), and the
// per-element copy at 0x00887C90 is the matched StringBase<char>::set body
// (StringBase.cpp), so this TU calls that body under its own name.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Retail 0x0052D740 is STLport's _STL::__copy_backward for the (byte, string,
// dword) record S4SortElem12_00532740: its only proven caller, __linear_insert
// 0x00531860 (stlport_insertion_sort_s4sortelem12_b.cpp), reaches it through
// ILT 0x0003EF95 with STLport's five arguments (first, last, result, tag,
// distance*). The body reads only the first three, so the extra two leave no
// trace in it. The element layout is the one identity_evidence/
// 00532740-s4sortelem12-layout-split.md proves for that family.
struct S4SortElem12_00532740
{
	char m_bfme00;
	char m_bfmePad01[3];
	StringBase<char> m_bfme04;
	int m_bfme08;
};

namespace _STL
{

struct random_access_iterator_tag
{
};

template <class RandomAccessIter, class BidirectionalIter, class Distance>
BidirectionalIter __copy_backward(RandomAccessIter first, RandomAccessIter last,
	BidirectionalIter result, const random_access_iterator_tag &, Distance *)
{
	int n = last - first;

	if (n > 0)
	{
		int i = n;

		do
		{
			--last;
			--result;
			result->m_bfme00 = last->m_bfme00;
			result->m_bfme04.set(last->m_bfme04);
			result->m_bfme08 = last->m_bfme08;
		} while (--i);
	}
	return result;
}

template S4SortElem12_00532740 *__copy_backward<S4SortElem12_00532740 *,
	S4SortElem12_00532740 *, int>(S4SortElem12_00532740 *,
	S4SortElem12_00532740 *, S4SortElem12_00532740 *,
	const random_access_iterator_tag &, int *);

}
