// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// Retail calls vector<bool>::_M_initialize through its already pinned ILT and
// then fills every allocated word, exactly as STLport 4.5.3 defines this ctor.
template _STL::vector<bool, _STL::allocator<bool> >::vector(
	unsigned int,
	bool,
	const _STL::allocator<bool> &);
