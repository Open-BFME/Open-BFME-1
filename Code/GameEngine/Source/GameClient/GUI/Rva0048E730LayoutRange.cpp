// cl: /DNDEBUG /MD
// Address-derived layout range at retail 0x0048E730.

class Rva0048E730Measure
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int measure();
};

struct Rva0048E730Element
{
	Rva0048E730Measure *m_measure;
	int m_unused;
	int m_offset;
};

class Rva0048E730Layout
{
public:
	Rva0048E730Layout( int offset ) : m_offset( offset ) {}
	void operator()( Rva0048E730Element *element )
	{
		element->m_offset = m_offset;
		m_offset += element->m_measure->measure();
	}

	int m_offset;
};

Rva0048E730Layout layoutRva0048E730( Rva0048E730Element **first,
	Rva0048E730Element **last, Rva0048E730Layout layout )
{
	while( first != last ) {
		layout( *first );
		++first;
	}
	return layout;
}
