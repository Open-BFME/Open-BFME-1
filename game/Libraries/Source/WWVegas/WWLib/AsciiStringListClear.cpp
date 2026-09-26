// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// _STL::list<AsciiString>::clear at retail 0x000800C0.  The direct symbol
// identity is established by the map<AsciiString, list<AsciiString>> caller
// at 0x00082104 and the BFMEDisconnectManager update caller at 0x0066CBDF;
// the body walks 0xc-byte nodes, destroys the AsciiString at node+8, and
// uses the already matched STLport node allocator deallocator.

#include "ascii_string.h"
#include <list>

template class _STL::list<AsciiString>;
