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
//
// Kept in its own TU rather than joining
// Code/GameEngine/Source/Common/S4MakeHeapElem12.cpp: that tracked file's
// current content only produces this same gen005726F0 body (a prior
// session's in-place rewrite orphaned its original gen00531C50 row, still
// pointing at this filename in reverse/functions.csv) -- editing it further
// under a live orphaned claim was not this lane's call to make.

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

void gen005726F0(void *firstVoid, void *lastVoid, void *compState, int, int)
{
	char *first = (char *)firstVoid;
	char *last = (char *)lastVoid;
	int len = (int)((last - first) / 12);

	if (len < 2)
		return;

	S4Cmp00573A30 comp;
	comp.m_bfmeState = compState;

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
