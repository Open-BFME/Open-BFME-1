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

void rva00363C80AdjustHeap( Rva00364980HeapElement *first,
	int holeIndex, int length, Rva00364980HeapElement value,
	Rva00364980HeapCompare compare );

void rva003648E0MakeHeap( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	int length = last - first;
	if( length < 2 )
		return;

	int parent = ( length - 2 ) / 2;
	for( ;; )
	{
		rva00363C80AdjustHeap( first, parent, length,
			Rva00364980HeapElement( first[ parent ] ), compare );
		if( parent == 0 )
			return;

		--parent;
	}
}
