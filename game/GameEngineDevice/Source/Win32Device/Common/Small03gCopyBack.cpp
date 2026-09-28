// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /GX- /MD /Iinputs/reference/shims/ini /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x009CC570 / 0x009CC6F0 are byte-identical cdecl STL copy_backward
// wrappers: they forward (first, last, out) plus the null tag-pointer and
// guard slot into the pointer copy_backward at 0x003C4EA0 (reached through
// the ILT thunk at 0x0000FD9E) and clean 0x18 bytes of stack. The iterator
// arguments are plain AsciiString pointers (the callee ledger spelling is
// the PAVAsciiString random-access overload); declaring set iterators pulls
// in the tree-iterator bidirectional overload instead and leaves an
// unresolved call. Same free-function spelling as the Small03gCopyWrap copy
// twins. The callee is a matched real-source body, so no new pin is needed.
// IDENTITY IS NOT RECOVERED: the wrappers keep their address tokens and land
// under distinct opaque names (one-identity rule).
#include "Common/AsciiString.h"
#include <vector>

AsciiString * __cdecl Rva009CC570CopyB(AsciiString *first, AsciiString *last,
	AsciiString *out)
{
	return _STL::copy_backward(first, last, out);
}

AsciiString * __cdecl Rva009CC6F0CopyB(AsciiString *first, AsciiString *last,
	AsciiString *out)
{
	return _STL::copy_backward(first, last, out);
}
