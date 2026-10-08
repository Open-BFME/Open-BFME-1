// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// The ILT at 0x00009C28 names this body as vector<void *>::get_allocator (ilt_oracle CONFIRMED, exact).
// The ILT jumps to 0x000665A0, whose seven bytes return the hidden result slot in EAX with ret 4.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

template _STL::vector<void *>::allocator_type _STL::vector<void *>::get_allocator() const;
