// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: emit the retail-picked vector<Object*>::operator= instance.
// Retail's linker kept an instantiation built against STLport's node
// allocator without the dllimport extern-template (inline 0x80 threshold,
// direct call to __node_alloc::_M_deallocate), while AIStates.cpp compiles
// with _STLP_USE_NEWALLOC + _STLP_USE_DECLSPEC and emits a different shape.
// This TU instantiates the template the way retail's picked instance was
// built; only the operator= COMDAT is claimed from it.

class Object;
#include <vector>

// ??4?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z
void ForceObjectPointerVectorAssign(_STL::vector<Object *> &dst, const _STL::vector<Object *> &src)
{
    dst = src;
}
