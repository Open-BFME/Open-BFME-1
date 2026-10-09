// Address-derived: int-scalar sibling of the eight-byte partial-sort family
// (game/GameEngine/Source/Common/Rva00261920PartialSort.cpp). Same shape,
// element is a plain int and the comparator is a raw cdecl function pointer
// (retail calls it with `call ebp` directly, no vtable indirection).
// Callees, in body order: matched Rva00483480 (zero-tail family),
// the matched int-heap-adjust specialization at 0x0047E4F0
// (reached through ILT thunk 0x0004293D),
// and the sort-heap-finish body at 0x00483C20 (reached
// through ILT thunk 0x000103CA). Real STLport template identity not
// recovered.

typedef bool ( *GenIntLess )( int, int );

struct Q3HeapCompare { void *m_state; };
void Rva00483480(int **first, int **last, Q3HeapCompare compare);
namespace _STL
{
template <class Iterator, class Distance, class Value, class Compare>
void __adjust_heap(Iterator, Distance, Distance, Value, Compare);
}
void gen00483C20( void *first, void *last, void *compare );

void gen00483E00( void *firstArgument, void *middleArgument,
	void *lastArgument, int zero, void *compareArgument )
{
	int *first = (int *)firstArgument;
	int *middle = (int *)middleArgument;
	int *last = (int *)lastArgument;
	GenIntLess compare = (GenIntLess)compareArgument;

	// The matched heap primitive reads only the first three stack dwords;
    // preserve the retail caller's two unused trailing tag arguments.
    reinterpret_cast<void (__cdecl *)(int *, int *, GenIntLess, int, int)>(
        &Rva00483480)(first, middle, compare, 0, 0);
	for( int *i = middle; i < last; ++i )
	{
		if( compare( *i, *first ) )
		{
			int item = *i;
			*i = *first;
			_STL::__adjust_heap(first, 0, (int)(middle - first), item, compare);
		}
	}
	gen00483C20( first, middle, compare );
}

void gen00483C20( void *firstArgument, void *lastArgument, void *compareArgument )
{
	int *first = (int *)firstArgument;
	int *last = (int *)lastArgument;
	GenIntLess compare = (GenIntLess)compareArgument;

	while( last - first > 1 )
	{
		int item = *( last - 1 );
		*( last - 1 ) = *first;
		_STL::__adjust_heap(first, 0, (int)((last - 1) - first), item, compare);
		--last;
	}
}
