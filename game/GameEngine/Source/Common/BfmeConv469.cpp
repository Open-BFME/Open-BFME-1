// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <hash_map>

void __stdcall bfmeGoBIB(void *what)
{
	if (what != 0)
		_STL::__node_alloc<true, 0>::deallocate(what, 0x68);
}
