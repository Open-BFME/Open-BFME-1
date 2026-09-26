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
/*static*/ const FieldParse* PlayerTemplate::getFieldParse()
{
	static const FieldParse TheFieldParseTable[] = 
	{
		{ "Side",											INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_side ) },
		{ "BaseSide",								INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_baseSide ) },
		{ "PlayableSide",							INI::parseBool,																	NULL, offsetof( PlayerTemplate, m_playableSide ) },
		{ "DisplayName",							INI::parseAndTranslateLabel,										NULL, offsetof( PlayerTemplate, m_displayName) },
		{ "StartMoney",								PlayerTemplate::parseStartMoney,								NULL, offsetof( PlayerTemplate, m_money ) },
		{ "PreferredColor",						INI::parseRGBColor,															NULL, offsetof( PlayerTemplate, m_preferredColor ) },
		{ "StartingBuilding",					INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingBuilding ) },
		{ "StartingUnit0",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[0] ) },
		{ "StartingUnit1",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[1] ) },
		{ "StartingUnit2",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[2] ) },
		{ "StartingUnit3",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[3] ) },
		{ "StartingUnit4",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[4] ) },
		{ "StartingUnit5",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[5] ) },
		{ "StartingUnit6",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[6] ) },
		{ "StartingUnit7",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[7] ) },
		{ "StartingUnit8",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[8] ) },
		{ "StartingUnit9",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_startingUnits[9] ) },
		{ "ProductionCostChange",			PlayerTemplate::parseProductionCostChange,			NULL, 0 },
		{ "ProductionTimeChange",			PlayerTemplate::parseProductionTimeChange,			NULL, 0 },
		{ "ProductionVeterancyLevel",	PlayerTemplate::parseProductionVeterancyLevel,	NULL, 0 },
		{ "IntrinsicSciences",				INI::parseScienceVector,												NULL, offsetof( PlayerTemplate, m_intrinsicSciences ) },
		{ "PurchaseScienceCommandSetRank1",INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_purchaseScienceCommandSetRank1 ) },
		{ "PurchaseScienceCommandSetRank3",INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_purchaseScienceCommandSetRank3 ) },
		{ "PurchaseScienceCommandSetRank8",INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_purchaseScienceCommandSetRank8 ) },
		{ "SpecialPowerShortcutCommandSet",INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_specialPowerShortcutCommandSet ) },
		{ "SpecialPowerShortcutWinName"		,INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_specialPowerShortcutWinName) },
		{ "SpecialPowerShortcutButtonCount",INI::parseInt,												NULL, offsetof( PlayerTemplate, m_specialPowerShortcutButtonCount ) },
		{ "IsObserver",								INI::parseBool,																	NULL, offsetof( PlayerTemplate, m_observer ) },
    { "OldFaction",               INI::parseBool,                                 NULL, offsetof( PlayerTemplate, m_oldFaction ) },
		{ "IntrinsicSciencePurchasePoints",				INI::parseInt,												NULL, offsetof( PlayerTemplate, m_intrinsicSPP ) },
		{ "ScoreScreenImage",					INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_scoreScreenImage ) },
		{ "LoadScreenImage",					INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_loadScreenImage ) },
		{ "LoadScreenMusic",					INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_loadScreenMusic ) },
		{ "ScoreScreenMusic",					INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_scoreScreenMusic ) },

		{ "HeadWaterMark",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_headWaterMark ) },
		{ "FlagWaterMark",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_flagWaterMark ) },
		{ "EnabledImage",							INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_enabledImage ) },
		//{ "DisabledImage",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_disabledImage ) },
		//{ "HiliteImage",							INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_hiliteImage ) },
		//{ "PushedImage",							INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_pushedImage ) },
		{ "SideIconImage",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_sideIconImage ) },
		{ "GeneralImage",						INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_generalImage ) },

		{ "BeaconName",								INI::parseAsciiString,													NULL, offsetof( PlayerTemplate, m_beaconTemplate ) },
		{ "ArmyTooltip",						INI::parseAsciiString,					NULL, offsetof( PlayerTemplate, m_tooltip ) },
		{ "Features",						INI::parseAsciiString,					NULL, offsetof( PlayerTemplate, m_strGeneralFeatures ) },
		{ "MedallionRegular",						INI::parseAsciiString,					NULL, offsetof( PlayerTemplate, m_strMedallionNormal ) },
		{ "MedallionHilite",						INI::parseAsciiString,					NULL, offsetof( PlayerTemplate, m_strMedallionHilite ) },
		{ "MedallionSelect",						INI::parseAsciiString,					NULL, offsetof( PlayerTemplate, m_strMedallionSelected ) },

		{ NULL,											NULL,																				NULL, 0 },
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
// ?getHeadWaterMarkImage@PlayerTemplate@@QBEPBVImage@@XZ present-unmatched
const Image *PlayerTemplate::getHeadWaterMarkImage( void ) const
{
	return TheMappedImageCollection->findImageByName(m_headWaterMark);
}

//-----------------------------------------------------------------------------
// ?getFlagWaterMarkImage@PlayerTemplate@@QBEPBVImage@@XZ present-unmatched
const Image *PlayerTemplate::getFlagWaterMarkImage( void ) const
{
	return TheMappedImageCollection->findImageByName(m_flagWaterMark);
}

//-----------------------------------------------------------------------------
const Image *PlayerTemplate::getSideIconImage( void ) const
{
	return TheMappedImageCollection->findImageByName(m_sideIconImage);
}

//-----------------------------------------------------------------------------
// ?getGeneralImage@PlayerTemplate@@QBEPBVImage@@XZ absent-from-retail
const Image *PlayerTemplate::getGeneralImage( void ) const
{
	return TheMappedImageCollection->findImageByName(m_generalImage);
}

//-----------------------------------------------------------------------------
// ?getEnabledImage@PlayerTemplate@@QBEPBVImage@@XZ present-unmatched
const Image *PlayerTemplate::getEnabledImage( void ) const
{
	return TheMappedImageCollection->findImageByName(m_enabledImage);
}

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
const PlayerTemplate* PlayerTemplateStore::getNthPlayerTemplate(Int i) const
{
	if (i >= 0 && i < m_playerTemplates.size())
		return &m_playerTemplates[i];

	return NULL;
}

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
