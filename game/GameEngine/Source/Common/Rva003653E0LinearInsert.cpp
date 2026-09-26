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

struct Rva003653E0RandomAccessIteratorTag
{
};

Rva00364980HeapElement *rva003624E0CopyBackward(
	Rva00364980HeapElement *first, Rva00364980HeapElement *last,
	Rva00364980HeapElement *result,
	const Rva003653E0RandomAccessIteratorTag &, int * );

void rva00362360UnguardedLinearInsert( Rva00364980HeapElement *last,
	Rva00364980HeapElement value, Rva00364980HeapCompare compare );

void rva003653E0LinearInsert( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement value,
	Rva00364980HeapCompare compare )
{
	if( compare( value, *first ) )
	{
		Rva003653E0RandomAccessIteratorTag iteratorTag;
		rva003624E0CopyBackward( first, last, last + 1,
			iteratorTag, 0 );
		*first = value;
	}
	else
	{
		rva00362360UnguardedLinearInsert( last, value, compare );
	}
}
