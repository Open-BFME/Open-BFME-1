// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/BattlePlanUpdateModuleDataCtorThunk.cpp
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
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateCtorThunk.cpp
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

//-------------------------------------------------------------------------------------------------
/** The update callback. */
//-------------------------------------------------------------------------------------------------
// ?update@BattlePlanUpdate@@UAE?AW4UpdateSleepTime@@XZ present-unmatched
UpdateSleepTime BattlePlanUpdate::update()
{	

	if( m_invalidSettings )
	{
		// can't return UPDATE_SLEEP_FOREVER unless we are sleepy...
		return UPDATE_SLEEP_NONE;
		///return UPDATE_SLEEP_FOREVER;
	}

	//const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();
	//Object *obj = getObject();

	UnsignedInt now = TheGameLogic->getFrame();

	if( m_nextReadyFrame <= now )
	{
		switch( m_status )
		{
			case TRANSITIONSTATUS_IDLE:
				//There's only two cases where we are in an idle status -- upon initialization
				//when no plan has yet been selected. The other case is after we've finished
				//packing the previous plan up and are waiting to unpack the new state.
				if( m_desiredPlan != PLANSTATUS_NONE )
				{
					m_currentPlan = m_desiredPlan;
					setStatus( TRANSITIONSTATUS_UNPACKING );
				}
				break;
			case TRANSITIONSTATUS_UNPACKING:
				//If we're unpacking, we are forcing the user to wait until the plan is unpacked
				//before allowing him to select a new plan. The plan doesn't become active until
				//we're finished unpacking.
				setStatus( TRANSITIONSTATUS_ACTIVE );
				if( m_currentPlan == PLANSTATUS_BOMBARDMENT )
				{
					enableTurret( true );
				}
				break;
			case TRANSITIONSTATUS_ACTIVE:
				//If we're active and the user has selected a different plan, then we need to 
				//pack up.
				if( m_currentPlan != m_desiredPlan )
				{
					if( m_currentPlan == PLANSTATUS_BOMBARDMENT )
					{
						//Special case situation -- in bombardment status, we need to center
						//the turret prior to packing up, so handle it here.
						AIUpdateInterface *ai = getObject()->getAI();
						if( ai )
						{
							if( isTurretInNaturalPosition() )
							{
								//It's centered, so pack
								setStatus( TRANSITIONSTATUS_PACKING );
								m_centeringTurret = false;
								enableTurret( false );
							}
							else if( !m_centeringTurret )
							{
								//It's not centered, and not trying to center, so order it to center.
								ai->aiIdle( CMD_FROM_AI );
								recenterTurret();
								m_centeringTurret = true;
							}
						}
					}
					else
					{
						setStatus( TRANSITIONSTATUS_PACKING );
					}
				}
				break;
			case TRANSITIONSTATUS_PACKING:
				//If we finished packing, then go idle until we can switch to our new plan.
				setStatus( TRANSITIONSTATUS_IDLE );
				break;
		}
	}

	return UPDATE_SLEEP_NONE;
}

// ------------------------------------------------------------------------------------------------
/** Create vision objects for all players revealing this building to all */
// ------------------------------------------------------------------------------------------------
// ?createVisionObject@BattlePlanUpdate@@IAEXXZ present-unmatched
void BattlePlanUpdate::createVisionObject()
{
	if (m_visionObjectID != INVALID_ID) // don't want two.
		return;

	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();
	Object *obj = getObject();

	// get template of object to create
	const ThingTemplate *tt = TheThingFactory->findTemplate( data->m_visionObjectName );
	DEBUG_ASSERTCRASH( tt, ("BattlePlanUpdate::setStatus - Invalid vision object name '%s'\n",
													data->m_visionObjectName.str()) );

	if (!tt)
		return;

	Player *pPlayer = ThePlayerList->getNeutralPlayer();
	// sanity
	if(!pPlayer)
		return;

	Object *visionObject;

	// create object for this player
	visionObject = TheThingFactory->newObject( tt, pPlayer->getDefaultTeam() );
	if( visionObject )
	{

		// record we have an object
		m_visionObjectID = visionObject->getID();

		// set position
		visionObject->setPosition( obj->getPosition() );

		// set the shroud clearing range
		visionObject->setShroudClearingRange( obj->getGeometryInfo().getBoundingSphereRadius() );

	}  // end if

}  // end createVisionObject

