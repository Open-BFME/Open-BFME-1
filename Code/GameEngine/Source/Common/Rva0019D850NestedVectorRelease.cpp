// cl: /EHsc
// stlport

#include <vector>

// The retail body is the STLport destructor for an outer vector whose element
// is itself a three-pointer vector.  The innermost payload is only constrained
// by the twelve-byte stride visible in the nested vector's deallocation math.
struct Rva0019D850Value
{
	int m_words[3];
};

template class _STL::vector< _STL::vector< Rva0019D850Value > >;
