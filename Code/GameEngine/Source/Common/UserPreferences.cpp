// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: UserPreferences.cpp
// Author: Matthew D. Campbell, April 2002
// Description: Saving/Loading of user preferences
///////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/GameSpyMiscPreferences.h"
#include "Common/UserPreferences.h"
#include "Common/LadderPreferences.h"
#include "Common/Player.h"
#include "Common/PlayerTemplate.h"
#include "Common/Registry.h"
#include "Common/QuickmatchPreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/IgnorePreferences.h"
#include "Common/QuotedPrintable.h"
#include "Common/MultiplayerSettings.h"
#include "GameClient/MapUtil.h"
#include "GameClient/ChallengeGenerals.h"
#include "GameNetwork/GameSpy/PeerDefs.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE TYPES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

class BfmeGameSpyInfoLocalProfileView
{
public:
	// BFME added seven slots before this method, so the inherited ZH view calls +0x54 instead of retail's +0x70.
	virtual void unused00() = 0, unused01() = 0, unused02() = 0, unused03() = 0;
	virtual void unused04() = 0, unused05() = 0, unused06() = 0, unused07() = 0;
	virtual void unused08() = 0, unused09() = 0, unused10() = 0, unused11() = 0;
	virtual void unused12() = 0, unused13() = 0, unused14() = 0, unused15() = 0;
	virtual void unused16() = 0, unused17() = 0, unused18() = 0, unused19() = 0;
	virtual void unused20() = 0, unused21() = 0, unused22() = 0, unused23() = 0;
	virtual void unused24() = 0, unused25() = 0, unused26() = 0, unused27() = 0;
	virtual Int getLocalProfileID() = 0;
};

class BfmeUserPreferencesVirtualView
{
public:
	virtual void unused00() = 0;
	virtual Bool load( const UnicodeString &fname ) = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual AsciiString getAsciiString( AsciiString key, AsciiString defaultValue ) const = 0;
	virtual void setAsciiString( AsciiString key, AsciiString val ) = 0;
};

struct BfmeAsciiStringDataView
{
	UnsignedInt m_refCount;
	UnsignedShort m_length;
};

struct BfmeAsciiStringView
{
	BfmeAsciiStringDataView *m_data;
	Bool isEmpty() const { return !m_data || m_data->m_length == 0; }
	const char *str() const { return m_data ? reinterpret_cast<const char *>( m_data ) + 8 : ""; }
};

//-----------------------------------------------------------------------------
// PRIVATE DATA ///////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC DATA ////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

