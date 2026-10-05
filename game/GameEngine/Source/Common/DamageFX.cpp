// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
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

// FILE: DamageFX.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, November 2001
// Desc:   DamageFX descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "GameLogic/Damage.h"
// BFME has 16 damage types where Zero Hour has 38. DamageFX::clear
// @0x00065EB0 fully unrolls the four veterancy levels into one 0x40-byte
// iteration and then runs `mov edx,0x10; ... dec edx; jne`, so the outer bound
// is 16; the ZH enum makes it 0x26. Only the count is provable from these
// bytes - which sixteen of the names survive is not - so the enum keeps every
// name and only the array bound is pinned. Scoped to this translation unit:
// narrowing it in GameLogic/Damage.h is a header edit and the full gate is red
//.
#define DAMAGE_NUM_TYPES 16

#include "Common/INI.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/DamageFX.h"
#include "Common/GameAudio.h"

#include "GameClient/FXList.h"
#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"

// Retail lookups use the emotion-AI, weapon-set and model-condition tables.
template Int BitFlags<6>::getSingleBitFromName(const char *);
template Int BitFlags<29>::getSingleBitFromName(const char *);
template Int BitFlags<304>::getSingleBitFromName(const char *);

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

DamageFXStore *TheDamageFXStore = NULL;					///< the DamageFX store definition

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASSES ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
DamageFX::DamageFX()
{
	// not necessary.
	//clear();
}

