// cl: /DNDEBUG /MD /EHsc
// stlport

// Retail 0x005336D0 is an STLport sort driver over four-byte values. The
// scalar-ID pass at 0x00534034 calls this helper before it processes each ID.

struct Q4Sort00533470
{
	void *m_state;
	bool operator()(int, int) const;
};

namespace _STL
{
template <class RandomAccessIter, class Tp, class Size, class Compare>
void __introsort_loop(RandomAccessIter, RandomAccessIter, Tp *, Size, Compare);
}

void Gen005317B0(void **, void **, void *);
void bfmeGoDID(void **, void **, void *);

void Rva005336D0(int *first, int *last, Q4Sort00533470 comp)
{
	if (first != last)
	{
		int n = last - first;
		int k;
		for (k = 0; n != 1; n >>= 1)
			++k;
		_STL::__introsort_loop<int *, int, int, Q4Sort00533470>(
			first, last, (int *)0, k * 2, comp);
		if (last - first > 16)
		{
			Gen005317B0((void **)first, (void **)(first + 16), *(void **)&comp);
			bfmeGoDID((void **)(first + 16), (void **)last, *(void **)&comp);
		}
		else
			Gen005317B0((void **)first, (void **)last, *(void **)&comp);
	}
}
