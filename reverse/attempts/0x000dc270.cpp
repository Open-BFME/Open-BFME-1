// ?xfer@Player@@MAEXPAVXfer@@@Z
// partial score=0.4 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// FILE: Player.cpp /////////////////////////////////////////////////////////
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
// File name: Player.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_SCIENCE_AVAILABILITY_NAMES

#include "Common/ActionManager.h"
#include "Common/BuildAssistant.h"
#include "Common/CRCDebug.h"
#include "Common/DisabledTypes.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/Radar.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/TunnelTracker.h"
#include "Common/Upgrade.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "Common/BitFlagsIO.h"
#include "Common/SpecialPower.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/AISkirmishPlayer.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/Squad.h"
#include "GameLogic/RankInfo.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/VictoryConditions.h"

#include "GameNetwork/GameInfo.h"

struct BfmeBattlePlanBonuses
{
	UnsignedByte m_unreconstructed_00[0x14];
	KindOfMaskType m_validKindOf;				///< retail this+0x14
	UnsignedByte m_unreconstructed_24[0x2C - 0x24];
	KindOfMaskType m_invalidKindOf;				///< retail this+0x2c
};

struct BfmePlayerBattlePlanField
{
	UnsignedByte m_unreconstructed_00[0x70];
	BfmeBattlePlanBonuses *m_battlePlanBonuses;		///< retail this+0x70
};

/** Xfer Method
	* Version Info:
	* 1: Initial version
	* 2: Player can now have a modifier on his skill points (multiplicative)
	* 3: Player can be excluded from the score screen via script.
	* 4: Player stores a list of specialpowerreadyframe timers, used by specialpowermodules abroad
	* 5: ??? (Profit)
	* 6: Store m_unitsShouldHunt, set to true after the script "Tell player to hunt" is called.
	* 7: added Preorder flag
	* 8: Save m_disabledSciences & m_hiddenSciences. jba.
	*/
// BFME's Xfer interface predates the Zero Hour header used by this TU.  The
// recovered Player body uses the retail slots directly, so keep this view local.
struct BfmePlayerXferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

extern void __cdecl xferBlob_0010CC40( Xfer *xfer, void *field );
extern "C" void __cdecl bfmeXferThreeBA( Xfer *xfer, void *value );

class BfmePlayerXfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual Bool slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser( void *data, UnsignedInt size );
	virtual void xferVersion( BfmePlayerXferVersion *version );
	virtual void slot11();
	virtual void xferSnapshot( void *snapshot );
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void xferUnicodeString( UnicodeString *value );
	virtual void xferAsciiString( AsciiString *value );
	virtual void xferReal( Real *value );
	virtual void slot28();
	virtual void xferUnsignedInt( UnsignedInt *value );
	virtual void xferInt( Int *value );
	virtual void xferUnsignedShort( UnsignedShort *value );
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool( Bool *value );
	void xferUpgradeMask( UpgradeMaskType *value )
	{
		xferBlob_0010CC40( reinterpret_cast<Xfer *>(this), value );
	}
	void xferScienceVec( ScienceVec *value )
	{
		bfmeXferThreeBA( reinterpret_cast<Xfer *>(this), value );
	}
};

