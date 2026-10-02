// cl: /DNDEBUG /MD /O2 /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

struct S4SortElem12
{
	int m_a;
	AsciiString m_name;
	char m_flag;
};

struct S4Cmp002E0CD0
{
	void *m_state;
	bool operator()(S4SortElem12, S4SortElem12) const;
};

namespace _STL
{
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance hole, Distance len,
	Tp value, Compare comp);
}

void gen002E0CD0(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E0CD0 comp)
{
	if (last - first < 2)
		return;
	int len = last - first;
	int parent = (len - 2) / 2;
	for (;;)
	{
		_STL::__adjust_heap(first, parent, len, first[parent], comp);
		if (parent == 0)
			return;
		--parent;
	}
}
