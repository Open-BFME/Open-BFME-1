// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::__insertion_sort<S4SortElem12 *, S4Cmp002E1690>, retail
// 0x002E1170, 81 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
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

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);			// retail 0x00887B60
	~StringBase(void);

	T *m_bfmeData;

	friend struct S4SortElem12;
};

struct S4SortElem12
{
	int m_bfmeA;						// +0x00
	StringBase<char> m_bfmeName;				// +0x04
	char m_bfmeC;						// +0x08
};

struct S4Cmp002E1690
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);						// ILT 0x000219F9

template <class RandomAccessIter, class Compare>
void __insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	if (first == last)
		return;

	for (RandomAccessIter i = first + 1; i != last; ++i)
		__linear_insert(first, i, *i, comp);
}

template void __insertion_sort<S4SortElem12 *, S4Cmp002E1690>(
	S4SortElem12 *, S4SortElem12 *, S4Cmp002E1690);

}
