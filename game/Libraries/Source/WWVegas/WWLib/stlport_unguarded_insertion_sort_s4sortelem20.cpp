// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__unguarded_insertion_sort_aux<S4SortElem20 *,
// S4SortElem20, S4Cmp002EB8E0>, retail 0x002EA750.

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_bfmeData;

	friend struct S4Name;
};

struct S4Name
{
	S4Name(const S4Name &other) : m_bfmeName(other.m_bfmeName) {}
	~S4Name(void) {}

	StringBase<char> m_bfmeName;
};

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail(void);

private:
	int m_bfmeBody[3];
};

struct S4SortElem20
{
	S4Name m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;
};

struct S4Cmp002EB8E0
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

template void __unguarded_insertion_sort_aux<S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20 *,
	S4Cmp002EB8E0);

}
