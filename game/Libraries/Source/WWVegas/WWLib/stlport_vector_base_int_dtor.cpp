// ??1?$_Vector_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// Emit only the retail-owned destructor; the unrelated constructor conflicts.
template _STL::_Vector_base<int, _STL::allocator<int> >::~_Vector_base();
