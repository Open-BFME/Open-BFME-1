// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// ?updateMapStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@_N@Z at retail RVA
// 0x004559A0, 838 B.  Self-contained minimal-shim TU in the style of
// game/GameEngine/Source/Common/INI/Rva000C1E50MapCacheDefinition.cpp.
//
// The body is the BFME 1.03 descendant of the Zero Hour twin at
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp:
//updateMapStartSpots, with the four BFME deltas read off
// `python3 tools/dis_retail.py 0x004559A0 838`:
//   - the "map not cached" loop also blanks every button with GUI:Blank;
//   - no NULL tests on buttonMapStartPositions[] (the Zero Hour patch's guard);
//   - the four SetText calls reach the ledger's GadgetRadioSetText body
//     (0x004BC6E0) rather than GadgetButtonSetText (0x004BD400);
//   - a start position past mmd.m_numPlayers is reset to -1.
// The extent is 838 bytes; the 830-byte ledger row stops inside the final
// add esp / ret.
//
// The string model is the StringInline shape (inputs/reference/shims/
// stringinline/StringInline.h): a by-value string argument is only built in
// place -- `mov [esp+N],esp` AHEAD of the ctor's `mov ecx,esp`, the order
// retail uses -- when the copy ctor and destructor are INLINE FORWARDERS to a
// StringBase<T> that owns the out-of-line bodies.  A string class that spells
// them itself transposes the EH saved-esp store against the ctor `this` at all
// five by-value temporaries in this body (docs/shape_levers.md row 2).

template <typename T> struct UpdateMapStartSpotsStringData
{
	unsigned short m_refCount;
	unsigned short m_reserved;
	unsigned short m_length;
	unsigned short m_pad;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );

	UpdateMapStartSpotsStringData<T> *m_data;
};

template <typename T> bool operator<( const StringBase<T> &left, const StringBase<T> &right );

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	AsciiString &operator=( const AsciiString &other )
	{
		( (StringBase<char> *)this )->set( *(const StringBase<char> *)&other );
		return *this;
	}
	void toLower();
	void __cdecl format( AsciiString format, ... );
	int compareNoCase( const AsciiString &other ) const;
	int getLength( void ) const { return m_data ? m_data->m_length : 0; }
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
	static AsciiString TheEmptyString;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const AsciiString &other );
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	UnicodeString &operator=( const UnicodeString &other )
	{
		( (StringBase<unsigned short> *)this )->set( *(const StringBase<unsigned short> *)&other );
		return *this;
	}
	void __cdecl format( UnicodeString format, ... );
	int compareNoCase( const UnicodeString &other ) const;
	int getLength( void ) const { return m_data ? m_data->m_length : 0; }
	const unsigned short *str( void ) const { return m_data ? m_data->m_text : 0; }
	static const UnicodeString TheEmptyString;
};

inline bool operator<( const AsciiString &left, const AsciiString &right )
{
	return *(const StringBase<char> *)&left < *(const StringBase<char> *)&right;
}

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.getLength() == right.getLength() && left.str() == right.str();
}

#define ASCIISTRING_H
#define UNICODESTRING_H

#include <map>
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/PlayerTemplate.h"
#include "GameClient/MapUtil.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindow.h"
#include "GameNetwork/GameInfo.h"

// Retail's by-value GadgetRadioSetText argument reaches the call as four bytes
// -- the string is a single pointer -- so the free function takes it by value
// like the reference header does.  targets/game/reverse/symbols.csv pins the
// ILT 0x000424F1 retail's callers go through; the resolver binds this call to
// the same body (0x004BC6E0).
void GadgetRadioSetText( GameWindow *g, UnicodeString text );

