// cl: /DNDEBUG /MD
// Address-derived layout range at retail 0x0048E790, the two-field sibling of
// the range at 0x0048E730 that sits directly above it.

struct Rva0048E790Element
{
	int m_unused000[ 3 ];
	int m_extent;
	int m_offset;
	int m_depth;
};

class Rva0048E790Layout
{
public:
	Rva0048E790Layout( int offset, int depth )
		: m_offset( offset ), m_depth( depth ) {}
	void operator()( Rva0048E790Element *element )
	{
		element->m_offset = m_offset;
		element->m_depth = m_depth;
		m_offset += element->m_extent;
	}

	int m_offset;
	int m_depth;
};

Rva0048E790Layout layoutRva0048E790( Rva0048E790Element **first,
	Rva0048E790Element **last, Rva0048E790Layout layout )
{
	while( first != last ) {
		layout( *first );
		++first;
	}
	return layout;
}
