// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/aicommandoutofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// AssaultTransportAIUpdate.cpp ////////////
// Author: Kris Morness, December 2002
// Desc:   State machine that allows assault transports (troop crawler) to deploy
//         troops, order them to attack, then return. Can do extra things like ordering
//         injured troops to return to the transport for healing purposes.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// Retail AssaultTransportAIUpdate::AssaultTransportAIUpdate (0x002B46F0) is implemented in AssaultTransportAIUpdateCtorThunk.cpp.

//-------------------------------------------------------------------------------------------------
// ?reset@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::reset()
{
	for( int i = 0; i < m_currentMembers; i++ )
	{
		m_memberIDs[ i ] = INVALID_ID;
		m_memberHealing[ i ] = FALSE;
		m_newMember[ i ] = FALSE;
	}
	m_currentMembers = 0;
  m_attackMoveGoalPos.zero();
  m_designatedTarget = INVALID_ID;
	m_state = IDLE;
	m_framesRemaining = 0;
	m_isAttackMove = FALSE;
	m_isAttackObject = FALSE;
	m_newOccupantsAreNewMembers = FALSE;
}

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/AssaultTransportAIUpdateDestructorThunk.cpp
// ??1AssaultTransportAIUpdate@@ present-unmatched
AssaultTransportAIUpdate::~AssaultTransportAIUpdate( void )
{
} 

//-------------------------------------------------------------------------------------------------
// The matched AssaultTransportAIUpdate::aiDoCommand lives in AssaultTransportAIUpdate_aiDoCommand.cpp.

//-------------------------------------------------------------------------------------------------
void AssaultTransportAIUpdate::beginAssault( const Object *designatedTarget ) const
{
	//The transport has determined it is in range to begin the assault (via weapon system).
	//Now order the evacuation of healthy troops, and let the update handle moving them.
	if( designatedTarget )
	{
		m_designatedTarget = designatedTarget->getID();
	}
}

//-------------------------------------------------------------------------------------------------
// ?isIdle@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isIdle() const
{
	return AIUpdateInterface::isIdle();
}

//-------------------------------------------------------------------------------------------------
UpdateSleepTime calcSleepTime()
{
	return UPDATE_SLEEP_NONE;
}

//-------------------------------------------------------------------------------------------------
// The matched AssaultTransportAIUpdate::update lives in AssaultTransportAIUpdate_update.cpp.

//-------------------------------------------------------------------------------------------------
// ?isAttackPointless@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isAttackPointless() const
{
	//If all members are new members (thus can't attack), and the transport itself
	//is still attacking, stop!
	const Object *transport = getObject();
	if( transport->testStatus( OBJECT_STATUS_IS_ATTACKING ) )
	{
		for( int i = 0; i < m_currentMembers; i++ )
		{
			if( !m_newMember[ i ] )
			{
				//We have a non-new member, so attack is valid.
				return FALSE;
			}
		}

		//We are trying to attack, but can't because all our members are new.
		return TRUE;
	}

	//We aren't trying to attack, so everything is good.
	return FALSE;
}

// The matched isMemberWounded definition lives in AssaultTransportAIUpdate_isMemberWoundedTwin.cpp.

//-------------------------------------------------------------------------------------------------
// ?isMemberHealthy@AssaultTransportAIUpdate@@ present-unmatched
Bool AssaultTransportAIUpdate::isMemberHealthy( const Object *member ) const
{
	BodyModuleInterface *body = member->getBodyModule();
	if( body )
	{
		if( body->getHealth() == body->getMaxHealth() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// The matched AssaultTransportAIUpdate::retrieveMembers lives in AssaultTransportAIUpdate_retrieveMembers.cpp.

//-------------------------------------------------------------------------------------------------
// The matched AssaultTransportAIUpdate::giveFinalOrders lives in AssaultTransportAIUpdate_giveFinalOrders.cpp.

//-------------------------------------------------------------------------------------------------
/** CRC */
//-------------------------------------------------------------------------------------------------
// ?crc@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::crc( Xfer *xfer )
{
	// extend base class
	AIUpdateInterface::crc(xfer);
}  // end crc

//-------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
//-------------------------------------------------------------------------------------------------
// The matched AssaultTransportAIUpdate::xfer lives in AssaultTransportAIUpdate_xfer.cpp.

//-------------------------------------------------------------------------------------------------
/** Load post process */
//-------------------------------------------------------------------------------------------------
// ?loadPostProcess@AssaultTransportAIUpdate@@ present-unmatched
void AssaultTransportAIUpdate::loadPostProcess( void )
{
 // extend base class
	AIUpdateInterface::loadPostProcess();
}  // end loadPostProcess
