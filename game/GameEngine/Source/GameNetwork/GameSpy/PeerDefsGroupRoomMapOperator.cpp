// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// The retail body at 0x006357D0 implements GroupRoomMap::operator[].
// GameSpyInfo::addGroupRoom calls this map through m_groupRooms[room.m_groupID].
// The existing insert_unique body at 0x00633BB0 and the 0x20-byte
// GameSpyGroupRoom layout identify this STLport instantiation.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include "StringInline.h"

typedef int Int;

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom();
	GameSpyGroupRoom( const GameSpyGroupRoom &other );

	AsciiString m_name;
	UnicodeString m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
	Int m_bfmeExtra;
};

extern void j_00035f03();
#pragma comment(linker, "/alternatename:??0GameSpyGroupRoom@@QAE@ABV0@@Z=?j_00035f03@@YAXXZ")

typedef std::map<Int, GameSpyGroupRoom> GroupRoomMap;

template GameSpyGroupRoom &GroupRoomMap::operator[]( const Int &key );
