// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: STLport median of three for the twelve-byte S4 name record at
// retail 0x0052FB30. The matched introsort body at 0x00533520 reaches this
// specialization through ILT 0x000206C6.

#include "string_base.h"

struct S4Name
{
	StringBase<char> m_base;
};

struct S4SortElem12_00532740
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;
};

struct S4Cmp00532740
{
	int m_bfmeSlot;

	// Retail 0x0052FB30 inlines this comparator but calls compareNoCase
	// through ILT 0x27471, while the other S4Cmp00532740 layers inline
	// compareNoCase too. A member template keeps this TU's inline copy out of
	// the shared ??RS4Cmp00532740 COMDAT those layers emit.
	template <class Elem>
	bool operator()(const Elem &left, const Elem &right) const
	{
		if (((!left.m_bfmeA) ^ (!right.m_bfmeA)) != 0)
			return left.m_bfmeA;
		return left.m_bfmeName.m_base.compareNoCase(
			right.m_bfmeName.m_base) < 0;
	}
};

namespace _STL
{

template <class Tp, class Compare>
const Tp &__median(const Tp &a, const Tp &b, const Tp &c, Compare comp)
{
	if (comp(a, b))
		if (comp(b, c))
			return b;
		else if (comp(a, c))
			return c;
		else
			return a;
	else if (comp(a, c))
		return a;
	else if (comp(b, c))
		return c;
	else
		return b;
}

template const S4SortElem12_00532740 &__median<S4SortElem12_00532740, S4Cmp00532740>(
	const S4SortElem12_00532740 &, const S4SortElem12_00532740 &, const S4SortElem12_00532740 &,
	S4Cmp00532740);

}
