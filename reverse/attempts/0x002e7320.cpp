// ??0BfmeSortElem20Tail@@QAE@ABV0@@Z
// partial score=0.94 date=2026-08-31
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// stlport

#include <vector>

// Open-BFME5: _STL::__insertion_sort<S4SortElem20 *, S4Cmp002EB8E0>, retail
// 0x002EB270, 144 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The twenty-byte cousin of the sorts at 0x002E1170 and 0x00532080. Same
// STLport source -- the element goes to __linear_insert by value -- but this
// element has two members that need construction rather than one, so the copy
// is a string copy constructor at +0, a byte at +4, and a second out-of-line
// copy constructor for the twelve bytes at +8. The stride confirms the size:
// __i starts at first + 0x14 and advances by 0x14.
//
// Two members with destructors is also why this body has an unwind frame where
// its twelve-byte cousins have none: the state goes to 0 while the second
// member is being constructed, so the string gets destroyed if that throws.
//
// The string needs a destructor as well as a copy constructor, even though
// neither is called in this body. Without one the element is trivially
// destructible, the by-value argument needs no address recorded, and the store
// of the temporary's address into the now-dead first parameter slot -- four
// bytes -- does not appear.

class BfmeStringBaseChar;

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &other);			// retail 0x00887B60
	~StringBase(void);

	private:
	T *m_bfmeData;

	friend struct S4SortElem20;
};

struct BfmeSortElem20TailElement
{
	int m_bfmeValue;
	StringBase<char> m_bfmeName;
	char m_bfmeFlag;
};

class BfmeSortElem20Tail
	: public _STL::_Vector_base<BfmeSortElem20TailElement,
		_STL::allocator<BfmeSortElem20TailElement> >
{
private:
	typedef BfmeSortElem20TailElement Element;
	typedef _STL::allocator<Element> Allocator;
	typedef _STL::_Vector_base<Element, Allocator> Base;

public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);	// ILT 0x000266BB
	~BfmeSortElem20Tail(void);

	unsigned int size(void) const
	{
		return (unsigned int)(this->_M_finish - this->_M_start);
	}

	Allocator get_allocator(void) const
	{
		return (const Allocator &)this->_M_end_of_storage;
	}
};

BfmeSortElem20Tail::BfmeSortElem20Tail(const BfmeSortElem20Tail &other)
	: Base(other.size(), other.get_allocator())
{
	const Element *first = other._M_start;
	const Element *last = other._M_finish;
	Element *current = this->_M_start;
	for (; first != last; ++first, ++current)
		_STL::_Construct(current, *first);
	this->_M_finish = current;
}

struct S4SortElem20
{
	StringBase<char> m_bfmeName;				// +0x00
	char m_bfmeFlag;					// +0x04
	BfmeSortElem20Tail m_bfmeTail;				// +0x08
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);						// ILT 0x0002D34E

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (first == last)
		return;

	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<S4SortElem20 *, S4Cmp002EB8E0>(
	S4SortElem20 *, S4SortElem20 *, S4Cmp002EB8E0);

}
