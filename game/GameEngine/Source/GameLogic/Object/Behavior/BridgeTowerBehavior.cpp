// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// FILE: BridgeTowerBehavior.cpp //////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   Behavior module for the towers attached to bridges that can be targeted
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/TerrainLogic.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorCtorThunk.cpp
// ??0BridgeTowerBehavior@@ present-unmatched
BridgeTowerBehavior::BridgeTowerBehavior( Thing *thing, const ModuleData *moduleData )
									 : BehaviorModule( thing, moduleData )
{

	m_bridgeID = INVALID_ID;

}  // end BridgeTowerBehavior

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// The destructor (retail 0x001F5F70) is defined in BridgeTowerBehaviorDestructor.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::setBridge( Object *bridge )
{

	if( bridge == NULL )
		m_bridgeID = INVALID_ID;
	else
		m_bridgeID = bridge->getID();

}  // end setBridge

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?getBridgeID@BridgeTowerBehavior@@ present-unmatched
ObjectID BridgeTowerBehavior::getBridgeID( void )
{

	return m_bridgeID;

}  // end getBridge

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?setTowerType@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::setTowerType( BridgeTowerType type )
{

	m_type = type;

}  // end setTowerType

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Body in BridgeTowerBehaviorOnDamage.cpp (verified 514B at 0x001F6250).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void BridgeTowerBehavior::onBodyDamageStateChange( const DamageInfo* damageInfo, 
																									 BodyDamageType oldState, 
																									 BodyDamageType newState )
{

}  // end onBodyDamageStateChange

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onDie@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::onDie( const DamageInfo *damageInfo )
{

	// kill the bridge object, this will kill all the towers
	Object *bridge = TheGameLogic->findObjectByID( getBridgeID() );
	if( bridge )
		bridge->kill();

}  // end onDie

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
/** Given an object, return a bridge tower interface if that object has one */
// ------------------------------------------------------------------------------------------------
class BridgeTowerThingTemplateView
{
public:
	void *m_vtable;
	BridgeTowerThingTemplateView *m_nextOverride;
	unsigned char m_beforeKindOf[0xc0];
	unsigned int m_kindOf;
};

class BridgeTowerModuleInterfaceView
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterface();
};

extern void j_000022bb();

BridgeTowerBehaviorInterface *BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject( Object *obj )
{

	// sanity
	if( obj == NULL )
		return NULL;

	BridgeTowerThingTemplateView *thingTemplate = *(BridgeTowerThingTemplateView **)((unsigned char *)obj + 4);
	if( thingTemplate != NULL && thingTemplate->m_nextOverride != NULL )
	{
		typedef BridgeTowerThingTemplateView *(__fastcall *FinalOverrideCall)(BridgeTowerThingTemplateView *);
		FinalOverrideCall overrideCall = (FinalOverrideCall)j_000022bb;
		thingTemplate = overrideCall( thingTemplate->m_nextOverride );
	}

	if( (thingTemplate->m_kindOf & 0x01000000) == 0 )
		return NULL;

	BehaviorModule **bmi = *(BehaviorModule ***)((unsigned char *)obj + 0x1f0);
	BridgeTowerBehaviorInterface *bridgeTowerInterface = NULL;
	for( ; *bmi; ++bmi )
	{

		BridgeTowerModuleInterfaceView *moduleInterface =
			(BridgeTowerModuleInterfaceView *)((unsigned char *)*bmi + 0x0c);
		bridgeTowerInterface = moduleInterface->getBridgeTowerBehaviorInterface();
		if( bridgeTowerInterface )
			return bridgeTowerInterface;

	}  // end for bmi

	// interface not found
	return NULL;

}  // getBridgeTowerBehaviorInterfaceFromObject

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::crc( Xfer *xfer )
{

	// extend base class
	BehaviorModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	BehaviorModule::xfer( xfer );

	// xfer bridge object ID
	xfer->xferObjectID( &m_bridgeID );

	// xfer tower type
	xfer->xferUser( &m_type, sizeof( BridgeTowerType ) );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BridgeTowerBehavior@@ present-unmatched
void BridgeTowerBehavior::loadPostProcess( void )
{

	// extend base class
	BehaviorModule::loadPostProcess();

}  // end loadPostProcess
