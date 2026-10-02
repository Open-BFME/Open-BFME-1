// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

namespace _STL
{
	template <class RandomAccessIterator, class Value, class Distance,
		class Compare>
	void __introsort_loop( RandomAccessIterator first,
		RandomAccessIterator last, Value *pivot, Distance depthLimit,
		Compare compare );
}

void rva00366760FinalInsertionSort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare );

void rva00366FA0Sort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	if( first == last )
		return;

	int count = last - first;
	int depth = 0;
	while( count != 1 )
	{
		count >>= 1;
		++depth;
	}

	_STL::__introsort_loop<Rva00364980HeapElement *,
		Rva00364980HeapElement, int, Rva00364980HeapCompare>(
			first, last, 0, depth * 2, compare );
	rva00366760FinalInsertionSort( first, last, compare );
}
