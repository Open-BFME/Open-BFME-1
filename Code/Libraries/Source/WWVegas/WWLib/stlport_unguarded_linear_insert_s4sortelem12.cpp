// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_linear_insert<S4SortElem12 *,
// S4SortElem12, S4Cmp002E1690>, retail 0x002E01A0, 141 bytes.  The matched
// __linear_insert caller at 0x002E0FE0 proves this specialization's identity,
// by-value element layout, and comparator.

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

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
	RandomAccessIter next = last;
	--next;
	while (comp(val, *next))
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}

template void __unguarded_linear_insert<S4SortElem12 *, S4SortElem12,
	S4Cmp002E1690>(S4SortElem12 *, S4SortElem12, S4Cmp002E1690);

}
