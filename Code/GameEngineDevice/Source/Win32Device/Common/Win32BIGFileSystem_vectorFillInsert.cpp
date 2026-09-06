// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: STLport bodies of the BIG-file system as built in a retail TU with STLport
// exceptions off and nothrow deletes (docs/shape_levers.md); same include block as
// Win32BIGFileSystem_loadBigFiles.cpp, which cannot carry the defines itself.
#define _STLP_NO_EXCEPTIONS 1
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include "Common/AsciiString.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

template void _STL::vector<AsciiString, _STL::allocator<AsciiString> >::_M_fill_insert(AsciiString *, unsigned int, const AsciiString &);
