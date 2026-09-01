// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_insertion_sort_aux<S4SortElem12 *,
// S4SortElem12, S4Cmp002E1690>, retail 0x002E0730, 73 bytes.  The matched
// neighboring sort layers prove the non-trivial twelve-byte element layout.

struct S4Name;

template <class T>
class StringBase
{
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

	StringBase<char> m_base;
};

struct S4SortElem12
{
	int m_bfmeKey;
	S4Name m_bfmeName;
	char m_bfmeThird;
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first,
	RandomAccessIter last, Tp *, Compare comp)
{
	for (RandomAccessIter i = first; i != last; ++i)
		__unguarded_linear_insert(i, *i, comp);
}

template void __unguarded_insertion_sort_aux<S4SortElem12 *, S4SortElem12,
	S4Cmp002E1690>(S4SortElem12 *, S4SortElem12 *, S4SortElem12 *,
	S4Cmp002E1690);

}
