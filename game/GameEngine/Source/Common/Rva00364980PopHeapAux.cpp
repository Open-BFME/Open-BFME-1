// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	Rva00364980HeapElement( const Rva00364980HeapElement &other );
	~Rva00364980HeapElement();

	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

void rva003647E0PopHeap( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement *result,
	Rva00364980HeapElement value, Rva00364980HeapCompare compare, int * );

void rva00364980PopHeapAux( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement *,
	Rva00364980HeapCompare compare )
{
	rva003647E0PopHeap( first, last - 1, last - 1,
		Rva00364980HeapElement( *( last - 1 ) ), compare, 0 );
}
