// cl: /EHsc
// stlport

#include <vector>

// Address-derived 60-byte element.  Its out-of-line destructor is pinned to
// the callee encoded by the retail vector destructor at 0x003D1380.
struct Gen003D1380Elem
{
	char m_body[ 0x3C ];

	Gen003D1380Elem();
	Gen003D1380Elem( const Gen003D1380Elem & );
	~Gen003D1380Elem();
	Gen003D1380Elem &operator=( const Gen003D1380Elem & );
};

template class _STL::vector<Gen003D1380Elem>;
