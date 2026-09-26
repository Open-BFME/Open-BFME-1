// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME7: STLport insertion sort over four-byte Q3SortElem4 values.
// Retail 0x00453A80 is the Gen00453A80 sort layer. The retail comparator
// shares its implementation with S4Cmp00452A50 through BfmeCompAP.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *, const void *, unsigned int);

struct Q3SortElem4
{
	void *m_item;
};

struct Q3SortCompare
{
	void *m_state;
};

#include "string_base.h"

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}

	__declspec(nothrow) int compareNoCase(const UnicodeString &other) const
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&other);
	}
};

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName(void);

	char m_pad[0x20];
	int m_count;
};

class BfmeCompAP
{
	public:
	int m_bfmeState;

	__declspec(noinline) bool operator()(int a, int b)
	{
		if (((const MapMetaData *)a)->m_count == ((const MapMetaData *)b)->m_count)
			return ((MapMetaData *)a)->bfme_getDisplayName().compareNoCase(
				((MapMetaData *)b)->bfme_getDisplayName()) < 0;

		return ((const MapMetaData *)a)->m_count < ((const MapMetaData *)b)->m_count;
	}
};

__forceinline int *bfmeCopyBackward(int *first, int *last, int *result)
{
	int bytes = (char *)last - (char *)first;
	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);
	return (int *)((char *)result - bytes);
}

void bfmeUnguardedInsertAP(int *last, int value, BfmeCompAP comp);

__forceinline void bfmeLinearInsertAP(int *first, int *last, int value,
	BfmeCompAP comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);
		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAP(last, value, comp);
	}
}

void Gen00453A80(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare comp)
{
	int *rawFirst = (int *)first;
	int *rawLast = (int *)last;
	if (rawFirst == rawLast)
		return;
	for (int *i = rawFirst + 1; i != rawLast; ++i)
		bfmeLinearInsertAP(rawFirst, i, *i, *(BfmeCompAP *)&comp);
}
