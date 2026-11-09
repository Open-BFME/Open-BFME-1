// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

// Out-of-line STLport vector<void*> members that the /Od vector<void*>::_M_fill_assign
// 0x0082EF90 calls (identity_evidence/0082ef90-vector-voidptr-fill-assign.md):
//   erase(first, last)  0x000CF750 via ILT 0x00002A3B
//   swap                0x00066F00 via ILT 0x000063E3
//   ~_Vector_base       0x00066C30 via ILT 0x00031647

template void **_STL::vector<void *, _STL::allocator<void *> >::erase(void **, void **);
template void _STL::vector<void *, _STL::allocator<void *> >::swap(_STL::vector<void *, _STL::allocator<void *> > &);
template _STL::_Vector_base<void *, _STL::allocator<void *> >::~_Vector_base();