//-------------------------------------------------------------------------------------------------
void DamageFX::clear()
{
	for (Int dt = 0; dt < DAMAGE_NUM_TYPES; ++dt)
	{
		for (Int v = LEVEL_FIRST; v <= LEVEL_LAST; ++v)
		{
			m_dfx[dt][v].clear();
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?getDamageFXThrottleTime@DamageFX@@ present-unmatched
UnsignedInt DamageFX::getDamageFXThrottleTime(DamageType t, const Object* source) const 
{ 
	return m_dfx[t][source ? source->getVeterancyLevel() : LEVEL_REGULAR].m_damageFXThrottleTime; 
}

//-------------------------------------------------------------------------------------------------
// ?getDamageFXList@DamageFX@@ present-unmatched
ConstFXListPtr DamageFX::getDamageFXList(DamageType t, Real damageAmount, const Object* source) const
{ 
	/*
		if damage is zero, never do damage fx. this is by design, since "zero" damage can happen
		with some special weapons, like the battleship, which is a "faux" weapon that never does damage.
		if you really need to change this for some reason, consider carefully... (srj)
	*/
	if (damageAmount == 0.0f)
		return NULL;

	const DFX& dfx = m_dfx[t][source ? source->getVeterancyLevel() : LEVEL_REGULAR];
	ConstFXListPtr fx = 
		damageAmount >= dfx.m_amountForMajorFX ? 
		dfx.m_majorDamageFXList : 
		dfx.m_minorDamageFXList;

	return fx;
}

//-------------------------------------------------------------------------------------------------
const FieldParse* DamageFX::getFieldParse() const
{
	static const FieldParse myFieldParse[] = 
	{
		{ "AmountForMajorFX",						parseAmount,			NULL, 0 },
		{ "MajorFX",										parseMajorFXList,	NULL, 0 },
		{ "MinorFX",										parseMinorFXList,	NULL, 0 },
		{ "ThrottleTime",								parseTime,				NULL, 0 },
		{ "VeterancyAmountForMajorFX",	parseAmount,			TheVeterancyNames, 0 },
		{ "VeterancyMajorFX",						parseMajorFXList,	TheVeterancyNames, 0 },
		{ "VeterancyMinorFX",						parseMinorFXList,	TheVeterancyNames, 0 },
		{ "VeterancyThrottleTime",			parseTime,				TheVeterancyNames, 0 },
		{ 0, 0, 0,0 }
	};
	return myFieldParse;
}

//-------------------------------------------------------------------------------------------Static
static void parseCommonStuff(
	INI* ini, 
	ConstCharPtrArray names, 
	VeterancyLevel& vetFirst, 
	VeterancyLevel& vetLast, 
	DamageType& damageFirst, 
	DamageType& damageLast
)
{
	if (names)
	{
		vetFirst = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), names);
		vetLast = vetFirst;
	}
	else
	{
		vetFirst = LEVEL_FIRST;
		vetLast = LEVEL_LAST;
	}

	const char* damageName = ini->getNextToken();
	if (stricmp(damageName, "Default") == 0)
	{
		damageFirst = (DamageType)0;
		damageLast = (DamageType)(DAMAGE_NUM_TYPES - 1);
	}
	else
	{
		damageFirst = (DamageType)INI::scanIndexList(damageName, DamageTypeFlags::getBitNames());
		damageLast = damageFirst;
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseAmount( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	Real amt = INI::scanReal(ini->getNextToken());

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_amountForMajorFX = amt;
		}
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseMajorFXList( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	ConstFXListPtr fx;
	INI::parseFXList(ini, NULL, &fx, NULL);

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_majorDamageFXList = fx;
		}
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseMinorFXList( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	ConstFXListPtr fx;
	INI::parseFXList(ini, NULL, &fx, NULL);

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_minorDamageFXList = fx;
		}
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseTime( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	UnsignedInt t;
	INI::parseDurationUnsignedInt(ini, NULL, &t, NULL);

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_damageFXThrottleTime = t;
		}
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0DamageFXStore@@QAE@XZ body: DamageFXStore_ctor.asm (exact retail @ 0x00067C10)

//-------------------------------------------------------------------------------------------------
// ??1DamageFXStore@@ present-unmatched
DamageFXStore::~DamageFXStore()
{
	m_dfxmap.clear();
}

//-------------------------------------------------------------------------------------------------
// ?findDamageFX@DamageFXStore@@QBEPBVDamageFX@@VAsciiString@@@Z
// body: DamageFXStore_findDamageFX.asm (exact retail @ 0x00067440)

//-------------------------------------------------------------------------------------------------
// ?init@DamageFXStore@@ present-unmatched
void DamageFXStore::init()
{
	// Force-emit const $_Ht_iterator COMDAT (ICF @ 0x9E5EB0). Was only referenced
	// by former C++ findDamageFX; matched body is DamageFXStore_findDamageFX.asm.
	// init remains present-unmatched (ZH empty stub); find of key 0 is a no-op side effect.
	NameKeyType k = (NameKeyType)0;
	(void)static_cast<const DamageFXMap &>(m_dfxmap).find(k);
}

//-------------------------------------------------------------------------------------------------
// ?reset@DamageFXStore@@ present-unmatched
void DamageFXStore::reset()
{
} 

//-------------------------------------------------------------------------------------------------
// ?update@DamageFXStore@@ present-unmatched
void DamageFXStore::update()
{
}

//-------------------------------------------------------------------------------------------------
/*static */ void DamageFXStore::parseDamageFXDefinition(INI* ini)
{

	const char *c = ini->getNextToken();
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	DamageFX& dfx = TheDamageFXStore->m_dfxmap[key];
	dfx.clear();
	ini->initFromINI(&dfx, dfx.getFieldParse());
}

class Rva000CB630Noop
{
public:
	void noop();
};

void Rva000CB630Noop::noop()
{
}

// Verified retail name table at VA 0x012A6858.
template<> const char *BitFlags<6>::s_bitNameList[] =
{
	"BACK_AWAY",
	"AVOID_SCARER",
	"IDLE",
	"RUN_AWAY_PANIC",
	"FACE_OBJECT",
	"QUARREL",
	NULL
};

// Verified retail name table at VA 0x012AD6B0.
template<> const char *BitFlags<29>::s_bitNameList[] =
{
	"VETERAN",
	"ELITE",
	"HERO",
	"PLAYER_UPGRADE",
	"PASSENGER_TYPE_ONE",
	"PASSENGER_TYPE_TWO",
	"GARRISONED",
	"CLOSE_RANGE",
	"RAMPAGE",
	"CONTESTING_BUILDING",
	"WEAPON_RIDER1",
	"WEAPON_RIDER2",
	"WEAPON_RIDER3",
	"WEAPON_RIDER4",
	"WEAPON_RIDER5",
	"WEAPON_RIDER6",
	"WEAPON_RIDER7",
	"WEAPON_RIDER8",
	"SPECIAL_ONE",
	"SPECIAL_TWO",
	"CONTAINED",
	"MOUNTED",
	"ENRAGED",
	"SPECIAL_UPGRADE",
	"WEAPONSET_TOGGLE_1",
	"WEAPONSET_TOGGLE_2",
	"WEAPONSET_TOGGLE_3",
	"WEAPONSET_HERO_MODE",
	"WEAPONSET_ONE_RING_MODE",
	NULL
};

// Verified retail name table at VA 0x012A6918.
template<> const char *BitFlags<304>::s_bitNameList[] =
{
	"TOPPLED",
	"FRONTCRUSHED",
	"BACKCRUSHED",
	"DAMAGED",
	"REALLYDAMAGED",
	"RUBBLE",
	"SPECIAL_DAMAGED",
	"NIGHT",
	"SNOW",
	"PARACHUTING",
	"GARRISONED",
	"ENEMYNEAR",
	"WEAPONSET_VETERAN",
	"WEAPONSET_ELITE",
	"WEAPONSET_HERO",
	"WEAPONSET_PASSENGER_TYPE_ONE",
	"WEAPONSET_PASSENGER_TYPE_TWO",
	"WEAPONSET_PLAYER_UPGRADE",
	"WEAPONSTATE_ONE",
	"WEAPONSTATE_TWO",
	"WEAPONSTATE_THREE",
	"DOOR_1_OPENING",
	"DOOR_1_CLOSING",
	"DOOR_1_WAITING_OPEN",
	"DOOR_1_WAITING_TO_CLOSE",
	"DOOR_2_OPENING",
	"DOOR_2_CLOSING",
	"DOOR_2_WAITING_OPEN",
	"DOOR_2_WAITING_TO_CLOSE",
	"DOOR_3_OPENING",
	"DOOR_3_CLOSING",
	"DOOR_3_WAITING_OPEN",
	"DOOR_3_WAITING_TO_CLOSE",
	"DOOR_4_OPENING",
	"DOOR_4_CLOSING",
	"DOOR_4_WAITING_OPEN",
	"DOOR_4_WAITING_TO_CLOSE",
	"ATTACKING",
	"ATTACKING_STRUCTURE",
	"PREATTACK_A",
	"FIRING_A",
	"FIRING_OR_PREATTACK_A",
	"FIRING_OR_RELOADING_A",
	"BETWEEN_FIRING_SHOTS_A",
	"RELOADING_A",
	"PREATTACK_B",
	"FIRING_B",
	"FIRING_OR_PREATTACK_B",
	"FIRING_OR_RELOADING_B",
	"BETWEEN_FIRING_SHOTS_B",
	"RELOADING_B",
	"PREATTACK_C",
	"FIRING_C",
	"FIRING_OR_PREATTACK_C",
	"FIRING_OR_RELOADING_C",
	"BETWEEN_FIRING_SHOTS_C",
	"RELOADING_C",
	"TURRET_ROTATE",
	"POST_RUBBLE",
	"POST_COLLAPSE",
	"MOVING",
	"DYING",
	"EMOTION_ALERT",
	"EMOTION_AFRAID",
	"EMOTION_TERROR",
	"EMOTION_PANIC",
	"AWAITING_CONSTRUCTION",
	"PARTIALLY_CONSTRUCTED",
	"ACTIVELY_BEING_CONSTRUCTED",
	"UNIT_ACTIVELY_BEING_CONSTRUCTED",
	"PRONE",
	"FREEFALL",
	"ACTIVELY_CONSTRUCTING",
	"CONSTRUCTION_COMPLETE",
	"RADAR_EXTENDING",
	"RADAR_UPGRADED",
	"PANICKING",
	"AFLAME",
	"SMOLDERING",
	"BURNED",
	"DOCKING",
	"DOCKING_BEGINNING",
	"DOCKING_ACTIVE",
	"DOCKING_ENDING",
	"CARRYING",
	"FLOODED",
	"LOADED",
	"PASSENGER",
	"TRANSPORT_MOVING",
	"TRANSPORT_STOPPED",
	"CLUB",
	"JETAFTERBURNER",
	"JETEXHAUST",
	"PACKING",
	"PREPARING",
	"UNPACKING",
	"PACKING_TYPE_1",
	"PACKING_TYPE_2",
	"PACKING_TYPE_3",
	"DEPLOYED",
	"OVER_WATER",
	"POWER_PLANT_UPGRADED",
	"CLIMBING",
	"SOLD",
	"RAPPELLING",
	"ARMED",
	"POWER_PLANT_UPGRADING",
	"SPECIAL_CHEERING",
	"CONTINUOUS_FIRE_SLOW",
	"CONTINUOUS_FIRE_MEAN",
	"CONTINUOUS_FIRE_FAST",
	"RAISING_FLAG",
	"CAPTURED",
	"EXPLODED_FLAILING",
	"EXPLODED_BOUNCING",
	"SPLATTED",
	"USING_WEAPON_A",
	"USING_WEAPON_B",
	"USING_WEAPON_C",
	"PREORDER",
	"STUNNED_FLAILING",
	"STUNNED",
	"WANDER",
	"WALKING",
	"CHARGING",
	"TURN_LEFT",
	"TURN_RIGHT",
	"ACCELERATE",
	"DECELERATE",
	"TURN_LEFT_HIGH_SPEED",
	"TURN_RIGHT_HIGH_SPEED",
	"DESTROYED_FRONT",
	"DESTROYED_RIGHT",
	"DESTROYED_BACK",
	"DESTROYED_LEFT",
	"WEAPONSET_GARRISONED",
	"WEAPONLOCK_PRIMARY",
	"WEAPONLOCK_SECONDARY",
	"WEAPONLOCK_TERTIARY",
	"DEATH_1",
	"DEATH_2",
	"DEATH_3",
	"DEATH_4",
	"DECAY",
	"THROWN_PROJECTILE",
	"ABOUT_TO_HIT",
	"BACKING_UP",
	"ENGAGED",
	"DEFLECT_SPECIAL_POWER",
	"WEAPONSET_CLOSE_RANGE",
	"WEAPONSTATE_CLOSE_RANGE",
	"WEAPONSET_RAMPAGE",
	"RAMPAGE_ANIMATION_ONLY",
	"STUNNED_STANDING_UP",
	"REACT_1",
	"REACT_2",
	"REACT_3",
	"REACT_4",
	"REACT_5",
	"REACT_6",
	"SELECTED",
	"GUARDING",
	"HIT_REACTION",
	"HIT_LEVEL_1",
	"HIT_LEVEL_2",
	"HIT_LEVEL_3",
	"GRAB_BUILDING_CHUNK",
	"DEATH_5",
	"AIM_HIGH",
	"AIM_STRAIGHT",
	"AIM_LOW",
	"AIM_NEAR",
	"AIM_FAR",
	"DIVING",
	"USER_1",
	"USER_2",
	"USER_3",
	"USER_4",
	"USER_5",
	"SWOOPING",
	"BURNT_MODEL",
	"BURNT_TEXTURE",
	"WEAPONSET_CONTESTING_BUILDING",
	"DEBUG",
	"PASSENGER_VARIATION_1",
	"PASSENGER_VARIATION_2",
	"PASSENGER_VARIATION_3",
	"PASSENGER_VARIATION_4",
	"PASSENGER_VARIATION_5",
	"EMOTION_GUNG_HO",
	"EMOTION_LOOK_TO_SKY",
	"EMOTION_CELEBRATING",
	"EMOTION_AMUSED",
	"EMOTION_MORALE_HIGH",
	"EMOTION_MORALE_LOW",
	"EMOTION_COWER",
	"USING_SPECIAL_ABILITY",
	"WORLD_BUILDER",
	"SIEGE_CONTAIN",
	"LEVELED",
	"SPECIAL_POWER_1",
	"SPECIAL_POWER_2",
	"SPECIAL_POWER_3",
	"MOUNTED",
	"OATH_FULLFILLED",
	"RESURRECTED",
	"DESTROYED_WEAPON",
	"JUST_BUILT",
	"BASE_BUILD",
	"HERO",
	"RIDER1",
	"RIDER2",
	"RIDER3",
	"RIDER4",
	"RIDER5",
	"RIDER6",
	"RIDER7",
	"RIDER8",
	"WEAPONSET_RIDER1",
	"WEAPONSET_RIDER2",
	"WEAPONSET_RIDER3",
	"WEAPONSET_RIDER4",
	"WEAPONSET_RIDER5",
	"WEAPONSET_RIDER6",
	"WEAPONSET_RIDER7",
	"WEAPONSET_RIDER8",
	"WEAPONSET_SPECIAL_ONE",
	"WEAPONSET_SPECIAL_TWO",
	"WADING",
	"SWIMMING",
	"WEAPONSET_CONTAINED",
	"WEAPONSTATE_CONTAINED",
	"HORDE_EMPTY",
	"SPECIAL_WEAPON_ONE",
	"SPECIAL_WEAPON_TWO",
	"SPECIAL_WEAPON_THREE",
	"WEAPONSET_MOUNTED",
	"EATING",
	"CHANT_FOR_GROND",
	"WEAPONSET_ENRAGED",
	"WEAPONSET_SPECIAL_UPGRADE",
	"RUNNING_OFF_MAP",
	"ONE_RING",
	"PRIMARY_FORMATION",
	"ALTERNATE_FORMATION",
	"HARVEST_PREPARATION",
	"HARVEST_ACTION",
	"SPECIAL_ENEMY_NEAR",
	"HIDDEN",
	"PUTTING_ON_RING",
	"TAKING_OFF_RING",
	"UPGRADE_BOILING_OIL",
	"UPGRADE_GARRISON",
	"UPGRADE_POSTERN_GATE",
	"UPGRADE_TREBUCHET",
	"UPGRADE_NUMENOR_STONEWORK",
	"UPGRADE_BLANK2",
	"UPGRADE_BLANK3",
	"UPGRADE_BLANK4",
	"DRILL0",
	"DRILL1",
	"DRILL2",
	"DRILL3",
	"DRILL4",
	"RIDERLESS",
	"DRAFTED",
	"UPGRADED_ARMOR",
	"DISGUISED",
	"WEAPONSET_TOGGLE_1",
	"WEAPONSET_TOGGLE_2",
	"WEAPONSET_TOGGLE_3",
	"WEAPONSET_HERO_MODE",
	"DOCKING_PRE_DOCK",
	"TURRET_ANGLE_0",
	"TURRET_ANGLE_90",
	"TURRET_ANGLE_180",
	"TURRET_ANGLE_270",
	"USING_COMBO_LOCOMOTOR",
	"WAR_CHANT",
	"EMOTION_QUARRELSOME",
	"QUARRELSOME_FIGHTING",
	"UNCONTROLLABLE",
	"INITIAL_ENRAGED",
	"ARMORSET_VETERAN",
	"ARMORSET_ELITE",
	"ARMORSET_HERO",
	"ARMORSET_WEAK_VERSUS_BASEDEFENSES",
	"ARMORSET_ALTERNATE_FORMATION",
	"ARMORSET_MOUNTED",
	"ARMORSET_PLAYER_UPGRADE",
	"ARMORSET_PLAYER_UPGRADE_2",
	"ARMORSET_PLAYER_UPGRADE_3",
	"ARMORSET_UNBESIEGEABLE",
	"EMOTION_TAUNTING",
	"EMOTION_DOOM",
	"EMOTION_POINTING",
	"WEAPON_TOGGLING",
	"INVULNERABLE",
	"MARCHING",
	"UPGRADE_ECONOMY_BONUS",
	"COMING_OUT_OF_FACTORY",
	"DESTROYED_WHILST_BEING_CONSTRUCTED",
	"COLLAPSING",
	"EMOTION_UNCONTROLLABLY_AFRAID",
	NULL
};
