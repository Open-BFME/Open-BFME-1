// cl: /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
#include <stl/_alloc.h>

void __cdecl operator delete(void *block);

extern "C" void __stdcall Rva14B450SizedBufferDeallocate(void *block, unsigned int count)
{
    if (block != 0) {
        unsigned int size = count * 12;
        if (size > 128) {
            operator delete(block);
        } else {
            _STL::__node_alloc<true, 0>::deallocate(block, size);
        }
    }
}