// ------------------------------------------------------------------------------------------------
// ?xfer@Player@@MAEXPAVXfer@@@Z present-unmatched
void Player::xfer( Xfer *baseXfer )
{
	BfmePlayerXfer *xfer = reinterpret_cast<BfmePlayerXfer *>(baseXfer);
	Bool fullXfer = !xfer->isLightCRC();

	// version
	BfmePlayerXferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 4;
	xfer->xferVersion( &version );
	if (xfer->slot03())
		xfer->xferBool( reinterpret_cast<Bool *>(reinterpret_cast<char *>(this) + 0x29e) );
	Int zero = 0;
	UnsignedShort upgradeCount;
	Upgrade *upgrade = NULL;
	if (fullXfer)
	{
		char *const self = reinterpret_cast<char *>(this);
		Money &m_money = *reinterpret_cast<Money *>(self + 0x30);
		Upgrade *&m_upgradeList = *reinterpret_cast<Upgrade **>(self + 0x54);
		Bool &m_bfmeField681 = *reinterpret_cast<Bool *>(self + 0x681);
		UpgradeMaskType &m_upgradesInProgress = *reinterpret_cast<UpgradeMaskType *>(self + 0x74);
		UpgradeMaskType &m_upgradesCompleted = *reinterpret_cast<UpgradeMaskType *>(self + 0x8c);
		Energy &m_energy = *reinterpret_cast<Energy *>(self + 0xa4);
		BuildListInfo *&m_pBuildList = *reinterpret_cast<BuildListInfo **>(self + 0x1c0);
		AIPlayer *&m_ai = *reinterpret_cast<AIPlayer **>(self + 0x220);
		ResourceGatheringManager *&m_resourceGatheringManager = *reinterpret_cast<ResourceGatheringManager **>(self + 0x228);
		TunnelTracker *&m_tunnelSystem = *reinterpret_cast<TunnelTracker **>(self + 0x22c);
		Team *&m_defaultTeam = *reinterpret_cast<Team **>(self + 0x230);
		ScienceVec &m_sciences = *reinterpret_cast<ScienceVec *>(self + 0x234);
		Int &m_rankLevel = *reinterpret_cast<Int *>(self + 0x258);
		Real &m_skillPointsModifier = *reinterpret_cast<Real *>(self + 0x25c);
		Int &m_skillPoints = *reinterpret_cast<Int *>(self + 0x6a0);
		Int &m_sciencePurchasePoints = *reinterpret_cast<Int *>(self + 0x264);
		Int &m_levelUp = *reinterpret_cast<Int *>(self + 0x268);
		Int &m_levelDown = *reinterpret_cast<Int *>(self + 0x26c);
		UnicodeString &m_generalName = *reinterpret_cast<UnicodeString *>(self + 0x270);
		PlayerRelationMap *&m_playerRelations = *reinterpret_cast<PlayerRelationMap **>(self + 0x28c);
		TeamRelationMap *&m_teamRelations = *reinterpret_cast<TeamRelationMap **>(self + 0x290);
		Bool &m_canBuildUnits = *reinterpret_cast<Bool *>(self + 0x294);
		Bool &m_canBuildBase = *reinterpret_cast<Bool *>(self + 0x295);
		Bool &m_observer = *reinterpret_cast<Bool *>(self + 0x296);
		Real &m_cashBountyPercent = *reinterpret_cast<Real *>(self + 0x298);
		Bool &m_listInScoreScreen = *reinterpret_cast<Bool *>(self + 0x29c);
		Bool *m_attackedBy = reinterpret_cast<Bool *>(self + 0x29f);
		ScoreKeeper &m_scoreKeeper = *reinterpret_cast<ScoreKeeper *>(self + 0x348);
		SpecialPowerReadyTimerList &m_specialPowerReadyTimerList = *reinterpret_cast<SpecialPowerReadyTimerList *>(self + 0x640);

	// money
	xfer->xferSnapshot( &m_money );

	// upgrade list count
	upgradeCount = (UnsignedShort)zero;
	for( upgrade = m_upgradeList; upgrade; upgrade = *reinterpret_cast<Upgrade **>(reinterpret_cast<char *>(upgrade) + 0xc) )
		upgradeCount++;
	xfer->xferUnsignedShort( &upgradeCount );

	// preorder info
	xfer->xferBool( reinterpret_cast<Bool *>(self + 0x297) );

	if (xfer->isLoading())
	{
		reinterpret_cast<ScienceVec *>(self + 0x240)->clear();
		reinterpret_cast<ScienceVec *>(self + 0x24c)->clear();
	}
	xfer->xferScienceVec(reinterpret_cast<ScienceVec *>(self + 0x240));
	xfer->xferScienceVec(reinterpret_cast<ScienceVec *>(self + 0x24c));

	// xfer upgrade instances
	UnicodeString upgradeName;
	if( xfer->isSaving() )
	{

		for( upgrade = m_upgradeList; upgrade; upgrade = *reinterpret_cast<Upgrade **>(reinterpret_cast<char *>(upgrade) + 0xc) )
		{

			// write upgrade name
			UpgradeTemplate *upgradeTemplate = *reinterpret_cast<UpgradeTemplate **>(reinterpret_cast<char *>(upgrade) + 4);
			upgradeName.set( *reinterpret_cast<UnicodeString *>(reinterpret_cast<char *>(upgradeTemplate) + 8) );
			xfer->xferAsciiString( reinterpret_cast<AsciiString *>( &upgradeName ) );

			// xfer upgrade data
			xfer->xferSnapshot( upgrade );

		}  // end for, upgrade

	}  // end if, save
	else
	{
		const UpgradeTemplate *upgradeTemplate;

		for( UnsignedShort i = 0; i < upgradeCount; ++i )
		{

			// read name
			xfer->xferAsciiString( reinterpret_cast<AsciiString *>( &upgradeName ) );

			// find template for this upgrade
			upgradeTemplate = TheUpgradeCenter->findUpgrade( reinterpret_cast<const AsciiString &>( upgradeName ) );
			
			// sanity
			if( upgradeTemplate == NULL )
			{

				DEBUG_CRASH(( "Player::xfer - Unable to find upgrade '%s'\n", reinterpret_cast<const AsciiString &>( upgradeName ).str() ));
				throw SC_INVALID_DATA;

			}  // end if

			// add upgrade to player, the status is invalid, but that's OK cause we're about to xfer it
			upgrade = addUpgrade( upgradeTemplate, UPGRADE_STATUS_INVALID );

			// xfer upgrade data
			xfer->xferSnapshot( upgrade );
						
		}  // end for, i

	}  // end else, load

	// radar info
	xfer->xferInt( reinterpret_cast<Int *>(self + 0x58) );
	xfer->xferBool( reinterpret_cast<Bool *>(self + 0x680) );
	xfer->xferInt( reinterpret_cast<Int *>(self + 0x5c) );
	xfer->xferBool( reinterpret_cast<Bool *>(self + 0x60) );

	// upgrades in progress
	xfer->xferUpgradeMask( &m_upgradesInProgress );

	// upgrades complete
	xfer->xferUpgradeMask( &m_upgradesCompleted );

	// energy info
	xfer->xferSnapshot( &m_energy );

	//
	// team prototypes ... this is only the fact that team prototypes are on this player
	// it is not the team prototype data itself
	//
	PlayerTeamList *teamPrototypes = reinterpret_cast<PlayerTeamList *>(self + 0x288);
	UnsignedShort prototypeCount = teamPrototypes->size();
	xfer->xferUnsignedShort( &prototypeCount );
	TeamPrototypeID prototypeID;
	TeamPrototype *prototype;
	if( xfer->isSaving() )
	{

		PlayerTeamList::iterator it;
		for( it = teamPrototypes->begin(); it != teamPrototypes->end(); ++it )
		{

			prototype = *it;
			prototypeID = prototype->getID();
			xfer->xferUnsignedInt( reinterpret_cast<UnsignedInt *>( &prototypeID ) );

		}  // end for

	}  // end if, save
	else
	{

		// empty the list right now
		teamPrototypes->clear();

		// read all the data
		for( UnsignedShort i = 0; i < prototypeCount; ++i )
		{

			// read id
			xfer->xferUnsignedInt( reinterpret_cast<UnsignedInt *>( &prototypeID ) );

			// find prototype
			prototype = TheTeamFactory->findTeamPrototypeByID( prototypeID );

			// sanity
			if( prototype == NULL )
			{

				DEBUG_CRASH(( "Player::xfer - Unable to find team prototype by id\n" ));
				throw SC_INVALID_DATA;

			}  // end if

			// put in list
			teamPrototypes->push_back( prototype );

		}  // end for, i

	}  // end else, load

	// build list info
	UnsignedShort buildListInfoCount = 0;
	BuildListInfo *buildListInfo;
	for( buildListInfo = m_pBuildList; buildListInfo; buildListInfo = buildListInfo->getNext() )
		buildListInfoCount++;
	xfer->xferUnsignedShort( &buildListInfoCount );
	if( xfer->isSaving() )
	{

		// xfer each build list info
		for( buildListInfo = m_pBuildList; buildListInfo; buildListInfo = buildListInfo->getNext() )
			xfer->xferSnapshot( buildListInfo );

	}  // end if, save
	else
	{

		//
		// destroy any build list that we got from loading the bare bones map, note that deleting
		// the head of these structures automatically deletes any links attached
		//
		if( m_pBuildList)
			m_pBuildList->deleteInstance();
		m_pBuildList = NULL;

		// read each build list info
		for( UnsignedShort i = 0; i < buildListInfoCount; ++i )
		{

			// allocate new build list
			buildListInfo = newInstance( BuildListInfo );	
			buildListInfo->setNextBuildList( NULL );

			// attach to the *end* of the list in the player
			if( m_pBuildList == NULL )
				m_pBuildList = buildListInfo;
			else
			{
				BuildListInfo *last = m_pBuildList;

				while( last->getNext() != NULL )
					last = last->getNext();

				last->setNextBuildList( buildListInfo );

			}  // end else

			// xfer data
			xfer->xferSnapshot( buildListInfo );

		}  // end for,i

	}  // end else, load

	// ai player data
	Bool aiPlayerPresent = m_ai ? TRUE : FALSE;
	xfer->xferBool( &aiPlayerPresent );
	if( (aiPlayerPresent == TRUE && m_ai == NULL) || (aiPlayerPresent == FALSE && m_ai != NULL) )
	{

		DEBUG_CRASH(( "Player::xfer - m_ai present/missing mismatch\n" ));
		throw SC_INVALID_DATA;;

	}  // end if
	if( m_ai )
		xfer->xferSnapshot( m_ai );

	// resource gathering manager
	Bool resourceGatheringManagerPresent = m_resourceGatheringManager ? TRUE : FALSE;
	xfer->xferBool( &resourceGatheringManagerPresent );
	if( (resourceGatheringManagerPresent == TRUE && m_resourceGatheringManager == NULL) ||	
			(resourceGatheringManagerPresent == FALSE && m_resourceGatheringManager != NULL ) )
	{

		DEBUG_CRASH(( "Player::xfer - m_resourceGatheringManager present/missing mismatch\n" ));
		throw SC_INVALID_DATA;

	}  // end if
	if( m_resourceGatheringManager )
		xfer->xferSnapshot( m_resourceGatheringManager );

	// tunnel tracking system
	Bool tunnelTrackerPresent = m_tunnelSystem ? TRUE : FALSE;
	xfer->xferBool( &tunnelTrackerPresent );
	if( (tunnelTrackerPresent == TRUE && m_tunnelSystem == NULL) ||
			(tunnelTrackerPresent == FALSE && m_tunnelSystem != NULL) )
	{

		DEBUG_CRASH(( "Player::xfer - m_tunnelSystem present/missing mismatch\n" ));
		throw SC_INVALID_DATA;

	}  // end if
	if( m_tunnelSystem )
		xfer->xferSnapshot( m_tunnelSystem );

	// default team
	TeamID teamID = m_defaultTeam ? m_defaultTeam->getID() : TEAM_ID_INVALID;
	xfer->xferUnsignedInt( reinterpret_cast<UnsignedInt *>( &teamID ) );
	if( xfer->isLoading() )
		m_defaultTeam = TheTeamFactory->findTeamByID( teamID );

	// sciences
	if( xfer->isLoading() )
		m_sciences.clear();
	xfer->xferScienceVec(&m_sciences);

	// rank level
	xfer->xferInt( &m_rankLevel );

	// skill points and their modifier
	if (version.m_version >= 3)
	{
		xfer->xferReal( &m_skillPointsModifier );
		xfer->xferInt( &m_skillPoints );
	}
	else
	{
		Int oldSkillPoints = 0;
		xfer->xferInt( &oldSkillPoints );
		m_skillPointsModifier = (Real)oldSkillPoints;
		xfer->xferInt( &m_skillPoints );
	}

	// science purchase points
	xfer->xferInt( &m_sciencePurchasePoints );

	// level up
	xfer->xferInt( &m_levelUp );

	// level down
	xfer->xferInt( &m_levelDown );

	// general name
	xfer->xferUnicodeString( &m_generalName );

	// player relations
	xfer->xferSnapshot( m_playerRelations );

	// team relations
	xfer->xferSnapshot( m_teamRelations );

	// can build units
	xfer->xferBool( &m_canBuildUnits );

	// BFME's defeated flag is adjacent to the can-build flags.
	xfer->xferBool( &m_bfmeField681 );

	// can build base
	xfer->xferBool( &m_canBuildBase );

	// observer
	xfer->xferBool( &m_observer );

	// cash bounty percent
	xfer->xferReal( &m_cashBountyPercent );

	xfer->xferBool( &m_listInScoreScreen );
	// attacked by
	Int *m_playerScore = reinterpret_cast<Int *>(self + 0x2c4);
	for (Int i = 0; i < 0x20; ++i)
	{
		xfer->xferBool( &m_attackedBy[i] );
		xfer->xferInt( &m_playerScore[i] );
	}

	xfer->xferUnsignedShort( reinterpret_cast<UnsignedShort *>(self + 0x344) );

	// score keeper
	xfer->xferSnapshot( &m_scoreKeeper );

	///////////////////////////////////////////////////////////////////////////
	if ( version.m_version < 2 )
	{
		 m_specialPowerReadyTimerList.clear();
	}
	else
	{
		UnsignedShort timerListSize = m_specialPowerReadyTimerList.size();
		xfer->xferUnsignedShort( &timerListSize );// HANDY LITTLE SHORT TO SIZE MY LIST
		if( xfer->isSaving() )
		{

			SpecialPowerReadyTimerType *timer;
			SpecialPowerReadyTimerListIterator it;
			for( it = m_specialPowerReadyTimerList.begin(); it != m_specialPowerReadyTimerList.end(); ++it )
			{
				timer = &(*it);
				xfer->xferUnsignedInt( &timer->m_templateID );
				xfer->xferUnsignedInt( &timer->m_readyFrame );
			}
		}
		else
		{
			if( m_specialPowerReadyTimerList.size() != 0 ) // sanity, list must be empty right now
			{
				DEBUG_CRASH(( "Player::xfer - m_specialPowerReadyTimerList should be empty but is not\n" ));
				throw SC_INVALID_DATA;
			}  // end if

			// read each entry
			for( UnsignedInt i = 0; i < timerListSize; ++i )
			{
				SpecialPowerReadyTimerType timer;	

				// read data
				xfer->xferUnsignedInt( &timer.m_templateID );
				xfer->xferUnsignedInt( &timer.m_readyFrame );

				// put at end of list
				m_specialPowerReadyTimerList.push_back( timer );

			}  // end for i
		}
	}
	///////////////////////////////////////////////////////////////////////////




	// squads
	Squad **squads = reinterpret_cast<Squad **>(self + 0x654);
	UnsignedShort squadCount = NUM_HOTKEY_SQUADS;
	xfer->xferUnsignedShort( &squadCount );
	if( squadCount != NUM_HOTKEY_SQUADS )
	{

		DEBUG_CRASH(( "Player::xfer - size of m_squadCount array has changed\n" ));
		throw SC_INVALID_DATA;

	}  // end if
	for( UnsignedShort i = 0; i < squadCount; ++i )
	{

		if( squads[ i ] == NULL )
		{

			DEBUG_CRASH(( "Player::xfer - NULL squad at index '%d'\n", i ));
			throw SC_INVALID_DATA;

		}  // end if

		xfer->xferSnapshot( squads[ i ] );

	}  // end for, i

	// current squad selection
	Squad *&currentSelection = *reinterpret_cast<Squad **>(self + 0x67c);
	Bool currentSelectionPresent = currentSelection ? TRUE : FALSE;
	xfer->xferBool( &currentSelectionPresent );
	if( currentSelectionPresent )
	{

		// allocate squad if needed
		if( currentSelection == NULL && xfer->isLoading() )
			currentSelection = newInstance( Squad );

		// xfer
		xfer->xferSnapshot( currentSelection );

	}  // end if
	}

	// Player battle plan bonuses
	char *const playerBytes = reinterpret_cast<char *>(this);
	BattlePlanBonuses *&battlePlanBonuses = *reinterpret_cast<BattlePlanBonuses **>(playerBytes + 0x70);
	Int *const battlePlans = reinterpret_cast<Int *>(playerBytes + 0x64);
	Bool battlePlanBonus = battlePlanBonuses != NULL;
	xfer->xferBool( &battlePlanBonus ); //If we're loading, it just replaces the bool
	if( xfer->isLoading() )
	{
		if (battlePlanBonuses)
		{
			battlePlanBonuses->deleteInstance();
			battlePlanBonuses = NULL;
		}
		if ( battlePlanBonus )
		{
			battlePlanBonuses = newInstance( BattlePlanBonuses );
		}
	}
	if( battlePlanBonuses )
	{
		char *const bonus = reinterpret_cast<char *>(battlePlanBonuses);
		xfer->xferReal( reinterpret_cast<Real *>(bonus + 0x00) );
		xfer->xferReal( reinterpret_cast<Real *>(bonus + 0x10) );
		xfer->xferInt( reinterpret_cast<Int *>(bonus + 0x04) );
		xfer->xferInt( reinterpret_cast<Int *>(bonus + 0x08) );
		xfer->xferInt( reinterpret_cast<Int *>(bonus + 0x0c) );
		reinterpret_cast<BfmeBattlePlanBonuses *>(battlePlanBonuses)->m_validKindOf.xfer( reinterpret_cast<Xfer *>(xfer) );
		reinterpret_cast<BfmeBattlePlanBonuses *>(battlePlanBonuses)->m_invalidKindOf.xfer( reinterpret_cast<Xfer *>(xfer) );
	}
	xfer->xferInt( &battlePlans[0] );
	xfer->xferInt( &battlePlans[1] );
	xfer->xferInt( &battlePlans[2] );

}  // end xfer

// ------------------------------------------------------------------------------------------------
