// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__insertion_sort<S4SortElem12 *, S4Cmp00532740>, retail
// 0x00532080, 81 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The twin of 0x002E1170 over the same element with a different comparator.
// STLport's __insertion_sort, in the variant whose comment says "supply *__i
// as __val": the element is passed to __linear_insert by value rather than
// copied inside it. That is the twelve bytes the loop carves off the stack
// each pass, and the element's compiler-generated copy constructor is what
// fills them -- a dword at +0, a call to StringBase<char>'s copy constructor
// for the string at +4, and a byte at +8, in declaration order.
//
// The stride confirms the size: __i starts at first + 0x0C and advances by
// 0x0C. __linear_insert is marked inline in STLport but is a call here, so it
// is declared and left undefined.
//
// The string needs a destructor as well as a copy constructor, even though
// neither is called in this body. Without one the element is trivially
// destructible, the by-value argument needs no address recorded, and the store
// of the temporary's address into the now-dead first parameter slot -- four
// bytes -- does not appear.

class BfmeStringBaseChar;
struct S4Name;

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);			// retail 0x00887C90
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}
	int compareNoCase(const StringBase<T> &other) const;	// retail 0x00027471

	private:
	StringBase(const StringBase<T> &other);			// retail 0x00887B60
	~StringBase(void);
	T *m_bfmeData;

	friend struct S4Name;
	friend struct S4SortElem12;
};

// The wrapper keeps the retail string subobject at +0x04 while making its
// copy and destruction sequence explicit for this isolated STLport TU.
struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}

	StringBase<char> m_base;
};

// Not the same twelve bytes as the sort at 0x002E1170, despite the shared
// placeholder name: there the copy reads a dword at +0 and a byte at +8, here
// it reads a byte at +0 and a dword at +8. Only the string at +4 is common.
struct S4SortElem12
{
	bool m_bfmeA;						// +0x00
	S4Name m_bfmeName;					// +0x04
	int m_bfmeC;						// +0x08
};

struct S4Cmp00532740
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem12 &left, const S4SortElem12 &right) const
	{
		if (((!left.m_bfmeA) ^ (!right.m_bfmeA)) != 0)
			return left.m_bfmeA;
		return left.m_bfmeName.m_base.compareNoCase(right.m_bfmeName.m_base) < 0;
	}
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);

struct random_access_iterator_tag
{
};

template <class RandomAccessIter, class BidirectionalIter, class Distance>
BidirectionalIter __copy_backward(RandomAccessIter first, RandomAccessIter last,
	BidirectionalIter result, const random_access_iterator_tag &tag,
	Distance *distance);						// ILT 0x0003EF95

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp);

template <class RandomAccessIter, class Tp, class Compare>
inline void __linear_insert(RandomAccessIter first,
	RandomAccessIter last, Tp val, Compare comp)
{
	if (comp(val, *first)) {
		random_access_iterator_tag tag;
		__copy_backward(first, last, last + 1, tag, (int *)0);
		*first = val;
	} else {
		__unguarded_linear_insert(last, val, comp);
	}
}

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (first == last)
		return;

	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<S4SortElem12 *, S4Cmp00532740>(
	S4SortElem12 *, S4SortElem12 *, S4Cmp00532740);

}
