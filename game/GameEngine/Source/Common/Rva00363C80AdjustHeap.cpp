// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	Rva00364980HeapElement( const Rva00364980HeapElement &other );
	~Rva00364980HeapElement();
	Rva00364980HeapElement &operator=(
		const Rva00364980HeapElement &other );

	char m_prefix[ 8 ];
	float m_priority;
	char m_suffix[ 0xB4 - 12 ];
};

struct Rva00364980HeapCompare
{
	bool operator()( const Rva00364980HeapElement &left,
		const Rva00364980HeapElement &right ) const
	{
		return left.m_priority < right.m_priority;
	}

	void *m_state;
};

void rva00362400PushHeap( Rva00364980HeapElement *first,
	int holeIndex, int topIndex, Rva00364980HeapElement value,
	Rva00364980HeapCompare compare );

void rva00363C80AdjustHeap( Rva00364980HeapElement *first,
	int holeIndex, int length, Rva00364980HeapElement value,
	Rva00364980HeapCompare compare )
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while( secondChild < length )
	{
		if( compare( first[ secondChild - 1 ], first[ secondChild ] ) )
			--secondChild;

		first[ holeIndex ] = first[ secondChild ];
		holeIndex = secondChild;
		secondChild = 2 * ( secondChild + 1 );
	}

	if( secondChild == length )
	{
		first[ holeIndex ] = first[ secondChild - 1 ];
		holeIndex = secondChild - 1;
	}

	rva00362400PushHeap( first, holeIndex, topIndex, value, compare );
}