// BFME 1.03's map-cache record is 0xFC bytes with m_numPlayers at +0x20; the
// Zero Hour MapUtil.h copy this TU includes is four bytes shorter because it
// carries the extra m_nameLookupTag.  The record's copy ctor and destructor are
// retail bodies reached through the ledger's pins (0x0000EA75 / 0x0002756B),
// the same pair game/GameEngine/Source/GameNetwork/GameInfo_getMapIsOfficial_BFME.cpp
// drives; see that file for the layout evidence (the copy ctor at 0x000C1240
// copies the last member at +0xF8).  The copy ctor is pinned under this name;
// the destructor is the same inline forwarder that file uses, because an
// out-of-line ~BfmeMemberB_000C1490 would leave an unpinned reference the
// resolver cannot bind, while the forwarder encodes the pinned
// ??1Gen_uw_0002756b@@QAE@XZ body -- the 0x0002756B ILT retail reaches -- directly.
class Gen_uw_0002756b
{
public:
	~Gen_uw_0002756b( void );
};

class BfmeMemberB_000C1490
{
public:
	BfmeMemberB_000C1490( const BfmeMemberB_000C1490 &other );		// retail 0x0000EA75
	~BfmeMemberB_000C1490( void ) { ( (Gen_uw_0002756b *)this )->~Gen_uw_0002756b(); }

	unsigned char m_prefix[0x20];
	int m_numPlayers;												// +0x20
	unsigned char m_suffix[0xd8];
};

// ?updateMapStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@_N@Z
void updateMapStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], Bool onLoadScreen )
{
	AsciiString lowerMap = myGame->getMap();
	lowerMap.toLower();
	// Retail loads the global ONCE, into esi, before it materialises find()'s
	// argument; naming the cache is what lets MSVC 7.1 keep it there for the
	// end() compare too (same lever as GameInfo_getMapIsOfficial_BFME.cpp).
	MapCache *cache = TheMapCache;
	std::map<AsciiString, MapMetaData>::iterator it = cache->find( lowerMap );
	if ( it == cache->end() )
	{
		for ( Int i = 0; i < MAX_SLOTS; ++i )
		{
			buttonMapStartPositions[i]->winHide( TRUE );
			GadgetRadioSetText( buttonMapStartPositions[i], TheGameText->fetch( "GUI:Blank" ) );
		}
		return;
	}
	BfmeMemberB_000C1490 mmd = *reinterpret_cast<const BfmeMemberB_000C1490 *>( &it->second );

	for ( Int i = 0; i < MAX_SLOTS; ++i )
	{
		GadgetRadioSetText( buttonMapStartPositions[i], UnicodeString::TheEmptyString );
		if ( !onLoadScreen )
		{
			buttonMapStartPositions[i]->winSetTooltip( TheGameText->fetch( "TOOLTIP:StartPosition" ) );
		}
	}
	for ( i = 0; i < MAX_SLOTS; ++i )
	{
		GameSlot *gs = myGame->getSlot( i );
		if ( onLoadScreen )
		{
			if ( gs->getApparentStartPos() >= 0 && gs->getApparentStartPos() < mmd.m_numPlayers && gs->getPlayerTemplate() > PLAYERTEMPLATE_MIN )
			{
				AsciiString displayNumber;
				displayNumber.format( AsciiString( "NUMBER:%d" ), i + 1 );
				GadgetRadioSetText( buttonMapStartPositions[gs->getApparentStartPos()], TheGameText->fetch( displayNumber ) );
			}
		}
		else
		{
			if ( gs->getStartPos() >= 0 && gs->getStartPos() < mmd.m_numPlayers && gs->getPlayerTemplate() > PLAYERTEMPLATE_MIN )
			{
				AsciiString displayNumber;
				displayNumber.format( AsciiString( "NUMBER:%d" ), i + 1 );
				GadgetRadioSetText( buttonMapStartPositions[gs->getStartPos()], TheGameText->fetch( displayNumber ) );
				UnicodeString temp;
				temp.format( TheGameText->fetch( "TOOLTIP:StartPositionN" ), i + 1 );
				buttonMapStartPositions[gs->getStartPos()]->winSetTooltip( temp );
			}
			else if ( gs->getStartPos() >= mmd.m_numPlayers )
			{
				gs->setStartPos( -1 );
			}
		}
	}
}
