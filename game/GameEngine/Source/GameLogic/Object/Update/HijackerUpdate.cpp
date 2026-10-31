// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/shims/aicommandoutofline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// FILE: HijackerUpdate.cpp 
// Author: Mark Lorenzen, July 2002
// Desc:   Allows hijacker to kepp with his hijacked vehicle (though hidden) until it dies, then 
// to become a hijacker once more
//
/////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/HijackerUpdate.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/EjectPilotDie.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/ExperienceTracker.h"

// HijackerUpdate's constructor is defined in HijackerUpdateConstructor.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The destructor (retail 0x00295AC0) is defined in HijackerUpdateDestructor.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ: retail body is in HijackerUpdateUpdate.cpp



void HijackerUpdate::setTargetObject( const Object *object )
{
  if( object )
  {
    m_targetID = object->getID();

		// here we also test the target to see whether it ejects pilots
		// when it dies... if so, stores a pointer to that diemoduleinterface
		// NULL if not...

//		BehaviorModule **dmi = NULL;
//		for( dmi = object->getBehaviorModules(); *dmi; ++dmi )
//		{
//			m_ejectPilotDMI = (*dmi)->getEjectPilotDieInterface();
//			if( m_ejectPilotDMI )
//				return;
//		}  // end for dmi
  }
	else
	{
		m_targetID = INVALID_ID;
//		m_ejectPilotDMI = NULL;
	}

}

// ?getTargetObject@HijackerUpdate@@ present-unmatched
Object* HijackerUpdate::getTargetObject() const
{
  if( m_targetID != INVALID_ID )
  {
    return TheGameLogic->findObjectByID( m_targetID );
  }
  return NULL;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@HijackerUpdate@@ present-unmatched
void HijackerUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@HijackerUpdate@@ present-unmatched
void HijackerUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// target ID
	xfer->xferObjectID( &m_targetID );

	// eject pos
	xfer->xferCoord3D( &m_ejectPos );

	// udpate
	xfer->xferBool( &m_update );

	// is in vehicle
	xfer->xferBool( &m_isInVehicle );

	// was target airborne
	xfer->xferBool( &m_wasTargetAirborne );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@HijackerUpdate@@ present-unmatched
void HijackerUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

	// set the target object, this will also tie up teh m_ejectPilotDMI pointer
	Object *obj = TheGameLogic->findObjectByID( m_targetID );
	setTargetObject( obj );

}  // end loadPostProcess