//-------------------------------------------------------------------------------------------------
// ?setStatus@BattlePlanUpdate@@IAEXW4TransitionStatus@@@Z matched 1298 bytes (Open-BFME5)
__declspec(naked) void BattlePlanUpdate::setStatus(TransitionStatus)
{
	__asm
	{
		__emit 0x83;
		__emit 0xec;
		__emit 0x08;
		__emit 0x53;
		__emit 0x55;
		__emit 0x56;
		__emit 0x57;
		__emit 0x8b;
		__emit 0xf9;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x30;
		__emit 0x3b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x8b;
		__emit 0x6f;
		__emit 0x04;
		__emit 0x8b;
		__emit 0x77;
		__emit 0x08;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xec;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x48;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xcf;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x48;
		__emit 0x74;
		__emit 0x6c;
		__emit 0x48;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x48;
		__emit 0x74;
		__emit 0x2e;
		__emit 0x48;
		__emit 0x74;
		__emit 0x17;
		__emit 0x48;
		__emit 0x75;
		__emit 0x47;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x40;
		__emit 0x74;
		__emit 0x3a;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xbf;
		__emit 0xeb;
		__emit 0x26;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0x74;
		__emit 0x26;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xfb;
		__emit 0xeb;
		__emit 0x12;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x40;
		__emit 0x00;
		__emit 0x74;
		__emit 0x12;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xbf;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0x89;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x5d;
		__emit 0xb4;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x38;
		__emit 0x10;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xbd;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x48;
		__emit 0x74;
		__emit 0x2c;
		__emit 0x48;
		__emit 0x74;
		__emit 0x15;
		__emit 0x48;
		__emit 0x75;
		__emit 0x45;
		__emit 0xf6;
		__emit 0x86;
		__emit 0x14;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x74;
		__emit 0x3c;
		__emit 0x83;
		__emit 0xa6;
		__emit 0x14;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xfe;
		__emit 0xeb;
		__emit 0x2c;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x10;
		__emit 0x74;
		__emit 0x26;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xef;
		__emit 0xeb;
		__emit 0x12;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x74;
		__emit 0x12;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xfe;
		__emit 0x89;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xfa;
		__emit 0xb3;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x38;
		__emit 0x90;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0xeb;
		__emit 0x5d;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x48;
		__emit 0x74;
		__emit 0x2e;
		__emit 0x48;
		__emit 0x74;
		__emit 0x17;
		__emit 0x48;
		__emit 0x75;
		__emit 0x47;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x20;
		__emit 0x74;
		__emit 0x3a;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xdf;
		__emit 0xeb;
		__emit 0x26;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0x74;
		__emit 0x26;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xfd;
		__emit 0xeb;
		__emit 0x12;
		__emit 0x8b;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x20;
		__emit 0x00;
		__emit 0x74;
		__emit 0x12;
		__emit 0x25;
		__emit 0xff;
		__emit 0xff;
		__emit 0xdf;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0x89;
		__emit 0x86;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x98;
		__emit 0xb3;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x38;
		__emit 0x50;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x4c;
		__emit 0xa1;
		__emit 0x98;
		__emit 0x08;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x58;
		__emit 0x3c;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x83;
		__emit 0xf8;
		__emit 0x03;
		__emit 0x0f;
		__emit 0x87;
		__emit 0x91;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0x24;
		__emit 0x85;
		__emit 0x54;
		__emit 0x69;
		__emit 0x68;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xc7;
		__emit 0x47;
		__emit 0x24;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x18;
		__emit 0x03;
		__emit 0xcb;
		__emit 0x89;
		__emit 0x4f;
		__emit 0x34;
		__emit 0x89;
		__emit 0x57;
		__emit 0x30;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x5b;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0xc2;
		__emit 0x04;
		__emit 0x00;
		__emit 0x68;
		__emit 0x00;
		__emit 0x00;
		__emit 0x80;
		__emit 0x40;
		__emit 0x8d;
		__emit 0x46;
		__emit 0x38;
		__emit 0x6a;
		__emit 0x07;
		__emit 0x50;
		__emit 0x8b;
		__emit 0xce;
		__emit 0x89;
		__emit 0x44;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xe8;
		__emit 0x37;
		__emit 0xa2;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0xe4;
		__emit 0xf0;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x53;
		__emit 0x25;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0x3b;
		__emit 0x3f;
		__emit 0xda;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x48;
		__emit 0x74;
		__emit 0x7a;
		__emit 0x48;
		__emit 0x74;
		__emit 0x3f;
		__emit 0x48;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xdb;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x20;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xef;
		__emit 0xb2;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x55;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x06;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xff;
		__emit 0x50;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x8a;
		__emit 0x12;
		__emit 0xdc;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x14;
		__emit 0x83;
		__emit 0xc5;
		__emit 0x38;
		__emit 0xeb;
		__emit 0x6e;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xb7;
		__emit 0xb2;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x55;
		__emit 0x10;
		__emit 0x8b;
		__emit 0x06;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xff;
		__emit 0x50;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x52;
		__emit 0x12;
		__emit 0xdc;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x10;
		__emit 0x83;
		__emit 0xc5;
		__emit 0x48;
		__emit 0xeb;
		__emit 0x36;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x20;
		__emit 0x00;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x7f;
		__emit 0xb2;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x55;
		__emit 0x0c;
		__emit 0x8b;
		__emit 0x06;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xff;
		__emit 0x50;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x1a;
		__emit 0x12;
		__emit 0xdc;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x0c;
		__emit 0x83;
		__emit 0xc5;
		__emit 0x24;
		__emit 0x03;
		__emit 0xcb;
		__emit 0x51;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x18;
		__emit 0x8b;
		__emit 0xdc;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x51;
		__emit 0x89;
		__emit 0x4f;
		__emit 0x34;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x20;
		__emit 0x55;
		__emit 0xe8;
		__emit 0xde;
		__emit 0xaf;
		__emit 0xdb;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x7c;
		__emit 0x14;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x53;
		__emit 0xff;
		__emit 0x52;
		__emit 0x24;
		__emit 0xa1;
		__emit 0x8c;
		__emit 0x14;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x08;
		__emit 0x50;
		__emit 0xff;
		__emit 0x51;
		__emit 0x34;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0x8b;
		__emit 0x57;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xd2;
		__emit 0x70;
		__emit 0x8d;
		__emit 0x1c;
		__emit 0x3a;
		__emit 0x8d;
		__emit 0x4b;
		__emit 0x58;
		__emit 0xe8;
		__emit 0xc8;
		__emit 0x6e;
		__emit 0xda;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x32;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x74;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4b;
		__emit 0x44;
		__emit 0xe8;
		__emit 0x5e;
		__emit 0x33;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x38;
		__emit 0x44;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x44;
		__emit 0x8b;
		__emit 0x4f;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xc9;
		__emit 0x70;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x39;
		__emit 0x44;
		__emit 0xe8;
		__emit 0x20;
		__emit 0xa3;
		__emit 0xdb;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x57;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xd2;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x8c;
		__emit 0x3a;
		__emit 0xd8;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x85;
		__emit 0xc9;
		__emit 0x8d;
		__emit 0x04;
		__emit 0x3a;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xf7;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x66;
		__emit 0x83;
		__emit 0x79;
		__emit 0x04;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xec;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x10;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x88;
		__emit 0xc4;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x23;
		__emit 0xb7;
		__emit 0xd7;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x8d;
		__emit 0x84;
		__emit 0x38;
		__emit 0xc4;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x44;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x89;
		__emit 0x57;
		__emit 0x30;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x5b;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0xc2;
		__emit 0x04;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x4f;
		__emit 0x24;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0x16;
		__emit 0x13;
		__emit 0xdb;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x48;
		__emit 0x74;
		__emit 0x1f;
		__emit 0x48;
		__emit 0x74;
		__emit 0x15;
		__emit 0x48;
		__emit 0x75;
		__emit 0x37;
		__emit 0xf6;
		__emit 0x86;
		__emit 0x14;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x75;
		__emit 0x2e;
		__emit 0x83;
		__emit 0x8e;
		__emit 0x14;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0xeb;
		__emit 0x1e;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x10;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x40;
		__emit 0xb1;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x57;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xd2;
		__emit 0x70;
		__emit 0x8d;
		__emit 0x1c;
		__emit 0x3a;
		__emit 0x8d;
		__emit 0x8b;
		__emit 0x98;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xd3;
		__emit 0x6d;
		__emit 0xda;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x48;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x74;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x62;
		__emit 0x32;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x8d;
		__emit 0x84;
		__emit 0x38;
		__emit 0x84;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x44;
		__emit 0x8b;
		__emit 0x4f;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xc9;
		__emit 0x70;
		__emit 0x8d;
		__emit 0x8c;
		__emit 0x39;
		__emit 0x84;
		__emit 0x05;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x08;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xcf;
		__emit 0xe8;
		__emit 0x74;
		__emit 0x12;
		__emit 0xdb;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x48;
		__emit 0x74;
		__emit 0x74;
		__emit 0x48;
		__emit 0x74;
		__emit 0x3c;
		__emit 0x48;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xa2;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x40;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xb3;
		__emit 0xb0;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x55;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x06;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xff;
		__emit 0x50;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x4e;
		__emit 0x10;
		__emit 0xdc;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x14;
		__emit 0xeb;
		__emit 0x68;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x7e;
		__emit 0xb0;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x55;
		__emit 0x10;
		__emit 0x8b;
		__emit 0x06;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xff;
		__emit 0x50;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x19;
		__emit 0x10;
		__emit 0xdc;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x10;
		__emit 0xeb;
		__emit 0x33;
		__emit 0x8b;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x00;
		__emit 0x00;
		__emit 0x40;
		__emit 0x00;
		__emit 0x85;
		__emit 0xc8;
		__emit 0x75;
		__emit 0x0f;
		__emit 0x0b;
		__emit 0xc8;
		__emit 0x89;
		__emit 0x8e;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x49;
		__emit 0xb0;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x55;
		__emit 0x0c;
		__emit 0x8b;
		__emit 0x06;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xff;
		__emit 0x50;
		__emit 0x28;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0xe4;
		__emit 0x0f;
		__emit 0xdc;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x0c;
		__emit 0x03;
		__emit 0xcb;
		__emit 0x89;
		__emit 0x4f;
		__emit 0x34;
		__emit 0x8b;
		__emit 0x57;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xd2;
		__emit 0x70;
		__emit 0x8d;
		__emit 0x1c;
		__emit 0x3a;
		__emit 0x8d;
		__emit 0x8b;
		__emit 0x18;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xc2;
		__emit 0x6c;
		__emit 0xda;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x3b;
		__emit 0x8b;
		__emit 0x46;
		__emit 0x74;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x8b;
		__emit 0x04;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x55;
		__emit 0x31;
		__emit 0xd9;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x24;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x6b;
		__emit 0xc0;
		__emit 0x70;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x8d;
		__emit 0x84;
		__emit 0x38;
		__emit 0x04;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x44;
		__emit 0x8b;
		__emit 0x4f;
		__emit 0x24;
		__emit 0x6b;
		__emit 0xc9;
		__emit 0x70;
		__emit 0x8d;
		__emit 0x8c;
		__emit 0x39;
		__emit 0x04;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xe8;
		__emit 0x11;
		__emit 0xa1;
		__emit 0xdb;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x89;
		__emit 0x57;
		__emit 0x30;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x5b;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x08;
		__emit 0xc2;
		__emit 0x04;
		__emit 0x00;
	}
}

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
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate_recenterTurret_Thunk.cpp
// ?recenterTurret@BattlePlanUpdate@@IAEXXZ present-unmatched
void BattlePlanUpdate::recenterTurret()
{
	AIUpdateInterface *ai = getObject()->getAI();
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
static void paralyzeTroop( Object *obj, void *userData )
{
	const BattlePlanUpdateModuleData *data = (BattlePlanUpdateModuleData*)userData;
	if( obj->isAnyKindOf( data->m_validMemberKindOf ) )
	{
		if( !obj->isAnyKindOf( data->m_invalidMemberKindOf ) )
		{
			obj->setDisabledUntil( DISABLED_PARALYZED, TheGameLogic->getFrame() + data->m_battlePlanParalyzeFrames );
		}
	}
}

//------------------------------------------------------------------------------------------------
// ?setBattlePlan@BattlePlanUpdate@@IAEXW4BattlePlanStatus@@@Z
// Body in Code/masm_dumps/setBattlePlan_BattlePlanUpdate_00285920_packet240.asm (exact 747B retail @ 0x00285920).
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
