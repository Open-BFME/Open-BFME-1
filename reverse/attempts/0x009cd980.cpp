// ?d_009cd980@@YAXXZ
// partial score=0.9835 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport partial sort over four-byte AsciiString elements at
// retail 0x009CD980, reached by the named Q3 introsort caller at 0x009CDAA0.
// The heap and sort helpers are the already matched VOU family at 0x009CD5E0,
// 0x009CD560, and 0x009CD910. The comparator moves underscore-prefixed names
// in reverse case-insensitive order and all other names in forward order.

#include <new>

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

template <class T>
struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_data[1];
};

template <class T>
class StringBase
{
	friend struct Q3SortElem4;
	friend struct BfmeElemVOU;
	friend struct Q3SortCompare;

public:
	int compareNoCase(const StringBase<T> &other) const;
	__forceinline bool startsWithUnderscore() const
	{
		return m_data != 0 && m_data->m_data[0] == '_';
	}
	__forceinline int compareNoCaseInline(const StringBase<T> &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const T *otherData = other.m_data
			? other.m_data->m_data : (const T *)"";
		int thisLength = m_data ? m_data->m_length : 0;
		const T *thisData = m_data
			? m_data->m_data : (const T *)"";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = _memicmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

private:
	StringBase(const StringBase<T> &other);
	StringInlineData<T> *m_data;
};

struct Q3SortElem4
{
	Q3SortElem4(const Q3SortElem4 &other)
		: m_base(*(const StringBase<char> *)&other) {}
	~Q3SortElem4() {}
	StringBase<char> m_base;

	friend struct Q3SortCompare;
};

struct Q3SortCompare
{
	void *m_state;

	__forceinline bool operator()(const Q3SortElem4 &left,
		const Q3SortElem4 &right) const
	{
		if (left.m_base.startsWithUnderscore()
			&& right.m_base.startsWithUnderscore())
			return left.m_base.compareNoCase(right.m_base) > 0;

		return left.m_base.compareNoCaseInline(right.m_base) < 0;
	}
};

struct BfmeElemVOU
{
	BfmeElemVOU(const BfmeElemVOU &other)
		: m_base(*(const StringBase<char> *)&other) {}
	~BfmeElemVOU() {}
	StringBase<char> m_base;
};

extern "C" void q3PopHeap(BfmeElemVOU *first, BfmeElemVOU *last,
	BfmeElemVOU *result, BfmeElemVOU value, Q3SortCompare compare, int *);
#pragma comment(linker, "/alternatename:_q3PopHeap=?bfmePopHeapVOU@@YAXPAUBfmeElemVOU@@00U1@PAXPAH@Z")
void bfmeSortVOU(void *first, void *last, void *compare);

extern "C" void q3MakeHeap(BfmeElemVOU *first, BfmeElemVOU *last,
	Q3SortCompare compare, void *, int *);
#pragma comment(linker, "/alternatename:_q3MakeHeap=?bfmeMakeHeapVOU@@YAXPAUBfmeElemVOU@@0PAX@Z")

// ?Gen009CD980@@YAXPAUQ3SortElem4@@000UQ3SortCompare@@@Z
void Gen009CD980(Q3SortElem4 *first, Q3SortElem4 *middle,
	Q3SortElem4 *last, Q3SortElem4 *, Q3SortCompare compare)
{
	q3MakeHeap((BfmeElemVOU *)first, (BfmeElemVOU *)middle,
		compare, (Q3SortElem4 *)0, (int *)0);
	for (Q3SortElem4 *i = middle; i < last; ++i)
	{
		if (compare(*i, *first))
		{
			q3PopHeap((BfmeElemVOU *)first, (BfmeElemVOU *)middle,
				(BfmeElemVOU *)i, *(BfmeElemVOU *)i,
				compare, (int *)0);
		}
	}
	bfmeSortVOU(first, middle, *(void **)&compare);
}
