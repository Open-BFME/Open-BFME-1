// cl: /DNDEBUG /MD /EHsc
// stlport
// ?_M_fill_insert@?$vector@UICoord2D@@V?$allocator@UICoord2D@@@_STL@@@_STL@@QAEXPAUICoord2D@@IABU3@@Z
// Open-BFME: instantiate the authentic STLport vector fill-insert body.
//
// The previous source was a naked __emit lift of the retail dump.  This is
// the vendor STLport implementation itself; the resize callers and ILT
// 0x000160C2 independently establish the ICoord2D element type and ABI.

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
