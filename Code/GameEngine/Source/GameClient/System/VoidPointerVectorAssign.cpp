// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: emit the retail-picked vector<void*>::operator= instance at
// 0x003CF650. Same node-alloc static-STLport shape as
// ObjectVectorAssignThunk.cpp (vector<Object*> at 0x004A0890): the bodies
// differ only in the REL32 of _M_allocate_and_copy. That callee is the ILT
// thunk 0x0001A780 -> 0x003CEAE0, already tagged
// ??$_M_allocate_and_copy@PAPAX@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@IAEPAPAXIPAPAX0@Z
// on the gen-shim row. A named caller
// (Bfme5DropAndHandOver.cpp / BfmeSinkAB::bfmeTake) reaches this body
// through the ICF thunk at 0x00014E1B.

#include <vector>

// ??4?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEAAV01@ABV01@@Z
void ForceVoidPointerVectorAssign(_STL::vector<void *> &dst, const _STL::vector<void *> &src)
{
	dst = src;
}
