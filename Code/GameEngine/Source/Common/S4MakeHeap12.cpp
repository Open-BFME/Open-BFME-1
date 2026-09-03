// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline

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

void Gen002E07A0(S4SortElem12 *first, int hole, int len, S4SortElem12 value,
	S4Cmp002E0CD0 comp);

void gen002E0CD0(S4SortElem12 *first, S4SortElem12 *last, S4Cmp002E0CD0 comp)
{
	if (last - first < 2)
		return;
	int len = last - first;
	int parent = (len - 2) / 2;
	for (;;)
	{
		Gen002E07A0(first, parent, len, first[parent], comp);
		if (parent == 0)
			return;
		--parent;
	}
}
