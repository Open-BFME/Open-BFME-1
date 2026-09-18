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

void rva00362360UnguardedLinearInsert( Rva00364980HeapElement *last,
	Rva00364980HeapElement value, Rva00364980HeapCompare compare )
{
	Rva00364980HeapElement *next = last;
	--next;
	while( compare( value, *next ) )
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}
