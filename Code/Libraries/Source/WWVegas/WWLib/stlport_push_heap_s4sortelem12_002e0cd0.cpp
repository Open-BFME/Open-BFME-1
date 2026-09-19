// ??$__push_heap@PAUS4SortElem12@@HU1@US4Cmp002E0CD0@@@_STL@@YAXPAUS4SortElem12@@HHU1@US4Cmp002E0CD0@@@Z
// Retail 0x002E0250. The matched __adjust_heap caller at 0x002E07A0
// proves this STLport specialization, its twelve-byte element, and the
// first-field comparator.
// cl: /DNDEBUG /MD /O2 /EHsc

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
	int m_a;
	S4Name m_name;
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

template void __push_heap<S4SortElem12 *, int, S4SortElem12,
	S4Cmp002E0CD0>(S4SortElem12 *, int, int, S4SortElem12,
	S4Cmp002E0CD0);

}
