// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/psplayerstats /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport

// Retail's PSPlayerStats map accessor uses the direct value-type constructor.
// Keep this STLport instantiation isolated from PersistentStorageThread.cpp,
// whose PreRTS include has already selected the VC7 default-constructor bug
// workaround before its map templates are parsed.
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <string>

#include "Lib/BaseType.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"

typedef _STL::map<Int, PSPlayerStats> PlayerStatsMap;

template PSPlayerStats &PlayerStatsMap::operator[](const Int &key);