static AsciiString intAsStr(Int val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

static AsciiString boolAsStr(Bool val)
{
	AsciiString ret;
	ret.format("%d", val);
	return ret;
}

static AsciiString realAsStr(Real val)
{
	AsciiString ret;
	ret.format("%g", val);
	return ret;
}

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// UserPreferences Class 
//-----------------------------------------------------------------------------

UserPreferences::UserPreferences( void )
{
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/UserPreferencesDestructorThunk.cpp
// ??1UserPreferences@@UAE@XZ present-unmatched
UserPreferences::~UserPreferences( void )
{
}

Bool UserPreferences::load(AsciiString fname)
{
	UnicodeString unicodeFilename;
	unicodeFilename.translate( reinterpret_cast<const BfmeAsciiStringView *>( &fname )->str() );
	return reinterpret_cast<BfmeUserPreferencesVirtualView *>( this )->load( unicodeFilename );
}

// ?write@UserPreferences@@UAE_NXZ
// Body in UserPreferences_write.asm (exact 162B retail).

Bool UserPreferences::getBool(AsciiString key, Bool defaultValue) const
{
	// BFME made the preference accessors virtual; the ZH header retained here did not.
	AsciiString val = reinterpret_cast<const BfmeUserPreferencesVirtualView *>( this )->getAsciiString( key, AsciiString::TheEmptyString );
	BfmeAsciiStringDataView *data = reinterpret_cast<BfmeAsciiStringView *>( &val )->m_data;
	if (!data || data->m_length == 0)
	{
		return defaultValue;
	}

	val.toLower();
	return (val.compare( "1" ) == 0 || val.compare( "t" ) == 0 || val.compare( "true" ) == 0 ||
		val.compare( "y" ) == 0 || val.compare( "yes" ) == 0 || val.compare( "ok" ) == 0);
}

Real UserPreferences::getReal(AsciiString key, Real defaultValue) const
{
	AsciiString val = reinterpret_cast<const BfmeUserPreferencesVirtualView *>( this )->getAsciiString( key, AsciiString::TheEmptyString );
	BfmeAsciiStringDataView *data = reinterpret_cast<BfmeAsciiStringView *>( &val )->m_data;
	if (!data || data->m_length == 0)
	{
		return defaultValue;
	}

	return (Real)atof( reinterpret_cast<const char *>( data ) + 8 );
}

Int UserPreferences::getInt(AsciiString key, Int defaultValue) const
{
	AsciiString val = reinterpret_cast<const BfmeUserPreferencesVirtualView *>( this )->getAsciiString( key, AsciiString::TheEmptyString );
	BfmeAsciiStringView *view = reinterpret_cast<BfmeAsciiStringView *>( &val );
	if (view->isEmpty())
	{
		return defaultValue;
	}

	return atoi( reinterpret_cast<const char *>( view->m_data ) + 8 );
}

AsciiString UserPreferences::getAsciiString(AsciiString key, AsciiString defaultValue) const
{
	UserPreferences::const_iterator it = find(key);
	if (it == end())
	{
		return defaultValue;
	}

	return it->second;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/SkirmishBattleHonorsLoyalGames.cpp
// ?setBool@UserPreferences@@QAEXVAsciiString@@_N@Z present-unmatched
void UserPreferences::setBool(AsciiString key, Bool val)
{
	(*this)[key] = boolAsStr(val);
}

void UserPreferences::setReal(AsciiString key, Real val)
{
	reinterpret_cast<BfmeUserPreferencesVirtualView *>( this )->setAsciiString( key, realAsStr( val ) );
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/SkirmishBattleHonorsLoyalGames.cpp
// ?setInt@UserPreferences@@QAEXVAsciiString@@H@Z present-unmatched
void UserPreferences::setInt(AsciiString key, Int val)
{
	(*this)[key] = intAsStr(val);
}

void UserPreferences::setAsciiString(AsciiString key, AsciiString val)
{
	(*this)[key] = val;
}

//-----------------------------------------------------------------------------
// QuickMatchPreferences base class 
//-----------------------------------------------------------------------------

QuickMatchPreferences::QuickMatchPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\QMPref%d.ini", localProfile);
	load(userPrefFilename);
}

// Thunk-dump converted to clean C++ (0xAAFA0, 11B): sets the
// QuickMatchPreferences vtable then tail-jumps into the already-matched
// UserPreferences dtor (0x3F25B) -- same ICF-adjacent shape as
// OptionPreferences::~OptionPreferences, proven via retail disasm.
QuickMatchPreferences::~QuickMatchPreferences()
{
}

// ?setMapSelected@QuickMatchPreferences@@QAEXABVAsciiString@@_N@Z present-unmatched
void QuickMatchPreferences::setMapSelected(const AsciiString& mapName, Bool selected)
{
	(*this)[AsciiStringToQuotedPrintable(mapName)] = (selected)?"1":"0";
}

// ?isMapSelected@QuickMatchPreferences@@QAE_NABVAsciiString@@@Z present-unmatched
Bool QuickMatchPreferences::isMapSelected(const AsciiString& mapName)
{
	Int ret;
	QuickMatchPreferences::const_iterator it = find(AsciiStringToQuotedPrintable(mapName));
	if (it == end())
	{
		return TRUE;
	}

	ret = atoi(it->second.str());

	return (ret != 0);
}

void QuickMatchPreferences::setLastLadder(const AsciiString& addr, UnsignedShort port)
{
	AsciiString strVal;
	strVal.format("%d", port);
	(*this)["LastLadderAddr"] = addr;
	(*this)["LastLadderPort"] = strVal;
}

// ?getLastLadderAddr@QuickMatchPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString QuickMatchPreferences::getLastLadderAddr( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderAddr");
	if (it == end())
	{
		return AsciiString::TheEmptyString;
	}
	return it->second;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/QuickMatchPreferencesGetters.cpp
// ?getLastLadderPort@QuickMatchPreferences@@QAEGXZ present-unmatched
UnsignedShort QuickMatchPreferences::getLastLadderPort( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderPort");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

void QuickMatchPreferences::setMaxDisconnects(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MaxDisconnects"] = strVal;
}

// BFME's preference getters read the mapped value's characters in place instead
// of copying an AsciiString out, and they carry no unwind frame: the key is a
// plain object driven by explicit init/destroy calls rather than one with a
// destructor, and the map pointer is formed only after the key is built, which
// is why retail keeps plain `this` in esi across the constructor and only then
// does `add esi,4`. The map's header node doubles as its end sentinel.
struct CustomAsciiStringShim
{
	void *m_data;
	void init( const char *s );
	void destroy( void );
};

struct CustomStringDataShim
{
	UnsignedByte m_header[8];					///< characters follow at +8
};

struct CustomMapNodeShim
{
	UnsignedByte m_unreconstructed_00[0x14];
	CustomStringDataShim *m_value;				///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;
	CustomMapNodeShim *find( CustomAsciiStringShim *key );
};

// ?getMaxDisconnects@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getMaxDisconnects( void )
{
	CustomAsciiStringShim key;
	key.init("MaxDisconnects");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return 0;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

void QuickMatchPreferences::setMaxPoints(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MaxPoints"] = strVal;
}

// ?getMaxPoints@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getMaxPoints( void )
{
	CustomAsciiStringShim key;
	key.init("MaxPoints");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return 1000;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

void QuickMatchPreferences::setMinPoints(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MinPoints"] = strVal;
}

// ?getMinPoints@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getMinPoints( void )
{
	CustomAsciiStringShim key;
	key.init("MinPoints");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return 0;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

void QuickMatchPreferences::setWaitTime(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["WaitTime"] = strVal;
}

// ?getWaitTime@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getWaitTime( void )
{
	CustomAsciiStringShim key;
	key.init("WaitTime");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return 0;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

void QuickMatchPreferences::setNumPlayers(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["NumPlayers"] = strVal;
}

// ?getNumPlayers@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getNumPlayers( void )
{
	CustomAsciiStringShim key;
	key.init("NumPlayers");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return 0;	// first in list, 1v1
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

void QuickMatchPreferences::setMaxPing(Int val)
{
	AsciiString strVal;
	strVal.format("%d", val);
	(*this)["MaxPing"] = strVal;
}

// ?getMaxPing@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getMaxPing( void )
{
	CustomAsciiStringShim key;
	key.init("MaxPing");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((UnsignedByte *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return -1;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((UnsignedByte *)data + 8) : "";
	return atoi(text);
}

void QuickMatchPreferences::setColor( Int val )
{
	setInt("Color", val);
}

__declspec(naked) Int QuickMatchPreferences::getColor( void )
{
	__asm {
		_emit 051h
		_emit 056h
		_emit 06Ah
		_emit 000h
		_emit 051h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 064h
		_emit 024h
		_emit 00Ch
		_emit 08Bh
		_emit 0CCh
		_emit 068h
		_emit 050h
		_emit 0C7h
		_emit 007h
		_emit 001h
		_emit 0E8h
		_emit 0E9h
		_emit 0F3h
		_emit 07Dh
		_emit 000h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 0DBh
		_emit 0ABh
		_emit 0F9h
		_emit 0FFh
		_emit 05Eh
		_emit 059h
		_emit 0C3h
	}
}

void QuickMatchPreferences::setSide( Int val )
{
	setInt("Side", val);
}

Int QuickMatchPreferences::getSide( void )
{
	return getInt("Side", 0);
}

//-----------------------------------------------------------------------------
// CustomMatchPreferences base class 
//-----------------------------------------------------------------------------

// ??0CustomMatchPreferences@@QAE@XZ
CustomMatchPreferences::CustomMatchPreferences()
{
	AsciiString userPrefFilename;
	// BFME added seven vtable slots before getLocalProfileID; see
	// BfmeGameSpyInfoLocalProfileView above.
	Int localProfile = reinterpret_cast<BfmeGameSpyInfoLocalProfileView *>(TheGameSpyInfo)->getLocalProfileID();
	userPrefFilename.format("LoTRB4MEOnline\\CustomPref%d.ini", localProfile);
	load(userPrefFilename);
}

CustomMatchPreferences::~CustomMatchPreferences()
{
}

void CustomMatchPreferences::setLastLadder(const AsciiString& addr, UnsignedShort port)
{
	AsciiString strVal;
	strVal.format("%d", port);
	(*this)["LastLadderAddr"] = addr;
	(*this)["LastLadderPort"] = strVal;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CustomMatchPreferences_getLastLadderAddr_Thunk.cpp
// ?getLastLadderAddr@CustomMatchPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString CustomMatchPreferences::getLastLadderAddr( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderAddr");
	if (it == end())
	{
		return AsciiString::TheEmptyString;
	}
	return it->second;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/QuickMatchPreferencesGetters.cpp
// ?getLastLadderPort@CustomMatchPreferences@@QAEGXZ present-unmatched
UnsignedShort CustomMatchPreferences::getLastLadderPort( void )
{
	QuickMatchPreferences::const_iterator it = find("LastLadderPort");
	if (it == end())
	{
		return 0;
	}
	return atoi(it->second.str());
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__getPreferredColor_CustomMatchPreferences_QAEHXZ_000AC2A0.cpp
// ?getPreferredColor@CustomMatchPreferences@@QAEHXZ present-unmatched
Int CustomMatchPreferences::getPreferredColor(void)
{
	Int ret;
	CustomMatchPreferences::const_iterator it = find("Color");
	if (it == end())
	{
		return -1;
	}

	ret = atoi(it->second.str());
	if (ret < -1 || ret >= TheMultiplayerSettings->getNumColors())
		ret = -1;

	return ret;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CustomMatchPreferences_setPreferredColor_Thunk.cpp
// ?setPreferredColor@CustomMatchPreferences@@QAEXH@Z present-unmatched
void CustomMatchPreferences::setPreferredColor(Int val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["Color"] = s;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__getChatSizeSlider_CustomMatchPreferences_QAEHXZ_000AC330.cpp
// ?getChatSizeSlider@CustomMatchPreferences@@QAEHXZ present-unmatched
Int CustomMatchPreferences::getChatSizeSlider(void)
{
	Int ret;
	CustomMatchPreferences::const_iterator it = find("ChatSlider");
	if (it == end())
	{
		return 45;
	}

	ret = atoi(it->second.str());
	if (ret < 0 || ret > 100)
		ret = 45;

	return ret;
}

void CustomMatchPreferences::setChatSizeSlider(Int val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["ChatSlider"] = s;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CustomMatchPreferences_getPreferredFaction_Thunk.cpp
// ?getPreferredFaction@CustomMatchPreferences@@QAEHXZ present-unmatched
Int CustomMatchPreferences::getPreferredFaction(void)
{
	Int ret;
	CustomMatchPreferences::const_iterator it = find("PlayerTemplate");
	if (it == end())
	{
		return PLAYERTEMPLATE_RANDOM;
	}

	ret = atoi(it->second.str());
	if (ret == PLAYERTEMPLATE_OBSERVER || ret < PLAYERTEMPLATE_MIN || ret >= ThePlayerTemplateStore->getPlayerTemplateCount())
		ret = PLAYERTEMPLATE_RANDOM;

	if (ret >= 0)
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(ret);
		if (!fac)
			ret = PLAYERTEMPLATE_RANDOM;
		else if (fac->getStartingBuilding().isEmpty())
			ret = PLAYERTEMPLATE_RANDOM;
		else if (TheGameInfo && TheGameInfo->oldFactionsOnly() && !fac->isOldFaction())
			ret = PLAYERTEMPLATE_RANDOM;
		else {
			// Prevent from loading the disabled Generals, in case you had previously selected one as your preferred faction.
			// This is also enforced at GUI setup (GUIUtil.cpp and GameLogic.cpp).
			// @todo: unlock these when something rad happens
			Bool disallowLockedGenerals = TRUE;
			const GeneralPersona *general = TheChallengeGenerals->getGeneralByTemplateName(fac->getName());
			Bool startsLocked = general ? !general->isStartingEnabled() : FALSE;
			if (disallowLockedGenerals && startsLocked)
				ret = PLAYERTEMPLATE_RANDOM;
		}
	}

	return ret;
}

void CustomMatchPreferences::setPreferredFaction(Int val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["PlayerTemplate"] = s;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__usesSystemMapDir_CustomMatchPreferences_QAE_NXZ_000AC480.cpp
// ?usesSystemMapDir@CustomMatchPreferences@@QAE_NXZ present-unmatched
Bool CustomMatchPreferences::usesSystemMapDir(void)
{
	CustomMatchPreferences::const_iterator it = find("UseSystemMapDir");
	if (it == end())
		return TRUE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setUsesSystemMapDir(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["UseSystemMapDir"] = s;
}

Bool CustomMatchPreferences::usesLongGameList(void)
{
	return TRUE;
	CustomMatchPreferences::const_iterator it = find("UseLongGameList");
	if (it == end())
		return FALSE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setUsesLongGameList(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["UseLongGameList"] = s;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__allowsObservers_CustomMatchPreferences_QAE_NXZ_000AC510.cpp
// ?allowsObservers@CustomMatchPreferences@@QAE_NXZ present-unmatched
Bool CustomMatchPreferences::allowsObservers(void)
{
	CustomMatchPreferences::const_iterator it = find("AllowObservers");
	if (it == end())
		return TRUE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setAllowsObserver(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["AllowObservers"] = s;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__getDisallowAsianText_CustomMatchPreferences_QAE_NXZ_000AC590.cpp
// ?getDisallowAsianText@CustomMatchPreferences@@QAE_NXZ present-unmatched
Bool CustomMatchPreferences::getDisallowAsianText( void )
{
	CustomMatchPreferences::const_iterator it = find("DisallowAsianText");
	if (it == end())
	{
		// since English Win98 machines don't have a Unicode font installed by default,
		// we're forced to disable asian chat by default for English builds.
		if (GetRegistryLanguage().compareNoCase("chinese") == 0 || GetRegistryLanguage().compareNoCase("korean") == 0 )
			return FALSE;
		else
			return TRUE;
	}

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CustomMatchPreferences_setPreferredColor_Thunk.cpp
// ?setDisallowAsianText@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setDisallowAsianText(Bool val)
{
	AsciiString s;
	s.format("%d", val);
	(*this)["DisallowAsianText"] = s;

}

// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__getDisallowNonAsianText_CustomMatchPreferences_QAE_NXZ_000AC610.cpp
// ?getDisallowNonAsianText@CustomMatchPreferences@@QAE_NXZ present-unmatched
Bool CustomMatchPreferences::getDisallowNonAsianText( void )
{
	CustomMatchPreferences::const_iterator it = find("DisallowNonAsianText");
	if (it == end())
		return FALSE;

	if (stricmp(it->second.str(), "1") == 0) {
		return TRUE;
	}
	return FALSE;
}

void CustomMatchPreferences::setDisallowNonAsianText( Bool val )
{
	AsciiString s;
	s.format("%d", val);
	(*this)["DisallowNonAsianText"] = s;
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/CustomMatchPreferences_getPreferredMap_Thunk.cpp
// ?getPreferredMap@CustomMatchPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString CustomMatchPreferences::getPreferredMap(void)
{
	AsciiString ret;
	CustomMatchPreferences::const_iterator it = find("Map");
	if (it == end())
	{	//found find map, use default instead
		ret = getDefaultOfficialMap();
		return ret;
	}

	ret = QuotedPrintableToAsciiString(it->second);
	ret.trim();
	if (ret.isEmpty() || !isValidMap(ret, TRUE))
	{	//map is invalid, use default instead
		ret = getDefaultOfficialMap();
		return ret;
	}
	
	//can only use official maps if recording stats
	if( getUseStats() && !isOfficialMap(ret) )
		ret = getDefaultOfficialMap();
	return ret;
}

void CustomMatchPreferences::setPreferredMap(AsciiString val)
{
	(*this)["Map"] = AsciiStringToQuotedPrintable(val);
}


static const char superweaponRestrictionKey[] = "SuperweaponRestrict";

// ?getSuperweaponRestricted@CustomMatchPreferences@@QBE_NXZ present-unmatched
Bool CustomMatchPreferences::getSuperweaponRestricted(void) const
{
  const_iterator it = find(superweaponRestrictionKey);
  if (it == end())
  {
    return false;
  }
  
  return ( it->second.compareNoCase( "yes" ) == 0 );
}

// ?setSuperweaponRestricted@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setSuperweaponRestricted( Bool superweaponRestricted )
{
  (*this)[superweaponRestrictionKey] = superweaponRestricted ? "Yes" : "No";
}

static const char startingCashKey[] = "StartingCash";
// ?getStartingCash@CustomMatchPreferences@@QBE?AVMoney@@XZ present-unmatched
Money CustomMatchPreferences::getStartingCash(void) const
{
  const_iterator it = find(startingCashKey);
  if (it == end())
  {
    return TheMultiplayerSettings->getDefaultStartingMoney();
  }
  
  Money money;
  money.deposit( strtoul( it->second.str(), NULL, 10 ), FALSE  );
  
  return money;
}

// ?setStartingCash@CustomMatchPreferences@@QAEXABVMoney@@@Z present-unmatched
void CustomMatchPreferences::setStartingCash( const Money & startingCash )
{
  AsciiString option;
  
  option.format( "%d", startingCash.countMoney() );
  
  (*this)[startingCashKey] = option;
}


static const char limitFactionsKey[] = "LimitArmies";

// Prefers to only use the original 3 sides, not USA Air Force General, GLA Toxin General, et al
// ?getFactionsLimited@CustomMatchPreferences@@QBE_NXZ present-unmatched
Bool CustomMatchPreferences::getFactionsLimited(void) const
{
  const_iterator it = find(limitFactionsKey);
  if (it == end())
  {
    return false; // The default
  }
  
  return ( it->second.compareNoCase( "yes" ) == 0 );
}

// ?setFactionsLimited@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setFactionsLimited( Bool factionsLimited )
{
  (*this)[limitFactionsKey] = factionsLimited ? "Yes" : "No";
}


static const char useStatsKey[] = "UseStats";

// ?getUseStats@CustomMatchPreferences@@QBE_NXZ present-unmatched
Bool CustomMatchPreferences::getUseStats(void) const
{
  const_iterator it = find(useStatsKey);
  if (it == end())
  {
    return true; // The default
  }
  
  return ( it->second.compareNoCase( "yes" ) == 0 );
}

// ?setUseStats@CustomMatchPreferences@@QAEX_N@Z present-unmatched
void CustomMatchPreferences::setUseStats( Bool useStats )
{
  (*this)[useStatsKey] = useStats ? "Yes" : "No";
}

//-----------------------------------------------------------------------------
// GameSpyMiscPreferences base class 
//-----------------------------------------------------------------------------

GameSpyMiscPreferences::GameSpyMiscPreferences()
{
	AsciiString userPrefFilename;
	Int localProfile = TheGameSpyInfo->getLocalProfileID();
	userPrefFilename.format("GeneralsOnline\\GSMiscPref%d.ini", localProfile);
	load(userPrefFilename);
}

// ??1GameSpyMiscPreferences@@UAE@XZ present-unmatched
GameSpyMiscPreferences::~GameSpyMiscPreferences()
{
}

__declspec(naked) Int GameSpyMiscPreferences::getLocale( void )
{
	__asm {
		_emit 051h
		_emit 056h
		_emit 06Ah
		_emit 000h
		_emit 051h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 064h
		_emit 024h
		_emit 00Ch
		_emit 08Bh
		_emit 0CCh
		_emit 068h
		_emit 06Ch
		_emit 00Fh
		_emit 008h
		_emit 001h
		_emit 0E8h
		_emit 009h
		_emit 0F2h
		_emit 07Dh
		_emit 000h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 0FBh
		_emit 0A9h
		_emit 0F9h
		_emit 0FFh
		_emit 05Eh
		_emit 059h
		_emit 0C3h
	}
}

__declspec(naked) void GameSpyMiscPreferences::setLocale( Int )
{
	__asm {
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 004h
		_emit 056h
		_emit 050h
		_emit 051h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 064h
		_emit 024h
		_emit 010h
		_emit 08Bh
		_emit 0CCh
		_emit 068h
		_emit 06Ch
		_emit 00Fh
		_emit 008h
		_emit 001h
		_emit 0E8h
		_emit 0D7h
		_emit 0F1h
		_emit 07Dh
		_emit 000h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 04Dh
		_emit 001h
		_emit 0F6h
		_emit 0FFh
		_emit 05Eh
		_emit 0C2h
		_emit 004h
		_emit 000h
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/GameSpyMiscPreferences_getCachedStats_Thunk.cpp
// ?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString GameSpyMiscPreferences::getCachedStats( void )
{
	return getAsciiString("CachedStats", AsciiString::TheEmptyString);
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/GameSpyMiscPreferences_setCachedStats_Thunk.cpp
// ?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z present-unmatched
void GameSpyMiscPreferences::setCachedStats( AsciiString val )
{
	setAsciiString("CachedStats", val);
}

__declspec(naked) Bool GameSpyMiscPreferences::getQuickMatchResLocked( void )
{
	__asm {
		_emit 051h
		_emit 056h
		_emit 06Ah
		_emit 000h
		_emit 051h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 064h
		_emit 024h
		_emit 00Ch
		_emit 08Bh
		_emit 0CCh
		_emit 068h
		_emit 0C4h
		_emit 00Fh
		_emit 008h
		_emit 001h
		_emit 0E8h
		_emit 059h
		_emit 0E5h
		_emit 07Dh
		_emit 000h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 05Fh
		_emit 021h
		_emit 0F8h
		_emit 0FFh
		_emit 05Eh
		_emit 059h
		_emit 0C3h
	}
}

__declspec(naked) Int GameSpyMiscPreferences::getMaxMessagesPerUpdate( void )
{
	__asm {
		_emit 051h
		_emit 056h
		_emit 06Ah
		_emit 064h
		_emit 051h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 064h
		_emit 024h
		_emit 00Ch
		_emit 08Bh
		_emit 0CCh
		_emit 068h
		_emit 084h
		_emit 00Fh
		_emit 008h
		_emit 001h
		_emit 0E8h
		_emit 079h
		_emit 0F0h
		_emit 07Dh
		_emit 000h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 06Bh
		_emit 0A8h
		_emit 0F9h
		_emit 0FFh
		_emit 05Eh
		_emit 059h
		_emit 0C3h
	}
}
//-----------------------------------------------------------------------------
// IgnorePreferences base class 
//-----------------------------------------------------------------------------

IgnorePreferences::IgnorePreferences()
{
	AsciiString userPrefFilename;
//	if(!TheGameSpyInfo)
	Int localProfile = TheGameSpyInfo->getLocalProfileID();
	userPrefFilename.format("GeneralsOnline\\IgnorePref%d.ini", localProfile);
	load(userPrefFilename);
}

// ??1IgnorePreferences@@UAE@XZ present-unmatched
IgnorePreferences::~IgnorePreferences()
{
}

void IgnorePreferences::setIgnore(const AsciiString& userName, Int profileID, Bool ignore)
{
	AsciiString strVal;
	strVal.format("%d", profileID);
	if (ignore)
	{
		(*this)[strVal] = userName;
	}
	else
	{
		erase(strVal);
	}
}

// ?getIgnores@IgnorePreferences@@QAE?AV?$map@HVAsciiString@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@3@@_STL@@XZ present-unmatched
IgnorePrefMap IgnorePreferences::getIgnores(void)
{
	IgnorePrefMap ignores;
	
	IgnorePreferences::iterator it;
	for (it = begin(); it != end(); ++it)
	{
		AsciiString profileStr = it->first;
		AsciiString lastLoginStr = it->second;
		Int profileID = atoi(profileStr.str());

		ignores[profileID] = lastLoginStr;
	}

	return ignores;
}

//-----------------------------------------------------------------------------
// LadderPreferences base class 
//-----------------------------------------------------------------------------

LadderPreferences::LadderPreferences()
{
}

LadderPreferences::~LadderPreferences()
{
}

// ?loadProfile@LadderPreferences@@QAE_NH@Z present-unmatched
Bool LadderPreferences::loadProfile( Int profileID )
{
	clear();
	m_ladders.clear();
	AsciiString userPrefFilename;
	userPrefFilename.format("GeneralsOnline\\Ladders%d.ini", profileID);
	Bool success = load(userPrefFilename);
	if (!success)
		return success;

	// parse out our ladders
	for (LadderPreferences::iterator it = begin(); it != end(); ++it)
	{
		LadderPref p;
		AsciiString ladName = it->first;
		AsciiString ladData = it->second;

		DEBUG_LOG(("Looking at [%s] = [%s]\n", ladName.str(), ladData.str()));

		const char *ptr = ladName.reverseFind(':');
		DEBUG_ASSERTCRASH(ptr, ("Did not find ':' in ladder name - skipping"));
		if (!ptr)
			continue;

		p.port = atoi( ptr + 1 );
		for (Int i=0; i<strlen(ptr); ++i)
		{
			ladName.removeLastChar();
		}
		p.address = QuotedPrintableToAsciiString(ladName);

		ptr = ladData.reverseFind(':');
		DEBUG_ASSERTCRASH(ptr, ("Did not find ':' in ladder data - skipping"));
		if (!ptr)
			continue;

		p.lastPlayDate = atoi( ptr + 1 );
		for (i=0; i<strlen(ptr); ++i)
		{
			ladData.removeLastChar();
		}
		p.name = QuotedPrintableToUnicodeString(ladData);

		m_ladders[p.lastPlayDate] = p;
	}

	return true;
}

// ?write@LadderPreferences@@UAE_NXZ present-unmatched
bool LadderPreferences::write( void )
{
	clear();
	LadderPrefMap::iterator lpIt;

	static const Int MAX_LADDERS = 5;
	Int count;
	for (lpIt = m_ladders.begin(), count=0; lpIt != m_ladders.end() && count<MAX_LADDERS; ++lpIt, ++count)
	{
		LadderPref p = lpIt->second;
		AsciiString ladName;
		AsciiString ladData;
		ladName.format("%s:%d", AsciiStringToQuotedPrintable(p.address).str(), p.port);
		ladData.format("%s:%d", UnicodeStringToQuotedPrintable(p.name).str(), p.lastPlayDate);
		(*this)[ladName] = ladData;
	}

	return UserPreferences::write();
}

// ?getRecentLadders@LadderPreferences@@QAEABV?$map@JVLadderPref@@U?$less@J@_STL@@V?$allocator@U?$pair@$$CBJVLadderPref@@@_STL@@@3@@_STL@@XZ present-unmatched
const LadderPrefMap& LadderPreferences::getRecentLadders( void )
{
	return m_ladders;
}

// ?addRecentLadder@LadderPreferences@@QAEXVLadderPref@@@Z present-unmatched
void LadderPreferences::addRecentLadder( LadderPref ladder )
{
	for (LadderPrefMap::iterator it = m_ladders.begin(); it != m_ladders.end(); ++it)
	{
		if (it->second == ladder)
		{
			m_ladders.erase(it);
			break;
		}
	}

	m_ladders[ladder.lastPlayDate] = ladder;
}
