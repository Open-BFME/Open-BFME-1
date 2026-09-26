// stlport
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
#include <stl/_alloc.h>

void __stdcall rva00926700NodeDeallocate(void *node)
{
	if (node) {
		_STL::__node_alloc<true, 0>::deallocate(node, 16);
	}
}
