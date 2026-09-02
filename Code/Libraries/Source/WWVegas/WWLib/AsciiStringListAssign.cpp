// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// _STL::list<AsciiString>::operator= at retail 0x00507ED0.

#include "ascii_string.h"
#include <list>

void BfmeAsciiStringListAssign(_STL::list<AsciiString> *dst, const _STL::list<AsciiString> &src)
{
	*dst = src;
}
