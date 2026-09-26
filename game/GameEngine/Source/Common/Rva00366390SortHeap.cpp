// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

void rva00364980PopHeapAuxCall( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement *,
	Rva00364980HeapCompare compare );

void rva00366390SortHeap( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	while( last - first > 1 )
		rva00364980PopHeapAuxCall( first, last--, 0, compare );
}
