// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: STLport __make_heap over the twelve-byte flag/string/int record
// at retail 0x00531C50.  The body was left orphaned when the former attempt at
// this address was moved to S4MakeHeapElem12Sort.cpp; the retail callee and
// element layout are independently established by the adjacent 0x00530350
// __adjust_heap and 0x00531D80 __pop_heap bodies.  The four-byte name member
// is the StringBase char subobject whose copied body is the existing
// GameSpyGroupRoom alias at retail 0x00887B60.

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &other);

private:
	void *m_bfmeData;
};

struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) {}

	GameSpyGroupRoom m_base;
};

struct S4SortElem12
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;

	S4SortElem12(const S4SortElem12 &other) :
		m_bfmeA(other.m_bfmeA),
		m_bfmeName(other.m_bfmeName),
		m_bfmeC(other.m_bfmeC)
	{
	}
	~S4SortElem12(void) {}
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
	S4SortElem12 *first = (S4SortElem12 *)firstVoid;
	S4SortElem12 *last = (S4SortElem12 *)lastVoid;
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

struct S4SortElem12Sort
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00573A30Sort
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12Sort &left,
		const S4SortElem12Sort &right) const { return left.m_bfmeKey < right.m_bfmeKey; }
};

namespace _STL
{

template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

}

void gen005726F0(void *firstVoid, void *lastVoid, void *compVoid, int, int)
{
	char *first = (char *)firstVoid;
	char *last = (char *)lastVoid;
	S4Cmp00573A30Sort comp = *(S4Cmp00573A30Sort *)compVoid;
	int len = (int)((last - first) / 12);

	if (len < 2)
		return;

	int parent = (len - 2) / 2;
	for (;;)
	{
		S4SortElem12Sort *elem = (S4SortElem12Sort *)(first + parent * 12);
		_STL::__adjust_heap((S4SortElem12Sort *)first, parent, len, *elem, comp);
		if (parent == 0)
			return;
		--parent;
	}
}
