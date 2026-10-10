// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: PlayerTemplate.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: PlayerTemplate.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_VETERANCY_NAMES				// for TheVeterancyNames[]

#include "Common/GameCommon.h"
#include "Common/PlayerTemplate.h"
#include "Common/Player.h"
#include "Common/INI.h"
#include "Common/Science.h"
#include "GameClient/Image.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Retail's LightPointsUpSound / ObjectiveAddedSound / ObjectiveCompletedSound entries all
// call the sound-reference parser whose body is 0x000BABF0 (ledger ?rva000BABF0@INI@@,
// reached in retail's table through ILT thunk ?j_00018e7b). Its identity is unproven
// beyond the address, so the table references it through the ?b_000babf0@@YAXXZ pin.
void b_000babf0();

/*static*/ const FieldParse* PlayerTemplate::getFieldParse()
{
	// Retail's table at 0x010847E0 is the BFME1 field list, not the ZH list the
	// reference tree carries: it parses IntrinsicSciencesMP, the sound and
	// objective fields, InitialUpgrades, DefaultPlayerAIType, SpellBook(Mp),
	// MaxLevelMP/SP, Evil, BuildableHeroesMP and the spell-store labels, and it
	// has no BaseSide, OldFaction, ScoreScreenMusic, GeneralImage or medallion
	// entries. The offset column holds retail's raw byte offsets copied from
	// that table: the shim PlayerTemplate class keeps the ZH members plus
	// layout padding, so the BFME1 members these offsets address are not
	// modeled as class members yet, and offsetof would read the ZH layout.
	static const FieldParse TheFieldParseTable[] = 
	{
		{ "Side",					INI::parseAsciiString,					NULL, 0x8 },
		{ "PlayableSide",			INI::parseBool,						NULL, 0xBD },
		{ "DisplayName",			INI::parseAndTranslateLabel,		NULL, 0x4 },
		{ "StartMoney",				PlayerTemplate::parseStartMoney,		NULL, 0x1C },
		{ "PreferredColor",			INI::parseRGBColor,					NULL, 0x28 },
		{ "StartingBuilding",		INI::parseAsciiString,				NULL, 0x34 },
		{ "StartingUnit0",			INI::parseAsciiString,				NULL, 0x38 },
		{ "StartingUnit1",			INI::parseAsciiString,				NULL, 0x3C },
		{ "StartingUnit2",			INI::parseAsciiString,				NULL, 0x40 },
		{ "StartingUnit3",			INI::parseAsciiString,				NULL, 0x44 },
		{ "StartingUnit4",			INI::parseAsciiString,				NULL, 0x48 },
		{ "StartingUnit5",			INI::parseAsciiString,				NULL, 0x4C },
		{ "StartingUnit6",			INI::parseAsciiString,				NULL, 0x50 },
		{ "StartingUnit7",			INI::parseAsciiString,				NULL, 0x54 },
		{ "StartingUnit8",			INI::parseAsciiString,				NULL, 0x58 },
		{ "StartingUnit9",			INI::parseAsciiString,				NULL, 0x5C },
		{ "ProductionCostChange",		PlayerTemplate::parseProductionCostChange,		NULL, 0 },
		{ "ProductionTimeChange",		PlayerTemplate::parseProductionTimeChange,		NULL, 0 },
		{ "ProductionVeterancyLevel",	PlayerTemplate::parseProductionVeterancyLevel,	NULL, 0 },
		{ "IntrinsicSciences",		INI::parseScienceVector,				NULL, 0x8C },
		{ "IntrinsicSciencesMP",	INI::parseScienceVector,				NULL, 0x98 },
		{ "PurchaseScienceCommandSet",		INI::parseAsciiString,				NULL, 0xA4 },
		{ "PurchaseScienceCommandSetMP",	INI::parseAsciiString,				NULL, 0xA8 },
		{ "SpecialPowerShortcutCommandSet",	INI::parseAsciiString,				NULL, 0xAC },
		{ "SpecialPowerShortcutWinName",	INI::parseAsciiString,				NULL, 0xB0 },
		{ "SpecialPowerShortcutButtonCount",	INI::parseInt,					NULL, 0xB4 },
		{ "IsObserver",			INI::parseBool,						NULL, 0xBC },
		{ "IntrinsicSciencePurchasePoints",	INI::parseInt,					NULL, 0xC0 },
		{ "ScoreScreenImage",		INI::parseAsciiString,				NULL, 0xCC },
		{ "LoadScreenImage",			INI::parseAsciiString,				NULL, 0xD0 },
		{ "LoadScreenMusic",			INI::parseAsciiString,				NULL, 0xB8 },
		{ "HeadWaterMark",			INI::parseAsciiString,				NULL, 0xD4 },
		{ "FlagWaterMark",			INI::parseAsciiString,				NULL, 0xD8 },
		{ "EnabledImage",			INI::parseAsciiString,				NULL, 0xDC },
		{ "SideIconImage",			INI::parseAsciiString,				NULL, 0xE0 },
		{ "BeaconName",			INI::parseAsciiString,				NULL, 0xE4 },
		{ "LightPointsUpSound",			(INIFieldParseProc)b_000babf0,			NULL, 0x100 },
		{ "ObjectiveAddedSound",			(INIFieldParseProc)b_000babf0,			NULL, 0x104 },
		{ "ObjectiveCompletedSound",		(INIFieldParseProc)b_000babf0,			NULL, 0x108 },
		{ "InitialUpgrades",		INI::parseAsciiStringVector,			NULL, 0xE8 },
		{ "DefaultPlayerAIType",		INI::parseAsciiString,				NULL, 0x10C },
		{ "SpellBook",				INI::parseAsciiString,				NULL, 0x110 },
		{ "SpellBookMp",			INI::parseAsciiString,				NULL, 0x114 },
		{ "MaxLevelMP",			INI::parseInt,					NULL, 0xC4 },
		{ "MaxLevelSP",			INI::parseInt,					NULL, 0xC8 },
		{ "Evil",				INI::parseBool,						NULL, 0x118 },
		{ "BuildableHeroesMP",		INI::parseAsciiStringVector,			NULL, 0xF4 },
		{ "SpellStoreCurrentPowerLabel",	INI::parseAsciiString,				NULL, 0x11C },
		{ "SpellStoreMaximumPowerLabel",	INI::parseAsciiString,				NULL, 0x120 },

		{ NULL,						NULL,										NULL, 0 },
	};

	return TheFieldParseTable;
}

