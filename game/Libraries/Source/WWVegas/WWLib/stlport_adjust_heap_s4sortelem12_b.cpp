// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: _STL::__adjust_heap<S4SortElem12 *, int, S4SortElem12,
// S4Cmp00532740>, retail 0x00530350, 402 bytes.  The neighboring insertion
// sort family proves the byte, StringBase<char>, and dword record layout.

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left,
	const void *right, unsigned int count);

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
		return left.m_bfmeName.m_base.compareNoCase(
			right.m_bfmeName.m_base) < 0;
	}
};

namespace _STL
{

template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIter first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);

template <class RandomAccessIter, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIter first, Distance holeIndex,
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

template void __adjust_heap<S4SortElem12 *, int, S4SortElem12,
	S4Cmp00532740>(S4SortElem12 *, int, int, S4SortElem12, S4Cmp00532740);

}
