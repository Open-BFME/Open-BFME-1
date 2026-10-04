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

// FILE: BattlePlanUpdate.cpp //////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, September 2002
// Desc:   Update module to handle building states and battle plan execution & changes
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_MAXHEALTHCHANGETYPE_NAMES						// for TheMaxHealthChangeTypeNames[]

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/BitFlagsIO.h"
#include "Common/Radar.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/Xfer.h"

#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/FXList.h"
#include "GameClient/ControlBar.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectIter.h"
#include "GameLogic/Weaponset.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/StealthDetectorUpdate.h"

// BitFlags<116>::xfer is retail's one out-of-line body (BitFlags116Xfer.cpp); do not emit a header copy.
template<> void BitFlags<116>::xfer(Xfer *);
// The header xfer copy no longer instantiates the count()/getSingleBitFromName() retail emits here.
template Int BitFlags<116>::count() const;
template Int BitFlags<116>::getSingleBitFromName(const char *);

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/AI/BattlePlanUpdateModuleDataCtorThunk.cpp
// ??0BattlePlanUpdateModuleData@@QAE@XZ present-unmatched
BattlePlanUpdateModuleData::BattlePlanUpdateModuleData()
{
	m_specialPowerTemplate								= NULL;
	m_bombardmentPlanAnimationFrames			= 0;
	m_holdTheLinePlanAnimationFrames			= 0;
	m_searchAndDestroyPlanAnimationFrames = 0;
	m_battlePlanParalyzeFrames						= 0;

	
	m_holdTheLineArmorDamageScalar				= 1.0f;
	m_searchAndDestroySightRangeScalar		= 1.0f;
	m_strategyCenterSearchAndDestroySightRangeScalar = 1.0f;
	m_strategyCenterSearchAndDestroyDetectsStealth = true;
	m_strategyCenterHoldTheLineMaxHealthScalar = 1.0f;
	m_strategyCenterHoldTheLineMaxHealthChangeType = PRESERVE_RATIO;

}

