// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x003AA980 copies a vector whose elements are eight bytes wide.
// Each element copy writes vtable 0x010EC76C and calls the copy routine at 0x00887B60.
// The native STLport vector instantiation reproduces this 172-byte body.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "ascii_string.h"

struct Gen_t_003a75c0_p8cd
{
	virtual ~Gen_t_003a75c0_p8cd() {}
	AsciiString m_member_4;
};

template class _STL::vector<Gen_t_003a75c0_p8cd>;
