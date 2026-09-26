// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	Rva00364980HeapElement( const Rva00364980HeapElement &other );
	~Rva00364980HeapElement();
	Rva00364980HeapElement &operator=(
		const Rva00364980HeapElement &other );
	float priority() const
	{
		return m_priority;
	}

	char m_prefix[ 8 ];
	float m_priority;
	char m_suffix[ 0xB4 - 12 ];
};

struct Rva00364980HeapCompare
{
	bool operator()( const Rva00364980HeapElement &left,
		const Rva00364980HeapElement &right ) const
	{
		return left.priority() > right.priority();
	}

	void *m_state;
};

void rva00363BE0IterSwap( Rva00364980HeapElement *left,
	Rva00364980HeapElement *right );

Rva00364980HeapElement *rva00365320UnguardedPartition(
	Rva00364980HeapElement *first, Rva00364980HeapElement *last,
	Rva00364980HeapElement pivot, Rva00364980HeapCompare compare )
{
	for( ;; )
	{
		while( compare( *first, pivot ) )
			++first;

		--last;
		while( compare( pivot, *last ) )
			--last;

		if( first >= last )
			return first;

		rva00363BE0IterSwap( first, last );
		++first;
	}
}
