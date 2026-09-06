// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// _STL::list<AsciiString>::clear at retail 0x000800C0.  The direct symbol
// identity is established by the map<AsciiString, list<AsciiString>> caller
// at 0x00082104 and the BFMEDisconnectManager update caller at 0x0066CBDF;
// the body walks 0xc-byte nodes, destroys the AsciiString at node+8, and
// uses the already matched STLport node allocator deallocator.

// Open-BFME7: copy of AsciiStringListClear.cpp built with the array/scalar delete declared
// nothrow (docs/shape_levers.md): retail 0x0009F630 (133 bytes) is the list<AsciiString>
// sized constructor as that TU compiled it; only that body is claimed here.
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include "ascii_string.h"
#include <list>

template class _STL::list<AsciiString>;
