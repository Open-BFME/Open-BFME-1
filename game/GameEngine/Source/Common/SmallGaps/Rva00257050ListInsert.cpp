// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Address-derived: std::list<T>::insert(iterator, const T&) for an 8-byte
// value type (two ints/floats) -- allocate a 0x10-byte node (0x8 link header
// + 8-byte value), copy the value in, and splice it in front of `position`.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva00257050Value
{
	int a;
	int b;
};

template _STL::list<Rva00257050Value>::iterator
_STL::list<Rva00257050Value>::insert(_STL::list<Rva00257050Value>::iterator, Rva00257050Value const&);
