// Address-derived: int-scalar sibling of the eight-byte partial-sort family
// (Code/GameEngine/Source/Common/Rva00261920PartialSort.cpp). Same shape,
// element is a plain int and the comparator is a raw cdecl function pointer
// (retail calls it with `call ebp` directly, no vtable indirection).
// Callees, in body order: gen00483480 (already declared/pinned by
// ConstantZeroForwarders.cpp, zero-tail family), the still-unconverted
// int-heap-adjust body at 0x0047E4F0 (reached through ILT thunk 0x0004293D),
// and the still-unconverted sort-heap-finish body at 0x00483C20 (reached
// through ILT thunk 0x000103CA). Real STLport template identity not
// recovered.

typedef bool ( *GenIntLess )( int, int );

void gen00483480( void *first, void *last, void *compare, int zero, int alsoZero );
void gen0047E4F0( int *first, int holeIndex, int len, int value, GenIntLess comp );
void gen00483C20( void *first, void *last, void *compare );

void gen00483E00( void *firstArgument, void *middleArgument,
	void *lastArgument, int zero, void *compareArgument )
{
	int *first = (int *)firstArgument;
	int *middle = (int *)middleArgument;
	int *last = (int *)lastArgument;
	GenIntLess compare = (GenIntLess)compareArgument;

	gen00483480( first, middle, compare, 0, 0 );
	for( int *i = middle; i < last; ++i )
	{
		if( compare( *i, *first ) )
		{
			int item = *i;
			*i = *first;
			gen0047E4F0( first, 0, (int)( middle - first ), item, compare );
		}
	}
	gen00483C20( first, middle, compare );
}
