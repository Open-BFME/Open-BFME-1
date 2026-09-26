// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

void rva00366320InsertionSortCall( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare );

void rva00363B80UnguardedInsertionSortAuxCall(
	Rva00364980HeapElement *first, Rva00364980HeapElement *last,
	Rva00364980HeapElement *, Rva00364980HeapCompare compare );

void rva00366760FinalInsertionSort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	if( last - first > 16 )
	{
		Rva00364980HeapElement *middle = first + 16;
		rva00366320InsertionSortCall( first, middle, compare );
		rva00363B80UnguardedInsertionSortAuxCall( middle, last, 0, compare );
	}
	else
	{
		rva00366320InsertionSortCall( first, last, compare );
	}
}