//-------------------------------------------------------------------------------------------------
/*static*/ void BattlePlanUpdateModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	ModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "SpecialPowerTemplate",									INI::parseSpecialPowerTemplate,	NULL, offsetof( BattlePlanUpdateModuleData, m_specialPowerTemplate ) },

    { "BombardmentPlanAnimationTime",					INI::parseDurationUnsignedInt,  NULL, offsetof( BattlePlanUpdateModuleData, m_bombardmentPlanAnimationFrames ) },
    { "HoldTheLinePlanAnimationTime",					INI::parseDurationUnsignedInt,  NULL, offsetof( BattlePlanUpdateModuleData, m_holdTheLinePlanAnimationFrames ) },
    { "SearchAndDestroyPlanAnimationTime",		INI::parseDurationUnsignedInt,  NULL, offsetof( BattlePlanUpdateModuleData, m_searchAndDestroyPlanAnimationFrames ) },
		{ "TransitionIdleTime",										INI::parseDurationUnsignedInt,  NULL, offsetof( BattlePlanUpdateModuleData, m_transitionIdleFrames ) },

		{ "BombardmentPlanUnpackSoundName",				INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_bombardmentUnpackName ) },
		{ "BombardmentPlanPackSoundName",					INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_bombardmentPackName ) },
		{ "BombardmentMessageLabel",							INI::parseAsciiString,					NULL,	offsetof( BattlePlanUpdateModuleData, m_bombardmentMessageLabel ) },
		{ "BombardmentAnnouncementName",					INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_bombardmentAnnouncementName ) },
		{ "SearchAndDestroyPlanUnpackSoundName",	INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_searchAndDestroyUnpackName ) },
		{ "SearchAndDestroyPlanIdleLoopSoundName",INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_searchAndDestroyIdleName ) },
		{ "SearchAndDestroyPlanPackSoundName",		INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_searchAndDestroyPackName ) },
		{ "SearchAndDestroyMessageLabel",					INI::parseAsciiString,					NULL,	offsetof( BattlePlanUpdateModuleData, m_searchAndDestroyMessageLabel ) },
		{ "SearchAndDestroyAnnouncementName",			INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_searchAndDestroyAnnouncementName ) },
		{ "HoldTheLinePlanUnpackSoundName",				INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_holdTheLineUnpackName ) },
		{ "HoldTheLinePlanPackSoundName",					INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_holdTheLinePackName ) },
		{ "HoldTheLineMessageLabel",							INI::parseAsciiString,					NULL,	offsetof( BattlePlanUpdateModuleData, m_holdTheLineMessageLabel ) },
		{ "HoldTheLineAnnouncementName",					INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_holdTheLineAnnouncementName ) },

		{ "ValidMemberKindOf",										KindOfMaskType::parseFromINI,								NULL, offsetof( BattlePlanUpdateModuleData, m_validMemberKindOf ) },
		{ "InvalidMemberKindOf",									KindOfMaskType::parseFromINI,								NULL, offsetof( BattlePlanUpdateModuleData, m_invalidMemberKindOf ) },
		{ "BattlePlanChangeParalyzeTime",					INI::parseDurationUnsignedInt,  NULL, offsetof( BattlePlanUpdateModuleData, m_battlePlanParalyzeFrames ) },
		{ "HoldTheLinePlanArmorDamageScalar",			INI::parseReal,									NULL, offsetof( BattlePlanUpdateModuleData, m_holdTheLineArmorDamageScalar ) },
		{ "SearchAndDestroyPlanSightRangeScalar",	INI::parseReal,									NULL, offsetof( BattlePlanUpdateModuleData, m_searchAndDestroySightRangeScalar ) },

		{ "StrategyCenterSearchAndDestroySightRangeScalar", INI::parseReal,				NULL, offsetof( BattlePlanUpdateModuleData, m_strategyCenterSearchAndDestroySightRangeScalar ) },
		{ "StrategyCenterSearchAndDestroyDetectsStealth",   INI::parseBool,				NULL, offsetof( BattlePlanUpdateModuleData, m_strategyCenterSearchAndDestroyDetectsStealth ) },
		{ "StrategyCenterHoldTheLineMaxHealthScalar",				INI::parseReal,				NULL, offsetof( BattlePlanUpdateModuleData, m_strategyCenterHoldTheLineMaxHealthScalar ) },
    { "StrategyCenterHoldTheLineMaxHealthChangeType",		INI::parseIndexList,  TheMaxHealthChangeTypeNames, offsetof( BattlePlanUpdateModuleData, m_strategyCenterHoldTheLineMaxHealthChangeType ) }, 

		{ "VisionObjectName",											INI::parseAsciiString,					NULL, offsetof( BattlePlanUpdateModuleData, m_visionObjectName ) },

		{ 0, 0, 0, 0 }
	};
	p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateCtorThunk.cpp
// ??0BattlePlanUpdate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
BattlePlanUpdate::BattlePlanUpdate( Thing *thing, const ModuleData* moduleData ) : 
	SpecialPowerUpdateModule( thing, moduleData ),
	m_bonuses(NULL)
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();

	m_status								= TRANSITIONSTATUS_IDLE;
	m_currentPlan						= PLANSTATUS_NONE;
	m_desiredPlan						= PLANSTATUS_NONE;
	m_planAffectingArmy			= PLANSTATUS_NONE;
	m_nextReadyFrame				= 0;
	m_invalidSettings				= false;
	m_centeringTurret				= false;

	//Default the bonuses to no change.
	m_bonuses = newInstance(BattlePlanBonuses);
	m_bonuses->m_armorScalar					= 1.0f;
	m_bonuses->m_sightRangeScalar		= 1.0f;
	m_bonuses->m_bombardment					= 0;
	m_bonuses->m_searchAndDestroy		= 0;
	m_bonuses->m_holdTheLine					= 0;
	m_bonuses->m_validKindOf					= data->m_validMemberKindOf;
	m_bonuses->m_invalidKindOf				= data->m_invalidMemberKindOf;

	m_visionObjectID = INVALID_ID;

	//------------------------//
	// Added by Sadullah Nader//
	//------------------------//

	m_specialPowerModule   = NULL;
	//
} 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
BattlePlanUpdate::~BattlePlanUpdate( void )
{
	TheAudio->removeAudioEvent( m_bombardmentUnpack.getPlayingHandle() );
	TheAudio->removeAudioEvent( m_bombardmentPack.getPlayingHandle() );
	TheAudio->removeAudioEvent( m_searchAndDestroyUnpack.getPlayingHandle() );
	TheAudio->removeAudioEvent( m_searchAndDestroyIdle.getPlayingHandle() );
	TheAudio->removeAudioEvent( m_searchAndDestroyPack.getPlayingHandle() );
	TheAudio->removeAudioEvent( m_holdTheLineUnpack.getPlayingHandle() );
	TheAudio->removeAudioEvent( m_holdTheLinePack.getPlayingHandle() );

}

