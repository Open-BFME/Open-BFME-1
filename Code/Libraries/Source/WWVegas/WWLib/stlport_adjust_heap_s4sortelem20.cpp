// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__adjust_heap<S4SortElem20 *, int, S4SortElem20,
// S4Cmp002EB8E0>, retail 0x002EA810. STLport sift-down over the same
// twenty-byte element as the insertion-sort family at 0x002EA750.

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
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

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

private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);
	friend struct S4SortElem20;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();
	BfmeSortElem20Tail &operator=(const BfmeSortElem20Tail &other)
	{
		set(other);
		return *this;
	}

	void set(const BfmeSortElem20Tail &other);

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	S4SortElem20 &operator=(const S4SortElem20 &other)
	{
		m_bfmeName = other.m_bfmeName;
		m_bfmeFlag = other.m_bfmeFlag;
		m_bfmeTail.set(other.m_bfmeTail);
		return *this;
	}
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

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp(*(first + secondChild), *(first + (secondChild - 1))))
			secondChild--;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, val, comp);
}

template void __adjust_heap<S4SortElem20 *, int, S4SortElem20, S4Cmp002EB8E0>(
	S4SortElem20 *, int, int, S4SortElem20, S4Cmp002EB8E0);

}
