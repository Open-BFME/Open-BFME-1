// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME7: the string-keyed map insert_unique of the ping thread (retail 0x0064C4C0,
// 292 bytes).  PingThread.cpp emits it one byte off because retail's tree insert passes
// the hint node twice to _M_insert (_BFME_RETAIL_TREE_INSERT_LAYOUT); the port TU cannot
// take the define without disturbing its other rows, so the instantiation lives here with
// the same include block.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define Matrix4x4 Matrix4  // BFME renamed it
#define _STLP_USE_STATIC_LIB
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <winsock.h>	// This one has to be here. Prevents collisions with windsock2.h
#include "GameNetwork/GameSpy/PingThread.h"
#include "mutex.h"
#include "thread.h"
#include "Common/StackDump.h"
#include "Common/SubsystemInterface.h"

typedef _STL::map<_STL::string, int> Rva0064C4C0Map;
template _STL::pair<Rva0064C4C0Map::iterator, bool> Rva0064C4C0Map::_Rep_type::insert_unique(const Rva0064C4C0Map::value_type &);
