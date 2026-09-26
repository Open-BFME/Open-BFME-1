// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_partition<S4SortElem20 *, S4SortElem20,
// S4Cmp002EB8E0>, retail 0x002EAA30, 287 bytes. The body carried only a
// machine byte-dump row.
//
// STLport's partition loop over the same twenty-byte string-keyed element the
// neighbouring insertion-sort and unguarded-linear-insert bodies already
// landed. The comparator is the inlined StringBase memcmp against the empty
// sentinel at 0x0107388B. The pivot is by-value so the frame has an unwind
// record; its destructor stays out of line through the ILT at 0x0002AB2B
// (body 0x002E9E10). The swap is the two-argument helper at ILT 0x0003A76F
// (body 0x002EA1A0) because the element is not trivially copyable.

extern "C" int memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <class T>
class StringBase
{
private:
	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_bfmeLength;
		unsigned short m_bfmeCapacity;
		T m_bfmeData[1];
	};

	Header *m_bfmeHeader;

public:
	int compare(const StringBase<T> &other) const
	{
		const int length = other.m_bfmeHeader ? other.m_bfmeHeader->m_bfmeLength : 0;
		const char *data = other.m_bfmeHeader ? (const char *)&other.m_bfmeHeader->m_bfmeData[0] : "";
		const int myLength = m_bfmeHeader ? m_bfmeHeader->m_bfmeLength : 0;
		const char *myData = m_bfmeHeader ? (const char *)&m_bfmeHeader->m_bfmeData[0] : "";
		int result = memcmp(myData, data, myLength < length ? myLength : length);
		if (result == 0)
			result = myLength - length;
		return result;
	}

	friend struct S4SortElem20;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	S4SortElem20(const S4SortElem20 &other);
	~S4SortElem20();
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem20 &left,
		const S4SortElem20 &right) const
	{
		return left.m_bfmeName.compare(right.m_bfmeName) < 0;
	}
};

void bfmeIterSwapS4SortElem20(S4SortElem20 *left, S4SortElem20 *right);

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
		bfmeIterSwapS4SortElem20(first, last);
		++first;
	}
}

template S4SortElem20 *__unguarded_partition<S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0);

}