// ------------------------------------------------------------------------------------------------
/** On delete */
// ------------------------------------------------------------------------------------------------
// ?onDelete@BattlePlanUpdate@@UAEXXZ present-unmatched
void BattlePlanUpdate::onDelete()
{

	// extend base class
	UpdateModule::onDelete();

	// delete our vision object, if it exists
	Object *obj;
	if( m_visionObjectID != INVALID_ID )
	{
		obj = TheGameLogic->findObjectByID( m_visionObjectID );
		if( obj )
			TheGameLogic->destroyObject( obj );
	}  // end if

	// If we get destroyed, then make sure we remove our bonus!
	// srj sez: we can't do this in the dtor because our team
	// (and thus controlling player) has already been nulled by then...
	Player* player = getObject()->getControllingPlayer();
	// however, player CAN legitimately be null during game reset cycles
	// (and which point it doesn't really matter if we can remove the bonus or not)
	//DEBUG_ASSERTCRASH(player != NULL, ("Hmm, controller is null"));
	if( player && m_planAffectingArmy != PLANSTATUS_NONE )
	{
		player->changeBattlePlan( m_planAffectingArmy, -1, m_bonuses );
	}

}

//-------------------------------------------------------------------------------------------------
// Validate that we have the necessary data from the ini file.
//-------------------------------------------------------------------------------------------------
// ?onObjectCreated@BattlePlanUpdate@@UAEXXZ present-unmatched
void BattlePlanUpdate::onObjectCreated()
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();
	Object *obj = getObject();

	if( !data->m_specialPowerTemplate )
	{
		DEBUG_CRASH( ("%s object's BattlePlanUpdate lacks access to the SpecialPowerTemplate. Needs to be specified in ini.", obj->getTemplate()->getName().str() ) );
		m_invalidSettings = true;
		return;
	}

	m_specialPowerModule = obj->getSpecialPowerModule( data->m_specialPowerTemplate );

	//Create instances of the sounds required.
	m_bombardmentUnpack.setEventName( data->m_bombardmentUnpackName );
	m_bombardmentPack.setEventName(	data->m_bombardmentPackName );
	m_bombardmentAnnouncement.setEventName( data->m_bombardmentAnnouncementName );
	m_searchAndDestroyUnpack.setEventName( data->m_searchAndDestroyUnpackName );
	m_searchAndDestroyIdle.setEventName( data->m_searchAndDestroyIdleName );
	m_searchAndDestroyPack.setEventName( data->m_searchAndDestroyPackName );
	m_searchAndDestroyAnnouncement.setEventName( data->m_searchAndDestroyAnnouncementName );
	m_holdTheLineUnpack.setEventName( data->m_holdTheLineUnpackName );
	m_holdTheLinePack.setEventName(	data->m_holdTheLinePackName );
	m_holdTheLineAnnouncement.setEventName( data->m_holdTheLineAnnouncementName );
	TheAudio->getInfoForAudioEvent( &m_bombardmentUnpack );
	TheAudio->getInfoForAudioEvent( &m_bombardmentPack );
	TheAudio->getInfoForAudioEvent( &m_bombardmentAnnouncement );
	TheAudio->getInfoForAudioEvent( &m_searchAndDestroyUnpack );
	TheAudio->getInfoForAudioEvent( &m_searchAndDestroyIdle );
	TheAudio->getInfoForAudioEvent( &m_searchAndDestroyPack );
	TheAudio->getInfoForAudioEvent( &m_searchAndDestroyAnnouncement );
	TheAudio->getInfoForAudioEvent( &m_holdTheLineUnpack );
	TheAudio->getInfoForAudioEvent( &m_holdTheLinePack );
	TheAudio->getInfoForAudioEvent( &m_holdTheLineAnnouncement );

	getObject()->setWeaponSetFlag( WEAPONSET_VETERAN );
	AIUpdateInterface *ai = obj->getAI();
	if( ai )
	{
		// lock it just till the weapon is empty or the attack is "done"
		obj->setWeaponLock( PRIMARY_WEAPON, LOCKED_TEMPORARILY );
	}
	enableTurret( false );
}

