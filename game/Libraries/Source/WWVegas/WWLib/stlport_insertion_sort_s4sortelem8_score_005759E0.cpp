// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: insertion-sort driver over S4SortElem8/S4Cmp00575AA0, retail
// 0x005759E0, 62 bytes.  Calls the already-landed
// _STL::__linear_insert<S4SortElem8 *, S4SortElem8, S4Cmp00575AA0>
// (retail 0x005756C0) once per element past the first, same shape as the
// GameTextStringLookUp insertion-sort driver at 0x00437E90.

struct S4SortElem8
{
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct S4Cmp00575AA0
{
	void *m_bfmeState;
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __linear_insert(RandomAccessIter first, RandomAccessIter last, Tp val,
	Compare comp);

}

void __cdecl S4InsertionSort005759E0(S4SortElem8 *first, S4SortElem8 *last,
	S4Cmp00575AA0 comp)
{
	if (first == last)
		return;
	S4SortElem8 *mid = first + 1;
	if (mid == last)
		return;
	for (S4SortElem8 *i = mid; i != last; ++i)
	{
		_STL::__linear_insert(first, i, *i, comp);
	}
}
