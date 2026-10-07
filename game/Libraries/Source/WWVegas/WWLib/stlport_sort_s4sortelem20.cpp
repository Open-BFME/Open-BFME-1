// Open-BFME5: STLport sort driver over twenty-byte S4 records, retail 0x002EBEF0.

struct S4SortElem20
{
	char m_bfmeBytes[20];
};

struct S4Cmp002EB8E0
{
	int m_bfmeState;
};

// ILT 0x00047343 -> 0x002EBAF0 is the matched __introsort_loop instance
// in stlport_introsort_loop_s4sortelem20.cpp.
namespace _STL
{
template <class RandomAccessIter, class T, class Size, class Compare>
void __introsort_loop(RandomAccessIter first,
	RandomAccessIter last, T *tag, Size depth_limit, Compare comp);

template <class RandomAccessIter, class Compare>
void __final_insertion_sort(RandomAccessIter first,
	RandomAccessIter last, Compare comp);
}

void Rva002EBEF0(S4SortElem20 *first,
	S4SortElem20 *last, S4Cmp002EB8E0 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		_STL::__introsort_loop(first, last, (S4SortElem20 *)0, k * 2, comp);
		_STL::__final_insertion_sort(first, last, comp);
	}
}
