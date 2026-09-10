// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<S4SortElem12 *, S4SortElem12,
// S4Cmp00532740>, retail 0x0052FC70, 358 bytes.  The exact identity comes
// from the ILT reached by the matched 0x00533520 introsort specialization
// (reverse/symbols.csv, 0x00017F26), while the neighboring insertion and
// introsort bodies establish the byte-string record and comparator.

extern "C" __declspec(dllimport) int __cdecl _memicmp(
	const void *left, const void *right, unsigned int count);

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
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		if (((!left.m_bfmeA) ^ (!right.m_bfmeA)) != 0)
			return left.m_bfmeA;
		return left.m_bfmeName.m_base.compareNoCase(right.m_bfmeName.m_base) < 0;
	}
};

void bfmeSwapElem12(S4SortElem12 &left, S4SortElem12 &right);

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
RandomAccessIter __unguarded_partition(RandomAccessIter first,
	RandomAccessIter last, Tp pivot, Compare comp)
{
	while (true)
	{
		while (comp(*first, pivot))
			++first;
		--last;
		while (comp(pivot, *last))
			--last;
		if (!(first < last))
			return first;
		bfmeSwapElem12(*first, *last);
		++first;
	}
}

template S4SortElem12 *__unguarded_partition<S4SortElem12 *, S4SortElem12,
	S4Cmp00532740>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp00532740);

}
