// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME7: STLport insertion sort over four-byte Q3SortElem4 values.
// Retail 0x004539D0 calls the shared AO comparator and the pointer-valued
// unguarded insertion body at 0x00452910.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *, const void *, unsigned int);

struct Q3SortElem4
{
	int m_item;
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
	UnicodeString getFileName() const;
};

#pragma comment(linker, "/alternatename:?getFileName@MapMetaData@@QBE?AVUnicodeString@@XZ=?d_00451350@@YAXXZ")

struct BfmeCompAO
{
	__declspec(noinline) bool operator()(int left, int right)
	{
		return ((const MapMetaData *)left)->getFileName().compareNoCase(
			((const MapMetaData *)right)->getFileName()) < 0;
	}
	int m_bfmeState;
};

struct BfmeInsertCompareB
{
	bool operator()(void *pending, void *element);
};

void bfmeLinearInsert_00452910(int *last, int pending,
	BfmeInsertCompareB compare);

__forceinline int *bfmeCopyBackward(int *first, int *last, int *result)
{
	int bytes = (char *)last - (char *)first;
	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);
	return (int *)((char *)result - bytes);
}

__forceinline void bfmeLinearInsertAO(int *first, int *last,
	int value, BfmeCompAO comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);
		*first = value;
	}
	else
	{
		bfmeLinearInsert_00452910(last, value,
			*(BfmeInsertCompareB *)&comp);
	}
}

void Gen004539D0(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortCompare comp)
{
	int *rawFirst = (int *)first;
	int *rawLast = (int *)last;
	if (rawFirst == rawLast)
		return;
	for (int *i = rawFirst + 1; i != rawLast; ++i)
		bfmeLinearInsertAO(rawFirst, i, *i, *(BfmeCompAO *)&comp);
}
