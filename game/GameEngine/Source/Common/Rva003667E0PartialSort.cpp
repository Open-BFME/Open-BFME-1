// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// stlport

#include <algorithm>

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

void instantiateRva003667E0PartialSort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *middle, Rva00364980HeapElement *last,
	Rva00364980HeapCompare compare )
{
	_STL::partial_sort( first, middle, last, compare );
}
