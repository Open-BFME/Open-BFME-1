// ?_M_fill_insert@?$vector@UICoord2D@@V?$allocator@UICoord2D@@@_STL@@@_STL@@QAEXPAUICoord2D@@IABU3@@Z
// partial score=0.96 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: instantiate the authentic STLport vector fill-insert body.

#define _STLP_NO_EXCEPTIONS 1
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include <vector>

struct ICoord2D
{
    int x;
    int y;
};

template void _STL::vector<ICoord2D, _STL::allocator<ICoord2D> >::_M_fill_insert(
    ICoord2D *, unsigned int, const ICoord2D &);
