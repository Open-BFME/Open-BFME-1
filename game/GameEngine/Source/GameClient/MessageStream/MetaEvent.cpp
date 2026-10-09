// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: MetaEvent.cpp ////////////////////////////////////////////////////////////////////////////
// Created:    Colin Day, September 2001
// Desc:       Translating keystrokes into event command messages
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/INI.h"
#include "Common/MessageStream.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"

#include "GameClient/Drawable.h"
#include "GameClient/Mouse.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/ParticleSys.h"	// for ParticleSystemDebugDisplay
#include "GameClient/Shell.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/DebugDisplay.h"	// for AudioDebugDisplay
#include "GameClient/GameText.h"
#include "GameClient/MetaEvent.h"

#include "GameLogic/GameLogic.h" // for TheGameLogic->getFrame()


#define dont_DUMP_ALL_KEYS_TO_LOG


#ifdef DUMP_ALL_KEYS_TO_LOG
#include "GameClient\Keyboard.h"
#endif

MetaMap *TheMetaMap = NULL;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////

// BFME message names and values from the retail table at VA 0x0110E1D8.
static const LookupListRec GameMessageMetaTypeNames[] =
{
	{ "SAVE_VIEW1", 33 },
	{ "SAVE_VIEW2", 34 },
	{ "SAVE_VIEW3", 35 },
	{ "SAVE_VIEW4", 36 },
	{ "SAVE_VIEW5", 37 },
	{ "SAVE_VIEW6", 38 },
	{ "SAVE_VIEW7", 39 },
	{ "SAVE_VIEW8", 40 },
	{ "VIEW_VIEW1", 41 },
	{ "VIEW_VIEW2", 42 },
	{ "VIEW_VIEW3", 43 },
	{ "VIEW_VIEW4", 44 },
	{ "VIEW_VIEW5", 45 },
	{ "VIEW_VIEW6", 46 },
	{ "VIEW_VIEW7", 47 },
	{ "VIEW_VIEW8", 48 },
	{ "CREATE_TEAM0", 49 },
	{ "CREATE_TEAM1", 50 },
	{ "CREATE_TEAM2", 51 },
	{ "CREATE_TEAM3", 52 },
	{ "CREATE_TEAM4", 53 },
	{ "CREATE_TEAM5", 54 },
	{ "CREATE_TEAM6", 55 },
	{ "CREATE_TEAM7", 56 },
	{ "CREATE_TEAM8", 57 },
	{ "CREATE_TEAM9", 58 },
	{ "SELECT_TEAM0", 59 },
	{ "SELECT_TEAM1", 60 },
	{ "SELECT_TEAM2", 61 },
	{ "SELECT_TEAM3", 62 },
	{ "SELECT_TEAM4", 63 },
	{ "SELECT_TEAM5", 64 },
	{ "SELECT_TEAM6", 65 },
	{ "SELECT_TEAM7", 66 },
	{ "SELECT_TEAM8", 67 },
	{ "SELECT_TEAM9", 68 },
	{ "ADD_TEAM0", 69 },
	{ "ADD_TEAM1", 70 },
	{ "ADD_TEAM2", 71 },
	{ "ADD_TEAM3", 72 },
	{ "ADD_TEAM4", 73 },
	{ "ADD_TEAM5", 74 },
	{ "ADD_TEAM6", 75 },
	{ "ADD_TEAM7", 76 },
	{ "ADD_TEAM8", 77 },
	{ "ADD_TEAM9", 78 },
	{ "VIEW_TEAM0", 79 },
	{ "VIEW_TEAM1", 80 },
	{ "VIEW_TEAM2", 81 },
	{ "VIEW_TEAM3", 82 },
	{ "VIEW_TEAM4", 83 },
	{ "VIEW_TEAM5", 84 },
	{ "VIEW_TEAM6", 85 },
	{ "VIEW_TEAM7", 86 },
	{ "VIEW_TEAM8", 87 },
	{ "VIEW_TEAM9", 88 },
	{ "SELECT_MATCHING_UNITS", 89 },
	{ "SELECT_NEXT_UNIT", 90 },
	{ "SELECT_PREV_UNIT", 91 },
	{ "SELECT_NEXT_WORKER", 92 },
	{ "SELECT_PREV_WORKER", 93 },
	{ "VIEW_HOME_BASE", 94 },
	{ "VIEW_LAST_RADAR_EVENT", 95 },
	{ "SELECT_HERO", 96 },
	{ "SELECT_ALL", 97 },
	{ "SCATTER", 98 },
	{ "STOP", 99 },
	{ "DEPLOY", 100 },
	{ "CREATE_FORMATION", 101 },
	{ "AUTO_SAVE", 102 },
	{ "FOLLOW", 103 },
	{ "CHAT_PLAYERS", 104 },
	{ "CHAT_BUDDIES", 105 },
	{ "CHAT_ALLIES", 106 },
	{ "CHAT_EVERYONE", 107 },
	{ "DIPLOMACY", 108 },
	{ "OPTIONS", 109 },
	{ "TOGGLE_LOWER_DETAILS", 110 },
	{ "TOGGLE_CONTROL_BAR", 111 },
	{ "BEGIN_PATH_BUILD", 112 },
	{ "END_PATH_BUILD", 113 },
	{ "BEGIN_FORCEATTACK", 114 },
	{ "END_FORCEATTACK", 115 },
	{ "BEGIN_FORCEMOVE", 116 },
	{ "END_FORCEMOVE", 117 },
	{ "BEGIN_WAYPOINTS", 118 },
	{ "END_WAYPOINTS", 119 },
	{ "BEGIN_PREFER_SELECTION", 120 },
	{ "END_PREFER_SELECTION", 121 },
	{ "TAKE_SCREENSHOT", 122 },
	{ "ALL_CHEER", 123 },
	{ "TOGGLE_ATTACKMOVE", 124 },
	{ "BEGIN_CAMERA_ROTATE_LEFT", 125 },
	{ "END_CAMERA_ROTATE_LEFT", 126 },
	{ "BEGIN_CAMERA_ROTATE_RIGHT", 127 },
	{ "END_CAMERA_ROTATE_RIGHT", 128 },
	{ "BEGIN_CAMERA_ZOOM_IN", 129 },
	{ "END_CAMERA_ZOOM_IN", 130 },
	{ "BEGIN_CAMERA_ZOOM_OUT", 131 },
	{ "END_CAMERA_ZOOM_OUT", 132 },
	{ "CAMERA_RESET", 133 },
	{ "BEGIN_CAMERA_SCROLL_LEFT", 134 },
	{ "END_CAMERA_SCROLL_LEFT", 135 },
	{ "BEGIN_CAMERA_SCROLL_RIGHT", 136 },
	{ "END_CAMERA_SCROLL_RIGHT", 137 },
	{ "BEGIN_CAMERA_SCROLL_UP", 138 },
	{ "END_CAMERA_SCROLL_UP", 139 },
	{ "BEGIN_CAMERA_SCROLL_DOWN", 140 },
	{ "END_CAMERA_SCROLL_DOWN", 141 },
	{ "PLACE_BEACON", 142 },
	{ "DELETE_BEACON", 143 },
	{ "SPELL_STORE", 144 },
	{ "DEMO_PERFORM_STATISTICAL_DUMP", 145 },
	{ "TOGGLE_FAST_FORWARD_MODE", 146 },
	{ NULL, 0 }
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
extern const FieldParse TheMetaMapFieldParseTable[];

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
MetaEventTranslator::MetaEventTranslator() : 
	m_lastKeyDown(MK_NONE),
	m_lastModState(0)
{
	UnsignedByte *base = (UnsignedByte *)this;
	for (Int i = 0; i < NUM_MOUSE_BUTTONS; ++i) {
		*(Bool *)(base + 0x24 + i) = FALSE;
		Int *mousePosition = (Int *)(base + 0x10 + i * 8);
		mousePosition[-1] = 0;
		mousePosition[0] = 0;
	}
}

//-------------------------------------------------------------------------------------------------
MetaEventTranslator::~MetaEventTranslator()
{
}

//-------------------------------------------------------------------------------------------------
static const char * findGameMessageNameByType(GameMessage::Type type)
{
	for (const LookupListRec* metaNames = GameMessageMetaTypeNames; metaNames->name; metaNames++)
		if (metaNames->value == (Int)type)
			return metaNames->name;

	DEBUG_CRASH(("MetaTypeName %d not found -- did you remember to add it to GameMessageMetaTypeNames[] ?\n"));
	return "???";
}

//-------------------------------------------------------------------------------------------------
// BFME translation: verified vtable VA 0x0110F050 slot 0 -> ILT
// 0x0000C248 -> RVA 0x005B6BA0. The following views retain retail offsets
// without changing the Zero Hour interfaces used by the other methods.
namespace Rva005B6BA0MessageTypes {
const GameMessage::Type RawKeyDown = (GameMessage::Type)21;
const GameMessage::Type RawKeyUp = (GameMessage::Type)22;
const GameMessage::Type RawMouseEnd = (GameMessage::Type)20;
const GameMessage::Type MiddleDown = (GameMessage::Type)10;
const GameMessage::Type MiddleDoubleClick = (GameMessage::Type)11;
const GameMessage::Type MiddleUp = (GameMessage::Type)12;
const GameMessage::Type RightDown = (GameMessage::Type)14;
const GameMessage::Type RightDoubleClick = (GameMessage::Type)15;
const GameMessage::Type RightUp = (GameMessage::Type)16;
const GameMessage::Type LeftClick = (GameMessage::Type)23;
const GameMessage::Type LeftDoubleClick = (GameMessage::Type)24;
const GameMessage::Type MiddleClick = (GameMessage::Type)25;
const GameMessage::Type MiddleClickDouble = (GameMessage::Type)26;
const GameMessage::Type RightClick = (GameMessage::Type)27;
const GameMessage::Type RightClickDouble = (GameMessage::Type)28;
}

// Retail MetaMapRec has no MemoryPoolObject vptr; its witnessed fields
// are m_next +0, m_meta +4, m_key +8, transition +C, modifiers +10, usable +14.
struct Rva005B6BA0MapView {
 const Rva005B6BA0MapView *m_next;
 GameMessage::Type m_meta;
 MappableKeyType m_key;
 MappableKeyTransition m_transition;
 MappableKeyModState m_modState;
 CommandUsableInType m_usableIn;
};
struct Rva005B6BA0StreamView {
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual void slot2C();
 virtual void slot30();
 virtual GameMessage *appendMessage(GameMessage::Type);
 virtual GameMessage *insertMessage(GameMessage::Type, GameMessage *);
};
// The client LivingWorld singleton cell at VA 0x012F7048, defined once by
// game/GameEngine/Source/GameClient/LivingWorld.cpp.  Declared here under the
// canonical name and type so the linked build has one mangled symbol.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;
GameMessageDisposition MetaEventTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;
	GameMessage::Type t = msg->getType();

	if (t == Rva005B6BA0MessageTypes::RawKeyDown || t == Rva005B6BA0MessageTypes::RawKeyUp)
	{
		MappableKeyType key = (MappableKeyType)msg->getArgument(0)->integer;
		Int keyState = msg->getArgument(1)->integer;

		// for our purposes here, we don't care to distinguish between right and left keys,
		// so just fudge a little to simplify things.
		Int newModState = 0;

		if( keyState & KEY_STATE_CONTROL )
		{
			newModState |= CTRL;
		}

		if( keyState & KEY_STATE_SHIFT )
		{
			newModState |= SHIFT;
		}

		if( keyState & KEY_STATE_ALT )
		{
			newModState |= ALT;
		}


    for (const Rva005B6BA0MapView *map = (const Rva005B6BA0MapView *)TheMetaMap->getFirstMetaMapRec(); map; map = map->m_next)
		{
			DEBUG_ASSERTCRASH(map->m_meta > GameMessage::MSG_BEGIN_META_MESSAGES && 
				map->m_meta < GameMessage::MSG_END_META_MESSAGES, ("hmm, expected only meta-msgs here"));
			
			//
			// if this command is *only* usable in the game, we will ignore it if the game client
			// has not yet incremented to frame 1 (keeps us from doing in-game commands during
			// a map load, which throws the input system into wack because there isn't a
			// client frame for the input event, and in the case of a command that pauses the
			// game, like the quit menu, the client frame will never get beyond 0 and we
			// lose the ability to process any input
			//
			if( map->m_usableIn == COMMANDUSABLE_GAME && TheGameClient->getFrame() < 1 )
				continue;

			// if the shell is active, and this command is not usable in shell, continue
			if (TheShell && TheShell->isShellActive() && !(map->m_usableIn & COMMANDUSABLE_SHELL) )
				continue;

			// if the shell is not active and this command is not usable in the game, continue			
			if (TheShell && !TheShell->isShellActive() && !(map->m_usableIn & COMMANDUSABLE_GAME) )
				continue;





			// check for the special case of mods-only-changed.
			if (
						map->m_key == MK_NONE && 
						newModState != m_lastModState &&
						(
							(map->m_transition == UP && map->m_modState == m_lastModState) ||
							(map->m_transition == DOWN && map->m_modState == newModState)
						)
					)
			{
				//DEBUG_LOG(("Frame %d: MetaEventTranslator::translateGameMessage() Mods-only change: %s\n", TheGameLogic->getFrame(), findGameMessageNameByType(map->m_meta)));
				/*GameMessage *metaMsg =*/ ((Rva005B6BA0StreamView *)TheMessageStream)->appendMessage(map->m_meta);
				disp = DESTROY_MESSAGE;
				break;
			}

			// ok, now check for "normal" key transitions.
			if (
						map->m_key == key && 
						map->m_modState == newModState &&
						(
							(map->m_transition == UP && (keyState & KEY_STATE_UP)) ||
							(map->m_transition == DOWN && (keyState & KEY_STATE_DOWN)) //||
							//(map->m_transition == DOUBLEDOWN && (keyState & KEY_STATE_DOWN) && m_lastKeyDown == key)
						)
					)			
			{

				if( keyState & KEY_STATE_AUTOREPEAT )
				{
					// if it's an autorepeat of a "known" key, don't generate the meta-event, 
					// but DO eat the keystroke so no one else can mess with it
					//DEBUG_LOG(("Frame %d: MetaEventTranslator::translateGameMessage() auto-repeat: %s\n", TheGameLogic->getFrame(), findGameMessageNameByType(map->m_meta)));
				}
				else
				{

/*GameMessage *metaMsg =*/ ((Rva005B6BA0StreamView *)TheMessageStream)->appendMessage(map->m_meta);
					//DEBUG_LOG(("Frame %d: MetaEventTranslator::translateGameMessage() normal: %s\n", TheGameLogic->getFrame(), findGameMessageNameByType(map->m_meta)));
				}
				if (*((const bool *)g_rva012F7048LivingWorld + 8)) break;
				disp = DESTROY_MESSAGE;
				break;
			}
		} 



		if (t == Rva005B6BA0MessageTypes::RawKeyDown)
    {
			m_lastKeyDown = key;


#ifdef DUMP_ALL_KEYS_TO_LOG

		          WideChar Wkey = TheKeyboard->getPrintableKey(key, 0);
		          UnicodeString uKey;
		          uKey.set(&Wkey);
		          AsciiString aKey;
		          aKey.translate(uKey);
  	          DEBUG_LOG(("^%s ", aKey.str()));
#endif

    }



    m_lastModState = newModState;
	}


	if (t > GameMessage::MSG_RAW_MOUSE_BEGIN && t < Rva005B6BA0MessageTypes::RawMouseEnd )
	{
		Int index = 0;
		switch (t)
		{
			case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_DOWN:
			case Rva005B6BA0MessageTypes::MiddleDown:
			case Rva005B6BA0MessageTypes::RightDown:
			{
				// Fill out which the current mouse down position
				if (t == Rva005B6BA0MessageTypes::MiddleDown)
					index = 1;
				else if (t == Rva005B6BA0MessageTypes::RightDown)
					index = 2;
				// else index == 0
				m_mouseDownPosition[index] = msg->getArgument(0)->pixel;
				m_nextUpShouldCreateDoubleClick[index] = FALSE;
				
				break;
			}

			case GameMessage::MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK:
			case Rva005B6BA0MessageTypes::MiddleDoubleClick:
			case Rva005B6BA0MessageTypes::RightDoubleClick:
			{
				if (t == Rva005B6BA0MessageTypes::MiddleDoubleClick)
					index = 1;
				else if (t == Rva005B6BA0MessageTypes::RightDoubleClick)
					index = 2;
				// else index == 0

				m_nextUpShouldCreateDoubleClick[index] = TRUE;
				break;
			}

			case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP:
			case Rva005B6BA0MessageTypes::MiddleUp:
			case Rva005B6BA0MessageTypes::RightUp:
			{
				ICoord2D location = msg->getArgument(0)->pixel;

				// Fill out which the current mouse down position
				if (t == Rva005B6BA0MessageTypes::MiddleUp)
					index = 1;
				else if (t == Rva005B6BA0MessageTypes::RightUp)
					index = 2;
				// else index == 0

				GameMessage *newMessage = NULL;
				if (t == GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP) 
				{
					if (m_nextUpShouldCreateDoubleClick[index])
						newMessage = ((Rva005B6BA0StreamView *)TheMessageStream)->insertMessage(Rva005B6BA0MessageTypes::LeftDoubleClick, const_cast<GameMessage*>(msg));
					else
						newMessage = ((Rva005B6BA0StreamView *)TheMessageStream)->insertMessage(Rva005B6BA0MessageTypes::LeftClick, const_cast<GameMessage*>(msg));
					m_nextUpShouldCreateDoubleClick[index] = FALSE;
				} 
				else if (t == Rva005B6BA0MessageTypes::MiddleUp)
				{
					if (m_nextUpShouldCreateDoubleClick[index])
						newMessage = ((Rva005B6BA0StreamView *)TheMessageStream)->insertMessage(Rva005B6BA0MessageTypes::MiddleClickDouble, const_cast<GameMessage*>(msg));
					else
						newMessage = ((Rva005B6BA0StreamView *)TheMessageStream)->insertMessage(Rva005B6BA0MessageTypes::MiddleClick, const_cast<GameMessage*>(msg));
					m_nextUpShouldCreateDoubleClick[index] = FALSE;
				}
				else if (t == Rva005B6BA0MessageTypes::RightUp) 
				{
					if (m_nextUpShouldCreateDoubleClick[index])
						newMessage = ((Rva005B6BA0StreamView *)TheMessageStream)->insertMessage(Rva005B6BA0MessageTypes::RightClickDouble, const_cast<GameMessage*>(msg));
					else
						newMessage = ((Rva005B6BA0StreamView *)TheMessageStream)->insertMessage(Rva005B6BA0MessageTypes::RightClick, const_cast<GameMessage*>(msg));
					m_nextUpShouldCreateDoubleClick[index] = FALSE;
				}

				IRegion2D pixelRegion;
				buildRegion( &m_mouseDownPosition[index], &location, &pixelRegion );
				if (abs(pixelRegion.hi.x - pixelRegion.lo.x) < (*(const UnsignedInt *)((const char *)TheMouse + 0x10EC)) &&
						abs(pixelRegion.hi.y - pixelRegion.lo.y) < (*(const UnsignedInt *)((const char *)TheMouse + 0x10EC)))
				{
					pixelRegion.hi.x = pixelRegion.lo.x;
					pixelRegion.hi.y = pixelRegion.lo.y;
				}

				newMessage->appendPixelRegionArgument( pixelRegion );
				
				// append the modifier keys to the message.
				newMessage->appendIntegerArgument( msg->getArgument(1)->integer );
				break;
			}
		
		}

	}

	return disp;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ??0MetaMap@@QAE@XZ present-unmatched
MetaMap::MetaMap() : 
	m_metaMaps(NULL)
{
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
GameMessage::Type MetaMap::findGameMessageMetaType(const char* name)
{
	for (const LookupListRec* metaNames = GameMessageMetaTypeNames; metaNames->name; metaNames++)
		if (_strcmpi(metaNames->name, name) == 0)
			return (GameMessage::Type)metaNames->value;

	DEBUG_CRASH(("MetaTypeName %s not found -- did you remember to add it to GameMessageMetaTypeNames[] ?", name));
	return GameMessage::MSG_INVALID;
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/MessageStream/MetaMap_getMetaMapRecThunk.cpp
// ?getMetaMapRec@MetaMap@@IAEPAVMetaMapRec@@W4Type@GameMessage@@@Z present-unmatched
MetaMapRec *MetaMap::getMetaMapRec(GameMessage::Type t)
{
	for (MetaMapRec *map = m_metaMaps; map; map = map->m_next)
	{
		if (map->m_meta == t)
			return map;
	}

	// not found.. create a new one.
	MetaMapRec *m = newInstance(MetaMapRec);
	m->m_meta = t;
	m->m_key = MK_NONE;
	m->m_transition = DOWN;
	m->m_modState = NONE;
	m->m_usableIn = COMMANDUSABLE_NONE;
	m->m_category = CATEGORY_MISC;
	m->m_description.clear();
	m->m_displayName.clear();
	m->m_next = m_metaMaps;
	m_metaMaps = m;
	
	return m;
}

//-------------------------------------------------------------------------------------------------
/*static */ void MetaMap::parseMetaMap(INI* ini)
{
	// read and ignore the meta-map name
	const char *c = ini->getNextToken();

	GameMessage::Type t = TheMetaMap->findGameMessageMetaType(c);
	if (t == GameMessage::MSG_INVALID)
		throw INI_INVALID_DATA;

	MetaMapRec *map = TheMetaMap->getMetaMapRec(t);
	if (map == NULL)
		throw INI_INVALID_DATA;

	ini->initFromINI(map, TheMetaMapFieldParseTable);
}

//-------------------------------------------------------------------------------------------------
/*static*/ void INI::parseMetaMapDefinition( INI* ini )
{
	MetaMap::parseMetaMap(ini);
}
