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

void rva00362360UnguardedLinearInsert( Rva00364980HeapElement *last,
	Rva00364980HeapElement value, Rva00364980HeapCompare compare );

void rva00363B80UnguardedInsertionSortAux( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement *,
	Rva00364980HeapCompare compare )
{
	for( Rva00364980HeapElement *current = first; current != last; ++current )
	{
		rva00362360UnguardedLinearInsert( current,
			Rva00364980HeapElement( *current ), compare );
	}
}
