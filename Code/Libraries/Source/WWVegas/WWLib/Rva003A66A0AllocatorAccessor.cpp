// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Retail vector copy 0x003AA980 puts its source in ECX and pushes the allocator result slot before calling ILT 0x00013FC5.
// The ILT jumps to 0x003A66A0, whose body returns the result slot in EAX with ret 4.
// This member instantiation keeps STLport's real get_allocator identity for the address-derived element type.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

struct Gen_t_003a75c0_p8cd;

template _STL::vector<Gen_t_003a75c0_p8cd>::allocator_type
_STL::vector<Gen_t_003a75c0_p8cd>::get_allocator() const;
