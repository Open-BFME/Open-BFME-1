// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__linear_insert<S4SortElem12 *, S4SortElem12,
// S4Cmp002E1690>, retail 0x002E0FE0, 177 bytes.  Its matched insertion-sort
// caller proves the twelve-byte element layout and passes the comparator by
// value through the ILT at 0x000219F9.

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
	T *m_bfmeData;

	friend struct S4Name;
	friend struct S4SortElem12;
};

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}
	S4Name &operator=(const S4Name &other)
	{
		m_base = other.m_base;
		return *this;
	}

	StringBase<char> m_base;
};

struct S4SortElem12
{
	int m_bfmeA;
	S4Name m_bfmeName;
	char m_bfmeC;
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const
	{
		return left.m_bfmeA < right.m_bfmeA;
	}
};

namespace _STL
{

struct random_access_iterator_tag
{
};

S4SortElem12 *BfmeCopyBackward002DFC60(S4SortElem12 *first,
	S4SortElem12 *last, S4SortElem12 *result,
	const random_access_iterator_tag &tag, int *distance);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first,
	RandomAccessIter last, Tp val, Compare comp)
{
	if (comp(val, *first))
	{
		random_access_iterator_tag tag;
		BfmeCopyBackward002DFC60(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem12 *, S4SortElem12,
	S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4SortElem12,
	S4Cmp002E1690);

}
