// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /GX- /MD /Iinputs/reference/shims/ini /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x009CC6C0 / 0x009CCAA0 are byte-identical cdecl STL copy wrappers:
// they forward (first, last, out) plus the null tag-pointer and guard slot
// into the pinned tree-iterator __copy at 0x009CC4C0 and clean 0x18 bytes of
// stack. The free-function spelling is what emits retail's `push ecx /
// mov ecx,[esp+0x10] / mov edx,[esp+0xC] / push 0 / lea eax,[esp+7] /
// push eax / ... / add esp,0x18 / ret` form; the member-function spelling
// drops the guard slot and reorders the loads. The iterator element type is
// plain AsciiString (the callee ledger spelling carries the
// _Rb_tree_iterator/VAsciiString/Const_traits decoration), and the callee at
// 0x009CC4C0 is a matched real-source body, so no new pin is needed.
// IDENTITY IS NOT RECOVERED: the wrappers keep their address tokens and land
// under distinct opaque names (one-identity rule).
#include "Common/AsciiString.h"
#include <set>

AsciiString * __cdecl Rva009CC6C0Copy(_STL::set<AsciiString>::iterator first,
	_STL::set<AsciiString>::iterator last, AsciiString *out)
{
	return _STL::copy(first, last, out);
}

AsciiString * __cdecl Rva009CCAA0Copy(_STL::set<AsciiString>::iterator first,
	_STL::set<AsciiString>::iterator last, AsciiString *out)
{
	return _STL::copy(first, last, out);
}
