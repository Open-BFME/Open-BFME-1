// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __make_heap over the same twelve-byte element as
// Code/GameEngine/Source/Common/S4SortHeapElem12.cpp (sort_heap, retail
// 0x00573A30), retail 0x005726F0, 148 bytes.  Same countdown shape as
// Code/GameEngine/Source/Common/S4MakeHeapElem12Pod.cpp (retail 0x00531B20)
// but the out-of-line callee is the templated
// _STL::__adjust_heap<S4SortElem12 *, int, S4SortElem12, S4Cmp00573A30>
// (ILT 0x0003DF00), not the address-derived bfmeAdjustHeap00531B20 the Pod
// sibling calls, so the element/comparator types are S4SortHeapElem12.cpp's
// S4SortElem12 / S4Cmp00573A30 rather than the Pod stand-ins.

struct S4SortElem12
{
	int m_bfmeKey;
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00573A30
{
	void *m_bfmeState;

	bool operator()(const S4SortElem12 &left,
		const S4SortElem12 &right) const { return left.m_bfmeKey < right.m_bfmeKey; }
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
	S4Cmp00573A30 comp = *(S4Cmp00573A30 *)compVoid;
	int len = (int)((last - first) / 12);

	if (len < 2)
		return;

	int parent = (len - 2) / 2;
	for (;;)
	{
		S4SortElem12 *elem = (S4SortElem12 *)(first + parent * 12);
		_STL::__adjust_heap((S4SortElem12 *)first, parent, len, *elem, comp);
		if (parent == 0)
			return;
		--parent;
	}
}