// ?getStartingUnit@PlayerTemplate@@QBE?AVAsciiString@@H@Z present-unmatched
AsciiString PlayerTemplate::getStartingUnit( Int i ) const
{
	if (i<0 || i>= MAX_MP_STARTING_UNITS)
		return AsciiString::TheEmptyString;

	return m_startingUnits[i];
}

//-------------------------------------------------------------------------------------------------
// This is is a Template, and a percent change to the cost of producing it.
/*static*/ void PlayerTemplate::parseProductionCostChange( INI* ini, void *instance, void *store, const void* /*userData*/ )
{
	PlayerTemplate* self = (PlayerTemplate*)instance;

	NameKeyType buildTemplateKey = NAMEKEY(ini->getNextToken());
	Real percentChange = INI::scanPercentToReal(ini->getNextToken());

	(*reinterpret_cast<ProductionChangeMap *>(reinterpret_cast<char *>(self) + 0x60))[buildTemplateKey] = percentChange;
}

class BFMEPlayerTemplateAsciiString
{
public:
	BFMEPlayerTemplateAsciiString( const char *text );
	~BFMEPlayerTemplateAsciiString();

private:
	void *m_data;
};

//-------------------------------------------------------------------------------------------------
/*static*/ void PlayerTemplate::parseProductionTimeChange( INI* ini, void *instance, void *store, const void* /*userData*/ )
{
	PlayerTemplate* self = (PlayerTemplate*)instance;

	typedef std::map< AsciiString, Real, std::less<AsciiString> > BFMEProductionTimeChangeMap;
	BFMEPlayerTemplateAsciiString buildTemplateKey( ini->getNextToken() );
	Real percentChange = INI::scanPercentToReal(ini->getNextToken());

	AsciiString &key = *reinterpret_cast<AsciiString *>(&buildTemplateKey);
	(*reinterpret_cast<BFMEProductionTimeChangeMap *>(reinterpret_cast<char *>(self) + 0x6C))[key] = percentChange;
}