//-------------------------------------------------------------------------------------------------
// ?initiateIntentToDoSpecialPower@BattlePlanUpdate@@UAE_NPBVSpecialPowerTemplate@@PBVObject@@PBUCoord3D@@PBVWaypoint@@I@Z present-unmatched
Bool BattlePlanUpdate::initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate, const Object *targetObj, const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions )
{
	if( m_specialPowerModule->getSpecialPowerTemplate() != specialPowerTemplate )
	{
		//Check to make sure our modules are connected.
		return FALSE;
	}

	//Set the desired status based on the command button option!
	if( BitTest( commandOptions, OPTION_ONE ) )
	{
		m_desiredPlan = PLANSTATUS_BOMBARDMENT;
	}
	else if( BitTest( commandOptions, OPTION_TWO ) )
	{
		m_desiredPlan = PLANSTATUS_HOLDTHELINE;
	}
	else if( BitTest( commandOptions, OPTION_THREE ) )
	{
		m_desiredPlan = PLANSTATUS_SEARCHANDDESTROY;
	}
	else
	{
		DEBUG_CRASH( ("Selected an unsupported strategy for strategy center.") );
		return FALSE;
	}

	getObject()->getControllingPlayer()->getAcademyStats()->recordBattlePlanSelected();
	return TRUE;
}

// ?isPowerCurrentlyInUse@BattlePlanUpdate@@UBE_NPBVCommandButton@@@Z present-unmatched
Bool BattlePlanUpdate::isPowerCurrentlyInUse( const CommandButton *command ) const
{
	//@todo -- perhaps we may need this one day...
	return false;
}

//-------------------------------------------------------------------------------------------------
CommandOption BattlePlanUpdate::getCommandOption() const
{
	switch( m_desiredPlan )
	{
		case PLANSTATUS_BOMBARDMENT:
			return OPTION_ONE;
		case PLANSTATUS_HOLDTHELINE:
			return OPTION_TWO;
		case PLANSTATUS_SEARCHANDDESTROY:
			return OPTION_THREE;
	}
	return (CommandOption)0;
}

// ------------------------------------------------------------------------------------------------
/** Create vision objects for all players revealing this building to all */
// ------------------------------------------------------------------------------------------------
// Retail BFME exposes the one-argument factory ABI at the ILT used below;
// GeneralsMD's ThingFactory header adds a defaulted check parameter.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

typedef BitFlags<86> BattlePlanObjectStatusMaskType;
typedef Object *(ThingFactory::*BattlePlanNewObjectCall)(
	const ThingTemplate *, Team *, const volatile BattlePlanObjectStatusMaskType &, void *);
extern void j_0004494a();

static __forceinline Object *battlePlanNewObject( ThingFactory *factory,
	const ThingTemplate *thingTemplate, Team *team,
	const volatile BattlePlanObjectStatusMaskType &statusMask, void *extra )
{
	union { void (*raw)(); BattlePlanNewObjectCall member; } call;
	call.raw = j_0004494a;
	return (factory->*call.member)( thingTemplate, team, statusMask, extra );
}

