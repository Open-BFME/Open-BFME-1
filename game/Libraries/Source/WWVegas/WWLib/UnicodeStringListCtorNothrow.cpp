// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The 133-byte sized-list body at retail 0x0009F630 constructs the
// list<UnicodeString> sentinel used by SkirmishPreferences::m_userNames.
// Its exception cleanup calls StringBase<wchar_t>::releaseBuffer at
// 0x008881D0, distinguishing this specialization from the narrow list body.

#include <wchar.h>
#include "../../../../../inputs/reference/shims/stringbaseunicode/Common/UnicodeString.h"
#include <list>

template class _STL::list<UnicodeString>;
