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

// FILE: ToppleUpdate.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, December 2001
// Desc:   Update for something that sits around until hit, then topples and stops
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/FXList.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/ToppleUpdate.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/Module/SwayClientUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Damage.h"

//-------------------------------------------------------------------------------------------------
// this is our "bounce" limit -- slightly less that 90 degrees, to account for slop.
static const Real ANGULAR_LIMIT = PI/2 - PI/64;		

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0ToppleUpdateModuleData@@ is implemented by the exact retail thunk in
// ToppleUpdateModuleDataCtorThunk.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?buildFieldParse@ToppleUpdateModuleData@@ present-unmatched
void ToppleUpdateModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "ToppleFX",	INI::parseFXList, NULL, offsetof( ToppleUpdateModuleData, m_toppleFX ) },
		{ "BounceFX",	INI::parseFXList, NULL, offsetof( ToppleUpdateModuleData, m_bounceFX ) },
		{ "StumpName",	INI::parseAsciiString, NULL, offsetof( ToppleUpdateModuleData, m_stumpName ) },
		{ "KillWhenStartToppling",	INI::parseBool, NULL, offsetof( ToppleUpdateModuleData, m_killWhenStartToppled ) },
		{ "KillWhenFinishedToppling",	INI::parseBool, NULL, offsetof( ToppleUpdateModuleData, m_killWhenToppled ) },
		{ "KillStumpWhenToppled",	INI::parseBool, NULL, offsetof( ToppleUpdateModuleData, m_killStumpWhenToppled ) },
		{ "ToppleLeftOrRightOnly",	INI::parseBool, NULL, offsetof( ToppleUpdateModuleData, m_toppleLeftOrRightOnly ) },
		{ "ReorientToppledRubble",	INI::parseBool, NULL, offsetof( ToppleUpdateModuleData, m_reorientToppledRubble ) },
		{ "InitialVelocityPercent",	INI::parsePercentToReal, NULL, offsetof( ToppleUpdateModuleData, m_initialVelocityPercent ) },
		{ "InitialAccelPercent",	INI::parsePercentToReal, NULL, offsetof( ToppleUpdateModuleData, m_initialAccelPercent ) },
		{ "BounceVelocityPercent",	INI::parsePercentToReal, NULL, offsetof( ToppleUpdateModuleData, m_bounceVelocityPercent ) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdateCtorThunk.cpp
// ??0ToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
ToppleUpdate::ToppleUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_angleDeltaX = 0.0f;
	m_doBounceFX = FALSE;
	m_numAngleDeltaX = 0;
	//
	m_angularVelocity = 0;
	m_angularAccumulation = 0;
	m_angularAcceleration = 0;	
	m_toppleDirection.x = 0;
	m_toppleDirection.y = 0;
	m_toppleDirection.z = 0;
	m_toppleState = TOPPLE_UPRIGHT;
	m_options = TOPPLE_OPTIONS_NONE;
	m_stumpID = INVALID_ID;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Real angleClosestTo(Real a1, Real a2, Real desired)
{
	a1 = normalizeAngle(a1);
	a2 = normalizeAngle(a2);
	return (fabs(stdAngleDiff(desired, a1)) < fabs(stdAngleDiff(desired, a2))) ? a1 : a2;
}


//-------------------------------------------------------------------------------------------------
///< Ask if this module is able to be toppled
//-------------------------------------------------------------------------------------------------
Bool ToppleUpdate::isAbleToBeToppled() const
{
	return m_toppleState == TOPPLE_UPRIGHT;
}

//-------------------------------------------------------------------------------------------------
static void deathByToppling(Object* obj)
{
	// use a special "topppling" damage type here so that
	// toppled stuff can have different damage/die modules 
	// for toppled-death vs other-death
	DamageInfo damageInfo;
	damageInfo.in.m_damageType = DAMAGE_UNRESISTABLE;
	damageInfo.in.m_deathType = DEATH_TOPPLED;
	damageInfo.in.m_sourceID = INVALID_ID;
	damageInfo.in.m_amount = HUGE_DAMAGE_AMOUNT;
	obj->attemptDamage(&damageInfo);
}

//-------------------------------------------------------------------------------------------------
///< Keep track of rotational fall distance, bounce and/or stop when needed.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Do the collision */
//-------------------------------------------------------------------------------------------------
// Retail ToppleUpdate::onCollide (0x002B12C0) is provided by ToppleUpdate_onCollide.cpp.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@ToppleUpdate@@MAEXPAVXfer@@@Z present-unmatched
void ToppleUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@ToppleUpdate@@MAEXPAVXfer@@@Z present-unmatched
void ToppleUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// angular velocity
	xfer->xferReal( &m_angularVelocity );

	// angular acceleration
	xfer->xferReal( &m_angularAcceleration );

	// topple direction
	xfer->xferCoord3D( &m_toppleDirection );

	// topple state
	xfer->xferUser( &m_toppleState, sizeof( ToppleState	) );

	// angluar accumulation
	xfer->xferReal( &m_angularAccumulation );

	// angle delta X
	xfer->xferReal( &m_angleDeltaX );

	// num angle delta X
	xfer->xferInt( &m_numAngleDeltaX );

	// do bounce FX
	xfer->xferBool( &m_doBounceFX );

	// options
	xfer->xferUnsignedInt( &m_options );

	// stump id
	xfer->xferObjectID( &m_stumpID );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@ToppleUpdate@@MAEXXZ present-unmatched
void ToppleUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
