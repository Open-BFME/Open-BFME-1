// cl: /DNDEBUG /MD /EHsc
// Native five-slot ABI view for retail 0x009F53D0.
// The original helper declaration and trailing argument types are unknown.
// Existing element/comparator spellings are ABI views, not native type names;
// m_key/m_values retain their inherited spelling without a semantic claim.
// Evidence: targets/game/reverse/identity_evidence/009f55d0-five-slot-call.md.

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
	bool operator()(const S4SortElem24 &a, const S4SortElem24 &b) const;
};

namespace _STL
{
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __push_heap(RandomAccessIterator first, Distance holeIndex,
	Distance topIndex, Tp val, Compare comp);
}

// ?Rva009F53D0@@YAXPAUS4SortElem24@@0US4Cmp009F4BF0@@PAX2@Z
void Rva009F53D0(S4SortElem24 *first, S4SortElem24 *last,
	S4Cmp009F4BF0 comp, void *, void *)
{
	_STL::__push_heap(first, (int)(last - first) - 1, 0, *(last - 1), comp);
}