//-------------------------------------------------------------------------------------------------
/*static*/ void PlayerTemplate::parseProductionVeterancyLevel( INI* ini, void *instance, void *store, const void* /*userData*/ )
{
	PlayerTemplate* self = (PlayerTemplate*)instance;

	// Format is ThingTemplatename VeterancyName
	AsciiString HACK = AsciiString(ini->getNextToken());
	NameKeyType buildTemplateKey = NAMEKEY(HACK.str());

	VeterancyLevel startLevel = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), TheVeterancyNames);
	self->m_productionVeterancyLevels[buildTemplateKey] = startLevel;
}

//-------------------------------------------------------------------------------------------------
/** Parse integer money and deposit in the m_money */
//-------------------------------------------------------------------------------------------------
/*static*/ void PlayerTemplate::parseStartMoney( INI* ini, void *instance, void *store, const void* /*userData*/ )
{
	Int money = 0;

	// parse the money as a regular "FIELD = <integer>"
	INI::parseInt( ini, instance, &money, NULL );

	// assign the money into the 'Money' (m_money) pointed to at 'store'
	Money *theMoney = (Money *)store;
	theMoney->init();
	theMoney->deposit( money );

}  // end parseStartMoney

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
class BfmeThingEFG
{
public:
	void bfmeClearEFG();
	void bfmeCopyEFG(BfmeThingEFG *that);
};

class PlayerTemplateProductionTimeChangeMap
{
public:
	PlayerTemplateProductionTimeChangeMap &operator=(const PlayerTemplateProductionTimeChangeMap &that)
	{
		if (&that != this)
		{
			((BfmeThingEFG *)this)->bfmeClearEFG();
			((BfmeThingEFG *)this)->bfmeCopyEFG((BfmeThingEFG *)&that);
		}
		return *this;
	}

	unsigned char m_data[0x14];
};

