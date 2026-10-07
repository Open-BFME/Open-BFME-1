// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// STLport vector<unsigned int> copy constructor, retail 0x003D3A00 (76 bytes).
// ilt_oracle CONFIRMS this decorated name at 0x003D3A00, and the two
// out-of-line callees it reaches: get_allocator at 0x003D32D0 (ILT
// 0x0002CE4E) and the _Vector_base constructor at 0x003D3540 (ILT 0x0000799B).
// A search of 176,314 candidate element types found no other type that fits
// any two of the three slots. The element is trivially copyable, so the copy
// is one memmove through the MSVCR71 import.

#include <vector>

template _STL::vector<unsigned int, _STL::allocator<unsigned int> >::vector(
	const _STL::vector<unsigned int, _STL::allocator<unsigned int> > &other);
