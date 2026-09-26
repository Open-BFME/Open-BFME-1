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

void rva003653E0LinearInsert( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement value,
	Rva00364980HeapCompare compare );

void rva00366320InsertionSort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	if( first == last )
		return;

	for( Rva00364980HeapElement *current = first + 1;
		current != last; ++current )
	{
		rva003653E0LinearInsert( first, current,
			Rva00364980HeapElement( *current ), compare );
	}
}
