// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"
#include <utility>

template _STL::pair<int, AsciiString>
_STL::make_pair<int, AsciiString>(const int &, const AsciiString &);
