// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"
#include <utility>

template _STL::pair<int, AsciiString>
_STL::make_pair<int, AsciiString>(const int &, const AsciiString &);
