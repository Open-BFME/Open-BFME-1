// cl: /DNDEBUG /MD /EHsc
// Open-BFME: _STL::__linear_insert<S4SortElem20 *, S4SortElem20,
// S4Cmp002EB8E0>, retail 0x002EAF10, 197 bytes.
//
// Same twenty-byte element as the matched insertion_sort at 0x002EB270 and
// unguarded_linear_insert at 0x002EA270. Retail compare is an int three-way
// (test eax / jge), copy_backward is the five-argument STLport form, then
// memberwise assign; else copy-construct val and call the matched unguarded
// insert. Val dtor is tail then StringBase::releaseBuffer.

template <class T>
class StringBase
{
public:
	int compare(const StringBase<T> &other) const;
	void set(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	T *m_bfmeData;

	friend struct S4SortElem20;
};

struct BfmeSortTailElement12;

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();
	BfmeSortElem20Tail &set(const BfmeSortElem20Tail &other);
	BfmeSortElem20Tail &operator=(const BfmeSortElem20Tail &other)
	{
		set(other);
		return *this;
	}

private:
	// Retail vector header; each element is12B, with StringBase at+4.
	BfmeSortTailElement12 *m_begin;
	BfmeSortTailElement12 *m_end;
	BfmeSortTailElement12 *m_capacity;
};

struct S4SortElem20
{
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	S4SortElem20(const S4SortElem20 &other);

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

	bool operator()(const S4SortElem20 &left, const S4SortElem20 &right) const
	{
		return left.m_bfmeName.compare(right.m_bfmeName) < 0;
	}
};

namespace _STL
{

struct random_access_iterator_tag
{
};

S4SortElem20 *BfmeCopyBackward002EA550(S4SortElem20 *first,
	S4SortElem20 *last, S4SortElem20 *result,
	const random_access_iterator_tag &tag, int *distance);

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp)
{
	if (comp(val, *first))
	{
		random_access_iterator_tag tag;
		BfmeCopyBackward002EA550(first, last, last + 1, tag, (int *)0);
		*first = val;
	}
	else
	{
		__unguarded_linear_insert(last, val, comp);
	}
}

template void __linear_insert<S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20,
	S4Cmp002EB8E0);

}
