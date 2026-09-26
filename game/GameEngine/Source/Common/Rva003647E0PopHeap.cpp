// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	Rva00364980HeapElement( const Rva00364980HeapElement &other );
	~Rva00364980HeapElement();
	Rva00364980HeapElement &operator=(
		const Rva00364980HeapElement &other );

	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

void rva00363C80AdjustHeap( Rva00364980HeapElement *first,
	int holeIndex, int length, Rva00364980HeapElement value,
	Rva00364980HeapCompare compare );

void rva003647E0PopHeap( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement *result,
	Rva00364980HeapElement value, Rva00364980HeapCompare compare, int * )
{
	*result = *first;
	rva00363C80AdjustHeap( first, 0, last - first, value, compare );
}
