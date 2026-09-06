// cl: /DNDEBUG /MD /O2 /EHsc

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct S4SortElem12
{
	int m_a;
	AsciiString m_name;
	char m_flag;
};

struct S4Cmp002E0CD0
{
	void *m_state;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_a < right.m_a;
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

template void __adjust_heap<S4SortElem12 *, int, S4SortElem12,
	S4Cmp002E0CD0>(S4SortElem12 *, int, int, S4SortElem12,
	S4Cmp002E0CD0);

}