class PlayerTemplateSoundObject
{
public:
	virtual ~PlayerTemplateSoundObject();
	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class PlayerTemplateSoundEvent
{
public:
	PlayerTemplateSoundEvent &operator=(const PlayerTemplateSoundEvent &that)
	{
		if (this != &that)
		{
			PlayerTemplateSoundObject *source = (PlayerTemplateSoundObject *)that.m_data;
			if (source != 0)
				InterlockedIncrement(&source->m_refCount);

			if (m_data != 0)
			{
				PlayerTemplateSoundObject *old = (PlayerTemplateSoundObject *)m_data;
				old->Release_Ref();
			}

			m_data = that.m_data;
		}
		return *this;
	}

	void *m_data;
};

class PlayerTemplateView
{
public:
	NameKeyType m_nameKey;
	UnicodeString m_displayName;
	AsciiString m_side;
	Handicap m_handicap;
	Money m_money;
	RGBColor m_preferredColor;
	AsciiString m_startingBuilding;
	AsciiString m_startingUnits[MAX_MP_STARTING_UNITS];
	ProductionChangeMap m_productionCostChanges;
	PlayerTemplateProductionTimeChangeMap m_productionTimeChanges;
	ProductionVeterancyMap m_productionVeterancyLevels;
	ScienceVec m_intrinsicSciences;
	ScienceVec m_intrinsicSciencesMP;
	AsciiString m_purchaseScienceCommandSet;
	AsciiString m_purchaseScienceCommandSetMP;
	AsciiString m_specialPowerShortcutCommandSet;
	AsciiString m_specialPowerShortcutWinName;
	Int m_specialPowerShortcutButtonCount;
	AsciiString m_loadScreenMusic;
	Bool m_observer;
	Bool m_playableSide;
	Int m_intrinsicSPP;
	Int m_maxLevelMP;
	Int m_maxLevelSP;
	AsciiString m_scoreScreenImage;
	AsciiString m_loadScreenImage;
	AsciiString m_headWaterMark;
	AsciiString m_flagWaterMark;
	AsciiString m_enabledImage;
	AsciiString m_sideIconImage;
	AsciiString m_beaconTemplate;
	std::vector<AsciiString> m_initialUpgrades;
	std::vector<AsciiString> m_buildableHeroesMP;
	PlayerTemplateSoundEvent m_lightPointsUpSound;
	PlayerTemplateSoundEvent m_objectiveAddedSound;
	PlayerTemplateSoundEvent m_objectiveCompletedSound;
	AsciiString m_defaultPlayerAIType;
	AsciiString m_spellBook;
	AsciiString m_spellBookMP;
	Bool m_evil;
	AsciiString m_spellStoreCurrentPowerLabel;
	AsciiString m_spellStoreMaximumPowerLabel;
};

class PlayerTemplateAssignShim
{
public:
	PlayerTemplate &assign(const PlayerTemplate &that);
	NameKeyType m_nameKey;
	UnicodeString m_displayName;
	AsciiString m_side;
	Handicap m_handicap;
	Money m_money;
	RGBColor m_preferredColor;
	AsciiString m_startingBuilding;
	AsciiString m_startingUnits[MAX_MP_STARTING_UNITS];
	ProductionChangeMap m_productionCostChanges;
	PlayerTemplateProductionTimeChangeMap m_productionTimeChanges;
	ProductionVeterancyMap m_productionVeterancyLevels;
	ScienceVec m_intrinsicSciences;
	ScienceVec m_intrinsicSciencesMP;
	AsciiString m_purchaseScienceCommandSet;
	AsciiString m_purchaseScienceCommandSetMP;
	AsciiString m_specialPowerShortcutCommandSet;
	AsciiString m_specialPowerShortcutWinName;
	Int m_specialPowerShortcutButtonCount;
	AsciiString m_loadScreenMusic;
	Bool m_observer;
	Bool m_playableSide;
	Int m_intrinsicSPP;
	Int m_maxLevelMP;
	Int m_maxLevelSP;
	AsciiString m_scoreScreenImage;
	AsciiString m_loadScreenImage;
	AsciiString m_headWaterMark;
	AsciiString m_flagWaterMark;
	AsciiString m_enabledImage;
	AsciiString m_sideIconImage;
	AsciiString m_beaconTemplate;
	std::vector<AsciiString> m_initialUpgrades;
	std::vector<AsciiString> m_buildableHeroesMP;
	PlayerTemplateSoundEvent m_lightPointsUpSound;
	PlayerTemplateSoundEvent m_objectiveAddedSound;
	PlayerTemplateSoundEvent m_objectiveCompletedSound;
	AsciiString m_defaultPlayerAIType;
	AsciiString m_spellBook;
	AsciiString m_spellBookMP;
	Bool m_evil;
	AsciiString m_spellStoreCurrentPowerLabel;
	AsciiString m_spellStoreMaximumPowerLabel;
};

PlayerTemplate &PlayerTemplateAssignShim::assign(const PlayerTemplate &that)
{
#define PT_SOURCE reinterpret_cast<const PlayerTemplateView *>(&that)
#define PT_COPY_ASCII(destination, source) reinterpret_cast<StringBase<char> &>(destination).set(reinterpret_cast<const StringBase<char> &>(source))
#define PT_COPY_WIDE(destination, source) reinterpret_cast<StringBase<WideChar> &>(destination).set(reinterpret_cast<const StringBase<WideChar> &>(source))
	m_nameKey = PT_SOURCE->m_nameKey;
	PT_COPY_WIDE(m_displayName, PT_SOURCE->m_displayName);
	PT_COPY_ASCII(m_side, PT_SOURCE->m_side);
	m_handicap = PT_SOURCE->m_handicap;
	m_money = PT_SOURCE->m_money;
	m_preferredColor = PT_SOURCE->m_preferredColor;
	PT_COPY_ASCII(m_startingBuilding, PT_SOURCE->m_startingBuilding);
	for (Int i = 0; i < MAX_MP_STARTING_UNITS; ++i)
		PT_COPY_ASCII(m_startingUnits[i], PT_SOURCE->m_startingUnits[i]);
	m_productionCostChanges = PT_SOURCE->m_productionCostChanges;
	m_productionTimeChanges = PT_SOURCE->m_productionTimeChanges;
	m_productionVeterancyLevels = PT_SOURCE->m_productionVeterancyLevels;
	m_intrinsicSciences = PT_SOURCE->m_intrinsicSciences;
	m_intrinsicSciencesMP = PT_SOURCE->m_intrinsicSciencesMP;
	PT_COPY_ASCII(m_purchaseScienceCommandSet, PT_SOURCE->m_purchaseScienceCommandSet);
	PT_COPY_ASCII(m_purchaseScienceCommandSetMP, PT_SOURCE->m_purchaseScienceCommandSetMP);
	PT_COPY_ASCII(m_specialPowerShortcutCommandSet, PT_SOURCE->m_specialPowerShortcutCommandSet);
	PT_COPY_ASCII(m_specialPowerShortcutWinName, PT_SOURCE->m_specialPowerShortcutWinName);
	m_specialPowerShortcutButtonCount = PT_SOURCE->m_specialPowerShortcutButtonCount;
	PT_COPY_ASCII(m_loadScreenMusic, PT_SOURCE->m_loadScreenMusic);
	m_observer = PT_SOURCE->m_observer;
	m_playableSide = PT_SOURCE->m_playableSide;
	m_intrinsicSPP = PT_SOURCE->m_intrinsicSPP;
	m_maxLevelMP = PT_SOURCE->m_maxLevelMP;
	m_maxLevelSP = PT_SOURCE->m_maxLevelSP;
	PT_COPY_ASCII(m_scoreScreenImage, PT_SOURCE->m_scoreScreenImage);
	PT_COPY_ASCII(m_loadScreenImage, PT_SOURCE->m_loadScreenImage);
	PT_COPY_ASCII(m_headWaterMark, PT_SOURCE->m_headWaterMark);
	PT_COPY_ASCII(m_flagWaterMark, PT_SOURCE->m_flagWaterMark);
	PT_COPY_ASCII(m_enabledImage, PT_SOURCE->m_enabledImage);
	PT_COPY_ASCII(m_sideIconImage, PT_SOURCE->m_sideIconImage);
	PT_COPY_ASCII(m_beaconTemplate, PT_SOURCE->m_beaconTemplate);
	m_initialUpgrades = PT_SOURCE->m_initialUpgrades;
	m_buildableHeroesMP = PT_SOURCE->m_buildableHeroesMP;
	m_lightPointsUpSound = PT_SOURCE->m_lightPointsUpSound;
	m_objectiveAddedSound = PT_SOURCE->m_objectiveAddedSound;
	m_objectiveCompletedSound = PT_SOURCE->m_objectiveCompletedSound;
	PT_COPY_ASCII(m_defaultPlayerAIType, PT_SOURCE->m_defaultPlayerAIType);
	PT_COPY_ASCII(m_spellBook, PT_SOURCE->m_spellBook);
	PT_COPY_ASCII(m_spellBookMP, PT_SOURCE->m_spellBookMP);
	m_evil = PT_SOURCE->m_evil;
	PT_COPY_ASCII(m_spellStoreCurrentPowerLabel, PT_SOURCE->m_spellStoreCurrentPowerLabel);
	PT_COPY_ASCII(m_spellStoreMaximumPowerLabel, PT_SOURCE->m_spellStoreMaximumPowerLabel);
	#undef PT_COPY_WIDE
	#undef PT_COPY_ASCII
	#undef PT_SOURCE
	return *reinterpret_cast<PlayerTemplate *>(this);
}

// ??0PlayerTemplate@@QAE@XZ exact retail body is emitted by
// PlayerTemplateCtorThunk.cpp.
//-----------------------------------------------------------------------------
// getHeadWaterMarkImage uses the retail BFME layout in PlayerTemplateImageGettersBFME.cpp.

//-----------------------------------------------------------------------------
// getFlagWaterMarkImage uses the retail BFME layout in PlayerTemplateImageGettersBFME.cpp.

//-----------------------------------------------------------------------------
// getSideIconImage uses the retail BFME layout in PlayerTemplateImageGettersBFME.cpp.

//-----------------------------------------------------------------------------
// ?getGeneralImage@PlayerTemplate@@QBEPBVImage@@XZ absent-from-retail
const Image *PlayerTemplate::getGeneralImage( void ) const
{
	return TheMappedImageCollection->findImageByName(m_generalImage);
}

//-----------------------------------------------------------------------------
// getEnabledImage uses the retail BFME layout in PlayerTemplateImageGettersBFME.cpp.

//-----------------------------------------------------------------------------
//const Image *PlayerTemplate::getDisabledImage( void ) const
//{
//	return TheMappedImageCollection->findImageByName(m_disabledImage);
//}

//-----------------------------------------------------------------------------
//const Image *PlayerTemplate::getHiliteImage( void ) const
//{
//	return TheMappedImageCollection->findImageByName(m_hiliteImage);
//}

//-----------------------------------------------------------------------------
//const Image *PlayerTemplate::getPushedImage( void ) const
//{
//	return TheMappedImageCollection->findImageByName(m_pushedImage);
//}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/*extern*/ PlayerTemplateStore *ThePlayerTemplateStore = NULL;

//-----------------------------------------------------------------------------
PlayerTemplateStore::PlayerTemplateStore() 
{
	// nothing
}

//-----------------------------------------------------------------------------
PlayerTemplateStore::~PlayerTemplateStore() 
{
	// nothing
}

//-----------------------------------------------------------------------------
void PlayerTemplateStore::init()
{
	m_playerTemplates.clear();
}

//-----------------------------------------------------------------------------
void PlayerTemplateStore::reset()
{
// don't reset this list here; we want to retain this info.
//	m_playerTemplates.clear();
}

//-----------------------------------------------------------------------------
void PlayerTemplateStore::update()
{
	// nothing
}


// ?getTemplateNumByName@PlayerTemplateStore@@QBEHVAsciiString@@@Z present-unmatched
Int PlayerTemplateStore::getTemplateNumByName(AsciiString name) const
{
	for (Int num = 0; num < m_playerTemplates.size(); num++)
	{
		if (m_playerTemplates[num].getName().compareNoCase(name.str()) == 0)
			return num;
	}
	DEBUG_ASSERTCRASH(NULL, ("Template doesn't exist for given name"));
	return -1;
}

//-----------------------------------------------------------------------------
const PlayerTemplate* PlayerTemplateStore::findPlayerTemplate(NameKeyType namekey) const
{
// begin ugly, hokey code to quietly load old maps...
	static NameKeyType a0 = NAMEKEY("FactionAmerica");
	static NameKeyType a1 = NAMEKEY("FactionAmericaChooseAGeneral");
	static NameKeyType a2 = NAMEKEY("FactionAmericaTankCommand");
	static NameKeyType a3 = NAMEKEY("FactionAmericaSpecialForces");
	static NameKeyType a4 = NAMEKEY("FactionAmericaAirForce");

	static NameKeyType c0 = NAMEKEY("FactionChina");
	static NameKeyType c1 = NAMEKEY("FactionChinaChooseAGeneral");
	static NameKeyType c2 = NAMEKEY("FactionChinaRedArmy");
	static NameKeyType c3 = NAMEKEY("FactionChinaSpecialWeapons");
	static NameKeyType c4 = NAMEKEY("FactionChinaSecretPolice");

	static NameKeyType g0 = NAMEKEY("FactionGLA");
	static NameKeyType g1 = NAMEKEY("FactionGLAChooseAGeneral");
	static NameKeyType g2 = NAMEKEY("FactionGLATerrorCell");
	static NameKeyType g3 = NAMEKEY("FactionGLABiowarCommand");
	static NameKeyType g4 = NAMEKEY("FactionGLAWarlordCommand");

	if (namekey == a1 || namekey == a2 || namekey == a3 || namekey == a4)
		namekey = a0;
	else if (namekey == c1 || namekey == c2 || namekey == c3 || namekey == c4)
		namekey = c0;
	else if (namekey == g1 || namekey == g2 || namekey == g3 || namekey == g4)
		namekey = g0;
// end ugly, hokey code to quietly load old maps...

	#ifdef _DEBUG
	AsciiString nn = KEYNAME(namekey);
	#endif
  for (PlayerTemplateVector::const_iterator it = m_playerTemplates.begin(); it != m_playerTemplates.end(); ++it)
	{
		#ifdef _DEBUG
		AsciiString n = KEYNAME((*it).getNameKey());
		#endif
		if ((*it).getNameKey() == namekey)
			return &(*it);
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// getNthPlayerTemplate is emitted by the retail-proven
// PlayerTemplateStoreGetAllSideStrings.cpp provider.

//-------------------------------------------------------------------------------------------------
// @todo: PERF_EVALUATE Get a perf timer on this. 
// If this function is called frequently, there are some relatively trivial changes we could make to 
// have it run a lot faster.
// ?getAllSideStrings@PlayerTemplateStore@@QAEXPAV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z present-unmatched
class BFMERetailAsciiString
{
	public:
	void releaseBuffer();
};

template <class T>
class BFMERetailStringBase
{
public:
	BFMERetailStringBase(const BFMERetailStringBase &source);
	~BFMERetailStringBase()
	{
		reinterpret_cast<BFMERetailAsciiString *>(this)->releaseBuffer();
	}

protected:
	T *m_data;
};

struct BFMEFindAsciiStringView : private BFMERetailStringBase<char>
{
	BFMEFindAsciiStringView(const BFMEFindAsciiStringView &source)
		: BFMERetailStringBase<char>(source)
	{
	}

	~BFMEFindAsciiStringView()
	{
	}

	bool operator==(const BFMEFindAsciiStringView &that) const
	{
		return strcmp(static_cast<const char *>(m_data) + 4,
			static_cast<const char *>(that.m_data) + 4) == 0;
	}
};

void PlayerTemplateStore::getAllSideStrings(AsciiStringList *outStringList)
{
	if (!outStringList) 
		return;

	// should outStringList be cleared first? If so, that would go here
	AsciiStringList tmpList;

	Int numTemplates = getPlayerTemplateCount();
	for ( Int i = 0; i < numTemplates; ++i ) 
	{
		const PlayerTemplate *pt = getNthPlayerTemplate(i);
		// Sanity
		if (!pt)			
			continue; 

		std::list<BFMEFindAsciiStringView> &viewList =
			reinterpret_cast<std::list<BFMEFindAsciiStringView> &>(tmpList);
		const BFMEFindAsciiStringView &side =
			reinterpret_cast<const BFMEFindAsciiStringView &>(pt->getSide());
		if (std::find(viewList.begin(), viewList.end(), side) == viewList.end())
			tmpList.push_back(pt->getSide());
	}
	// tmpList is now filled with all unique sides found in the player templates.

	// splice is a constant-time function which takes all elements from tmpList and 
	// inserts them before outStringList->end(), and also removes them from tmpList
	outStringList->splice(outStringList->end(), tmpList);
	
	// all done
}	

//-------------------------------------------------------------------------------------------------
/*static*/ void PlayerTemplateStore::parsePlayerTemplateDefinition( INI* ini )
{
	const char* c = ini->getNextToken();
	NameKeyType namekey = NAMEKEY(c);

	PlayerTemplate* pt = const_cast<PlayerTemplate*>(ThePlayerTemplateStore->findPlayerTemplate(namekey));
	if (pt)
	{
		ini->initFromINI(pt, pt->getFieldParse() );
		pt->setNameKey(namekey);
	}
	else
	{
		PlayerTemplate npt;
		ini->initFromINI( &npt, npt.getFieldParse() );
		npt.setNameKey(namekey);
		ThePlayerTemplateStore->m_playerTemplates.push_back(npt);
	}

}

//-------------------------------------------------------------------------------------------------
// ?parsePlayerTemplateDefinition@INI@@SAXPAV1@@Z present-unmatched
void INI::parsePlayerTemplateDefinition( INI* ini )
{
	PlayerTemplateStore::parsePlayerTemplateDefinition(ini);
}