struct BattlePlanCreateVisionDataRetailView
{
	unsigned char m_padding[ 0x9c ];
	AsciiString m_visionObjectName;
};

void BattlePlanUpdate::createVisionObject()
{
	struct BattlePlanCreateVisionObjectRetailView
	{
		unsigned char m_padding[ 0x744 ];
		ObjectID m_visionObjectID;
	};
	BattlePlanCreateVisionObjectRetailView *retail = reinterpret_cast<BattlePlanCreateVisionObjectRetailView *>( this );

	if (*reinterpret_cast<volatile ObjectID *>( reinterpret_cast<char *>( retail ) + 0x744 ) != INVALID_ID) // don't want two.
		return;

	const BattlePlanCreateVisionDataRetailView *retailData = reinterpret_cast<const BattlePlanCreateVisionDataRetailView *>(
		*reinterpret_cast<const BattlePlanUpdateModuleData *volatile *>( reinterpret_cast<char *>( this ) + 0x04 ) );
	Object *obj = *reinterpret_cast<Object *volatile *>( reinterpret_cast<char *>( this ) + 0x08 );

	// get template of object to create
	const ThingTemplate *tt = reinterpret_cast<BfmeThingFactory *>( TheThingFactory )->findTemplate(
		retailData->m_visionObjectName );
	DEBUG_ASSERTCRASH( tt, ("BattlePlanUpdate::setStatus - Invalid vision object name '%s'\n",
																												retailData->m_visionObjectName.str()) );

	if (!tt)
		return;

	Player *pPlayer = ThePlayerList->getNeutralPlayer();
	// sanity
	if(!pPlayer)
		return;

	Team *defaultTeam = *reinterpret_cast<Team **>( reinterpret_cast<char *>( pPlayer ) + 0x230 );
	Object *visionObject;
	BitFlags<86> statusMask;

	// create object for this player
	visionObject = battlePlanNewObject( TheThingFactory, tt, defaultTeam, statusMask, 0 );
	if( visionObject )
	{

		// record we have an object
		retail->m_visionObjectID = visionObject->getID();

		// set position
		visionObject->setPosition( obj->getPosition() );

		// set the shroud clearing range
		visionObject->setShroudClearingRange(
			*reinterpret_cast<const Real *>( reinterpret_cast<const char *>( obj ) + 0xc0 ) );

	}  // end if

}  // end createVisionObject

//-------------------------------------------------------------------------------------------------
// Byte-verified BFME body: BattlePlanUpdateSetStatus.cpp


//------------------------------------------------------------------------------------------------
void BattlePlanUpdate::enableTurret( Bool enable )
{
	Object *object = *(Object **)((char *)this + 0x08);
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)object + 0x204);
	if( ai )
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if( tur != TURRET_INVALID )
		{
			ai->setTurretEnabled( tur, enable );
		}
	}
}

//------------------------------------------------------------------------------------------------
// The Zero Hour body unchanged; two offsets are BFME's. The module's owning
// object is at module+0x08 -- the BFME_MODULE_NO_MPO layout, Module without its
// MemoryPoolObject base -- where this file's getObject() reads +0x0C, and the
// AI is at Object+0x204 where getAI() reads +0x19C. Switching the define on for
// this TU is not available: the members getActiveBattlePlan reads are pinned to
// the wider layout and stop matching, so both offsets are views.
struct BfmeRecenterTurretObject
{
	unsigned char m_unreconstructed_000[ 0x204 ];
	AIUpdateInterface *m_ai;				///< retail this+0x204
};

struct BfmeRecenterTurretModule
{
	unsigned char m_unreconstructed_000[ 8 ];
	BfmeRecenterTurretObject *m_object;			///< retail this+0x08
};

void BattlePlanUpdate::recenterTurret()
{
	AIUpdateInterface *ai = ((BfmeRecenterTurretModule *)this)->m_object->m_ai;
	if( ai )
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if( tur != TURRET_INVALID )
		{
			ai->recenterTurret( tur );
		}
	}
}

