// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// _STL::list<UnicodeString>::operator= at retail 0x005673A0.

#include <wchar.h>
#include "../../../../../inputs/reference/shims/stringbaseunicode/Common/UnicodeString.h"
#include <list>

void BfmeUnicodeStringListAssign(_STL::list<UnicodeString> *dst, const _STL::list<UnicodeString> &src)
{
	*dst = src;
}
