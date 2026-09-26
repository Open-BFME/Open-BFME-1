// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __partial_sort over the twelve-byte S4 record ordered by
// S4Cmp00532740, retail 0x00532F40, 287 bytes.  targets/game/reverse/symbols.csv already
// pins this name to ILT 0x000075C7, and that thunk jumps straight to
// 0x00532F40.  The introsort loop at 0x00533520 is one of the two callers and
// carries the same element and comparator types.
//
// The record is a flag byte, a narrow StringBase name and a dword, the same
// shape the neighboring insertion-sort family uses.  The comparator orders an
// empty flag against a set one first, then compares the two names without
// case.
//
// The three helpers are called out of line and keep the ledger's own names:
// make_heap at 0x00531C50, pop_heap at 0x00531A40 and sort_heap at 0x00532900.

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left,
	const void *right, unsigned int count);

struct S4Name;
struct S4SortElem12;

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}
	int compareNoCase(const StringBase<T> &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const T *otherData = other.m_data ? other.m_data->m_data : (const T *)"";
		int thisLength = m_data ? m_data->m_length : 0;
		const T *thisData = m_data ? m_data->m_data : (const T *)"";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = _memicmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	struct Header
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_data[1];
	};

	Header *m_data;

	friend struct S4Name;
	friend struct S4SortElem12;
};

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}

	StringBase<char> m_base;
};

struct S4SortElem12
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;
};

struct S4Cmp00532740
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		if (((!left.m_bfmeA) ^ (!right.m_bfmeA)) != 0)
			return left.m_bfmeA;
		return left.m_bfmeName.m_base.compareNoCase(right.m_bfmeName.m_base) < 0;
	}
};

void gen00531C50(void *first, void *last, void *comp, int, int);
void bfmePopHeap00531A40(S4SortElem12 *first, S4SortElem12 *last,
	S4SortElem12 *result, S4SortElem12 value, void *comp, int *distance);
void bfmeSortVOY(void *first, void *last, void *comp);

namespace _STL
{

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
	RandomAccessIterator last, Tp *, Compare comp)
{
	gen00531C50(first, middle, comp.m_bfmeState, 0, 0);
	for (RandomAccessIterator i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
			bfmePopHeap00531A40(first, middle, i, Tp(*i), comp.m_bfmeState, 0);
	}
	bfmeSortVOY(first, middle, comp.m_bfmeState);
}

template void __partial_sort<S4SortElem12 *, S4SortElem12,
	S4Cmp00532740>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *,
	S4SortElem12 *, S4Cmp00532740);

}
