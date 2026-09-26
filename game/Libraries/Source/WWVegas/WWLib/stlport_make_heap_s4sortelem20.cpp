// cl: /DNDEBUG /MD /EHsc

// Open-BFME: _STL::__make_heap<S4SortElem20 *, S4Cmp002EB8E0,
// S4SortElem20, int>, retail 0x002EACD0, 184 bytes.  The neighboring
// STLport sort bodies identify the twenty-byte element and comparator.

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);

	T *m_bfmeData;

	friend struct S4SortElem20;
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
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
	Compare comp, Tp *, Distance *)
{
	Distance len = last - first;
	if (len < 2)
		return;
	Distance parent = (len - 2) / 2;
	for (;;)
	{
		__adjust_heap(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}

template void __make_heap<S4SortElem20 *, S4Cmp002EB8E0,
	S4SortElem20, int>(S4SortElem20 *, S4SortElem20 *, S4Cmp002EB8E0,
	S4SortElem20 *, int *);

}