//------------------------------------------------------------------------------------------------
Bool BattlePlanUpdate::isTurretInNaturalPosition()
{
	#pragma pack(push, 1)
	struct RetailBattlePlanLayout {
		char padding[8];
		Object *object;
	};
	struct RetailObjectLayout {
		char padding[0x204];
		AIUpdateInterface *ai;
	};
	#pragma pack(pop)
	const RetailBattlePlanLayout *retail = reinterpret_cast<const RetailBattlePlanLayout *>(this);
	AIUpdateInterface *ai = reinterpret_cast<const RetailObjectLayout *>(retail->object)->ai;
	if( ai )
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if( tur != TURRET_INVALID )
		{
			return ai->isTurretInNaturalPosition( tur );
		}
	}
	return false;
}

//------------------------------------------------------------------------------------------------
Int paralyzeTroop( Object *obj, void *userData )
{
	const char *data = static_cast<const char *>( userData );
	if( obj->isAnyKindOf( *reinterpret_cast<const KindOfMaskType *>( data + 0x54 ) ) )
	{
		if( !obj->isAnyKindOf( *reinterpret_cast<const KindOfMaskType *>( data + 0x6c ) ) )
		{
			obj->setDisabledUntil( DISABLED_PARALYZED,
				TheGameLogic->getFrame() + *reinterpret_cast<const UnsignedInt *>( data + 0x50 ) );
		}
	}
	return true;
}

//------------------------------------------------------------------------------------------------
// ?setBattlePlan@BattlePlanUpdate@@IAEXW4BattlePlanStatus@@@Z
// Body in game/masm_dumps/setBattlePlan_BattlePlanUpdate_00285920_packet240.asm (exact 747B retail @ 0x00285920).
//------------------------------------------------------------------------------------------------
//Returns the currently active battle plan -- unpacked and ready... returns PLANSTATUS_NONE if in 
//transition!
//------------------------------------------------------------------------------------------------
BattlePlanStatus BattlePlanUpdate::getActiveBattlePlan() const
{
	if( m_status == TRANSITIONSTATUS_ACTIVE )
	{
		return m_planAffectingArmy;
	}
	return PLANSTATUS_NONE;
}

//------------------------------------------------------------------------------------------------
// ?crc@BattlePlanUpdate@@MAEXPAVXfer@@@Z present-unmatched
void BattlePlanUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

//------------------------------------------------------------------------------------------------
// Xfer method
//	Version Info:
//	1: Initial version
//------------------------------------------------------------------------------------------------
// ?xfer@BattlePlanUpdate@@MAEXPAVXfer@@@Z present-unmatched
void BattlePlanUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// current plan
	xfer->xferUser( &m_currentPlan, sizeof( BattlePlanStatus ) );

	// desired plan
	xfer->xferUser( &m_desiredPlan, sizeof( BattlePlanStatus ) );

	// plan affecting army
	xfer->xferUser( &m_planAffectingArmy, sizeof( BattlePlanStatus ) );

	// status
	xfer->xferUser( &m_status, sizeof( TransitionStatus ) );

	// next ready frame
	xfer->xferUnsignedInt( &m_nextReadyFrame );

	// don't need to save this interface, it's retrived on object creation
	// SpecialPowerModuleInterface *m_specialPowerModule;

	// invalid settings
	xfer->xferBool( &m_invalidSettings );

	// centering turret
	xfer->xferBool( &m_centeringTurret );

	// bonuses
	xfer->xferReal( &m_bonuses->m_armorScalar );
	xfer->xferInt( &m_bonuses->m_bombardment );
	xfer->xferInt( &m_bonuses->m_searchAndDestroy );
	xfer->xferInt( &m_bonuses->m_holdTheLine );
	xfer->xferReal( &m_bonuses->m_sightRangeScalar );
	m_bonuses->m_validKindOf.xfer( xfer );
	m_bonuses->m_invalidKindOf.xfer( xfer );

	// vision object data
	xfer->xferObjectID( &m_visionObjectID );

}  // end xfer

//------------------------------------------------------------------------------------------------
// ?loadPostProcess@BattlePlanUpdate@@MAEXXZ present-unmatched
void BattlePlanUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
