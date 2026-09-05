// cl: /DNDEBUG /MD /EHsc

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
	Distance topIndex, Tp val, Compare comp)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && comp(*(first + parent), val))
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template void __push_heap<S4SortElem20 *, int, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, int, int, S4SortElem20, S4Cmp002EB8E0);

}
