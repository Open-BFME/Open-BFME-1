// cl: -GX-
//
// Retail 0x00515780 is STLport's scalar sort driver. The Q4Sort005156D0
// introsort body at 0x005156D0 and the two final-insertion callees at
// 0x005139E0 and 0x00513A30 identify this address-derived driver. The retail
// call sites use ILT thunks 0x0001D660, 0x0003380C, and 0x000030F3.

struct Q4Sort005156D0
{
	void *m_state;
	bool operator()( int, int ) const;
};

namespace _STL
{
	template <class RandomAccessIter, class Tp, class Size, class Compare>
	void __introsort_loop( RandomAccessIter, RandomAccessIter, Tp *, Size, Compare );
}

void Gen005139E0( void **, void **, void * );
void bfmeGoDIB( void **, void **, void * );

void Rva00515780( int *first, int *last, Q4Sort005156D0 comp )
{
	if( first != last )
	{
		int length = last - first;
		int n = last - first;
		int k;
		for( k = 0; n != 1; n >>= 1 )
			++k;
		_STL::__introsort_loop<int *, int, int, Q4Sort005156D0>(
			first, last, (int *)0, k * 2, comp );
		if( length > 16 )
		{
			Gen005139E0( (void **)first, (void **)( first + 16 ), *(void **)&comp );
			bfmeGoDIB( (void **)( first + 16 ), (void **)last, *(void **)&comp );
		}
		else
			Gen005139E0( (void **)first, (void **)last, *(void **)&comp );
	}
}
