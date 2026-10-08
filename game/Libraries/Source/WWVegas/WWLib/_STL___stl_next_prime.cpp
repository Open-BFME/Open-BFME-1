// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport's __stl_next_prime at 0x00852190 (50 B; a gap in the
// INI region): lower_bound over the 28-entry prime table (_Stl_prime<bool>::
// _M_list at VA 0x01075870) returning the last prime (4294967291 folded to
// the immediate) when the request is past the end.  The bound search is the
// FXList.cpp __lower_bound instantiation already in the ledger.

#include <algorithm>
#include <hash_map>

namespace _STL
{

// ?__stl_next_prime@_STL@@YGII@Z
size_t __stdcall __stl_next_prime( size_t n )
{
	const size_t *first = (const size_t *)_Stl_prime<bool>::_M_list;
	const size_t *last = first + 28;
	// STLport 4.6's hashtable::_M_next_size spelling: lower_bound() would build
	// a __less_2 temporary on the stack that retail does not have.
	const size_t *pos = __lower_bound( first, last, n, __less( (size_t *)0 ), (ptrdiff_t *)0 );
	return pos == last ? *( last - 1 ) : *pos;
}

}
