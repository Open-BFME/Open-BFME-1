// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport __make_heap over the twelve-byte flag/string/int record
// at retail 0x00531C50.  The body was left orphaned when the former attempt at
// this address was moved to S4MakeHeapElem12Sort.cpp; the retail callee and
// element layout are independently established by the adjacent 0x00530350
// __adjust_heap and 0x00531D80 __pop_heap bodies.  The four-byte name member
// is the StringBase char subobject copied by retail 0x00887B60.

struct S4Name;

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
	void releaseBuffer(void);
	T *m_data;

	friend struct S4Name;
	friend struct S4SortElem12_00532740;
};

// Same S4Name view as the WWLib S4Cmp00532740 sort layers (89d88dcd24), so
// the inline S4SortElem12_00532740 special members are one COMDAT body.
struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) { m_base.releaseBuffer(); }

	StringBase<char> m_base;
};

struct S4SortElem12_00532740
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;
};

struct S4Cmp00532740
{
	int m_bfmeSlot;
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

}

void gen00531C50(void *firstVoid, void *lastVoid, void *compVoid, int, int)
{
	S4SortElem12_00532740 *first = (S4SortElem12_00532740 *)firstVoid;
	S4SortElem12_00532740 *last = (S4SortElem12_00532740 *)lastVoid;
	int len = last - first;

	if (len < 2)
		return;

	int parent = (len - 2) / 2;
	for (;;)
	{
		S4Cmp00532740 comp;
		comp.m_bfmeSlot = (int)compVoid;
		_STL::__adjust_heap(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}
