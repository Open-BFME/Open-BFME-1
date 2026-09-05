// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// _STL::list<UnicodeString>::operator= at retail 0x005673A0.

#include <wchar.h>
#include "../../../../../reference/shims/stringbaseunicode/Common/UnicodeString.h"
#include <list>

void BfmeUnicodeStringListAssign(_STL::list<UnicodeString> *dst, const _STL::list<UnicodeString> &src)
{
	*dst = src;
}
