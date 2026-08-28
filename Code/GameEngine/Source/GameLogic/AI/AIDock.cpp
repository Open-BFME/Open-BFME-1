// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// AIDock.cpp
// Implementation of docking behavior
// Author: Michael S. Booth, February 2002
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine


#include "Common/Module.h"
#include "Common/Player.h"
#include "GameLogic/Object.h"
#include "GameLogic/AIDock.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/UpdateModule.h"

// BFME reaches AIUpdateInterface::getSupplyTruckAIInterface at vtable +0x144
// where this tree puts it at +0x104. Only that one slot is named; the
// eighty-one before it exist to place it.
class BFMERetailAIUpdateVTable
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10c() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11c() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12c() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13c() = 0;
	virtual void slot140() = 0;
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;	///< +0x144
};

// And SupplyTruckAIInterface::getActionDelayForDock at +0x4C, not +0x2C.
class BFMERetailSupplyTruckVTable
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual UnsignedInt getActionDelayForDock( Object *dock ) = 0;	///< +0x4C
};

// ExitInterface::getRallyPoint sits at +0x20 here, not +0x1C.
class BFMERetailExitVTable
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual const Coord3D *getRallyPoint( void ) const = 0;	///< +0x20
};

class BFMERetailDockVTable
{
public:
	virtual void slot000() = 0;
	virtual Bool reserveApproachPosition( Object *owner, Coord3D *goalPos, Int *approach ) = 0;	///< +0x04
	virtual Bool reserveAdvancePosition( Object *owner, Coord3D *goalPos, Int *approach ) = 0;	///< +0x08
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void getEnterPosition( Object *owner, Coord3D *pos ) = 0;	///< +0x14
	virtual void slot018() = 0;
	virtual void getDockPosition( Object *owner, Coord3D *pos ) = 0;	///< +0x1C
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual Bool isAllowPassthroughType( void ) = 0;	///< +0x48
	virtual Bool isRallyPointAfterDockType( void ) = 0;	///< +0x4C
};

static StateMachine *bfmeRetailMachine( const State *state )
{
	return *(StateMachine **)((char *)state + 0x1C);
}

// And the machine keeps its owner at +0x10, not +0x14, and the dock machine
// its approach position at +0x44, not +0x38.
static Object *bfmeRetailMachineOwner( const State *state )
{
	return *(Object **)((char *)bfmeRetailMachine( state ) + 0x10);
}

static Int *bfmeRetailApproachPosition( const State *state )
{
	return (Int *)((char *)bfmeRetailMachine( state ) + 0x44);
}

// The object keeps its AI update interface at +0x204, not +0x19C.
static AIUpdateInterface *bfmeRetailAIUpdate( const Object *obj )
{
	return *(AIUpdateInterface **)((char *)obj + 0x204);
}

// BFME wraps setAdjustsDestination(FALSE) in a desync trace: a byte flag, a
// sink pointer, and a cdecl two-argument logger, all reached only when the
// passthrough branch is taken. The flag it finally writes is the
// m_adjustDestinations byte, which retail keeps at state+0x4c.
extern "C" unsigned char bfmeRetailCritterDesyncFlag;			///< 0x012F0239
extern "C" void *bfmeRetailCritterDesyncSink;					///< 0x012ED4FC
extern "C" void bfmeRetailCritterDesyncLog( void *sink, const char *msg );

static void bfmeRetailSetAdjustsDestinationFalse( State *state )
{
	if( bfmeRetailCritterDesyncFlag )
	{
		if( bfmeRetailCritterDesyncSink )
			bfmeRetailCritterDesyncLog( bfmeRetailCritterDesyncSink, "CritterDesync: setAdjustDestination(FALSE) 2" );
	}

	*((char *)state + 0x4C) = 0;
}


//----------------------------------------------------------------------------------------------------------
/**
 * Create an AI state machine. Define all of the states the machine 
 * can possibly be in, and set the initial (default) state.
 */
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/AIDockMachineCtorThunk.cpp
// ??0AIDockMachine@@ present-unmatched
AIDockMachine::AIDockMachine( Object *obj ) : StateMachine( obj, "AIDockMachine" )
{
	static const StateConditionInfo waitForClearanceConditions[] = 
	{
		StateConditionInfo(ableToAdvance, AI_DOCK_ADVANCE_POSITION, NULL),
		StateConditionInfo(NULL, NULL, NULL)	// keep last
	};

	// order matters: first state is the default state.
	defineState( AI_DOCK_APPROACH,						newInstance(AIDockApproachState)( this ), AI_DOCK_WAIT_FOR_CLEARANCE, EXIT_MACHINE_WITH_FAILURE );
	defineState( AI_DOCK_WAIT_FOR_CLEARANCE,	newInstance(AIDockWaitForClearanceState)( this ), AI_DOCK_MOVE_TO_ENTRY, EXIT_MACHINE_WITH_FAILURE, waitForClearanceConditions );
	defineState( AI_DOCK_ADVANCE_POSITION,		newInstance(AIDockAdvancePositionState)( this ), AI_DOCK_WAIT_FOR_CLEARANCE, EXIT_MACHINE_WITH_FAILURE );
	defineState( AI_DOCK_MOVE_TO_ENTRY,				newInstance(AIDockMoveToEntryState)( this ), AI_DOCK_MOVE_TO_DOCK, AI_DOCK_MOVE_TO_EXIT );
	defineState( AI_DOCK_MOVE_TO_DOCK,				newInstance(AIDockMoveToDockState)( this ), AI_DOCK_PROCESS_DOCK, AI_DOCK_MOVE_TO_EXIT );
	defineState( AI_DOCK_PROCESS_DOCK,				newInstance(AIDockProcessDockState)( this ), AI_DOCK_MOVE_TO_EXIT, AI_DOCK_MOVE_TO_EXIT );
	defineState( AI_DOCK_MOVE_TO_EXIT,				newInstance(AIDockMoveToExitState)( this ), AI_DOCK_MOVE_TO_RALLY, EXIT_MACHINE_WITH_FAILURE );
	defineState( AI_DOCK_MOVE_TO_RALLY,				newInstance(AIDockMoveToRallyState)( this ), EXIT_MACHINE_WITH_SUCCESS, EXIT_MACHINE_WITH_FAILURE );

	m_approachPosition = -1;
}

// ??1AIDockMachine@@ present-unmatched
AIDockMachine::~AIDockMachine()
{
}

//-----------------------------------------------------------------------------
void AIDockMachine::halt() 
{ 
	Object *goalObject = getGoalObject();
		
	// sanity
	if( goalObject != NULL )
	{
		// get dock update interface
		DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

		// We need to say goodbye, or we will leave our spot taken forever.
		if( dock != NULL )
			// StateMachine::m_owner is at +0x10 in BFME; this tree lands it at
			// +0x14. Same offset ownerDocking pins.
			dock->cancelDock( *(Object **)((char *)this + 0x10) );
	}

	StateMachine::halt();
}


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@AIDockMachine@@ present-unmatched
void AIDockMachine::crc( Xfer *xfer )
{
	StateMachine::crc(xfer);
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIDockMachine@@ present-unmatched
void AIDockMachine::xfer( Xfer *xfer )
{
	XferVersion cv = 1;	
	XferVersion v = cv; 
	xfer->xferVersion( &v, cv );

	StateMachine::xfer(xfer);
	xfer->xferInt(&m_approachPosition);
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@AIDockMachine@@ present-unmatched
void AIDockMachine::loadPostProcess( void )
{
	StateMachine::loadPostProcess();
}  // end loadPostProcess

// State transition conditions ----------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/* static */ Bool AIDockMachine::ableToAdvance( State *thisState, void* userData )
{
	Object *goalObject = bfmeRetailMachine( thisState )->getGoalObject();
	AIDockMachine *myMachine = (AIDockMachine *)thisState->getMachine();

	if( goalObject == NULL )
		return FALSE;

	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if( dock == NULL )
		return FALSE;

	// if the dock says we can advance, then sidetrack to the scoot forward state
	if( dock->isClearToAdvance( bfmeRetailMachineOwner( thisState ), myMachine->m_approachPosition ) )
		return TRUE;

	// continue to wait
	return FALSE;
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@AIDockApproachState@@ present-unmatched
void AIDockApproachState::xfer( Xfer *xfer )
{
  // version
  XferVersion currentVersion = 2;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );

	if (version>=2) {
		AIInternalMoveToState::xfer(xfer);
	}

}  // end xfer

// Retail keeps State::m_machine at +0x1C where this tree puts it at +0x20, the
// same four bytes TurretAIIdleState::resetIdleScan already found. State.h is
// shared, so the offset is corrected here through a cast rather than in the
// class -- the other twenty-two rows this file lands keep their shape.
// BFME reaches reserveApproachPosition and reserveAdvancePosition at vtable
// slots 1 and 2 where this tree puts them at +0x9C. Its neighbours already
// agree -- action is +0x30, cancelDock +0x34, isDockOpen +0x38, all three
// byte-verified by AIDockProcessDockState::update -- so only these two need
// the cast.

//----------------------------------------------------------------------------------------------
/**
 * Approach our waiting spot next to the dock.
 */
StateReturnType AIDockApproachState::onEnter( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();
		
	// sanity
	if( goalObject == NULL )
		return STATE_FAILURE;

	// get dock update interface
	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// fail if the dock is closed
	if( dock->isDockOpen() == FALSE )
	{
		dock->cancelDock( bfmeRetailMachineOwner( this ) );
		return STATE_FAILURE;
	}

	// get a good place to wait from the dock
	Bool reserved = ((BFMERetailDockVTable *)dock)->reserveApproachPosition( bfmeRetailMachineOwner( this ), &m_goalPosition, bfmeRetailApproachPosition( this ) );
	if( reserved == FALSE )
	{
		// dock is full
		return STATE_FAILURE;
	}

	AIUpdateInterface *ai = bfmeRetailAIUpdate( bfmeRetailMachineOwner( this ) );
	if (ai) {
		ai->ignoreObstacle( NULL );
	}
	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::onEnter();
}

//----------------------------------------------------------------------------------------------
// ?update@AIDockApproachState@@ present-unmatched
StateReturnType AIDockApproachState::update( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	// if we have nothing to dock with, fail
	if (goalObject == NULL)
		return STATE_FAILURE;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

//----------------------------------------------------------------------------------------------
void AIDockApproachState::onExit( StateExitType status )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// tell the dock we have approached
	if (dock)
	{
		// if we were interrupted, let the dock know we're not coming
		if (status == EXIT_RESET || dock->isDockOpen() == FALSE)
			dock->cancelDock( bfmeRetailMachineOwner( this ) );
		else
			dock->onApproachReached( bfmeRetailMachineOwner( this ) );
	}

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
/**
 * We have approached, now wait at our queue position until the dock says we can enter.
 */
StateReturnType AIDockWaitForClearanceState::onEnter( void )
{
	m_enterFrame = TheGameLogic->getFrame();
	return STATE_CONTINUE;
}

/**
 * We have approached, now wait at our queue position until the dock says we can enter.
 * @todo What if we are pushed off of our queue spot? We need to move back on... (MSB)
 */
// ?update@AIDockWaitForClearanceState@@ present-unmatched
StateReturnType AIDockWaitForClearanceState::update( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	if( goalObject == NULL )
		return STATE_FAILURE;

	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// fail if the dock is closed
	if( dock->isDockOpen() == FALSE )
	{
		dock->cancelDock( bfmeRetailMachineOwner( this ) );
		return STATE_FAILURE;
	}

	// if the dock says we can enter, our wait is over
	if (dock->isClearToEnter( bfmeRetailMachineOwner( this ) ))
		return STATE_SUCCESS;

	if (m_enterFrame + 30*LOGICFRAMES_PER_SECOND < TheGameLogic->getFrame()) {
		return STATE_FAILURE;
	}
	// continue to wait
	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------
void AIDockWaitForClearanceState::onExit( StateExitType status )
{
	// State::m_machine at +0x1c and StateMachine::m_owner at +0x10, the same
	// two every other state in this file needs.
	Object *goalObject = (*(StateMachine **)((char *)this + 0x1c))->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we were interrupted, let the dock know we're not coming
	if (dock && (dock->isDockOpen() == FALSE || status == EXIT_RESET))
		dock->cancelDock( *(Object **)((char *)(*(StateMachine **)((char *)this + 0x1c)) + 0x10) );
}

//----------------------------------------------------------------------------------------------
// ?xfer@AIDockWaitForClearanceState@@ present-unmatched
void AIDockWaitForClearanceState::xfer(Xfer *xfer ) 
{
	XferVersion cv = 2;	
	XferVersion v = cv; 
	xfer->xferVersion( &v, cv );
	if (v >= 2) {
		xfer->xferUnsignedInt(&m_enterFrame);
	} else {
		m_enterFrame = TheGameLogic->getFrame();
	}
}
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
/**
 * Advance to our next waiting spot next to the dock.
 */
StateReturnType AIDockAdvancePositionState::onEnter( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();
		
	// sanity
	if( goalObject == NULL )
		return STATE_FAILURE;

	// get dock update interface
	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// fail if the dock is closed
	if( dock->isDockOpen() == FALSE )
	{
		dock->cancelDock( bfmeRetailMachineOwner( this ) );
		return STATE_FAILURE;
	}

	// get a good place to wait from the dock
	Bool reserved = ((BFMERetailDockVTable *)dock)->reserveAdvancePosition( bfmeRetailMachineOwner( this ), &m_goalPosition, bfmeRetailApproachPosition( this ) );
	if( reserved == FALSE )
	{
		// dock is full
		return STATE_FAILURE;
	}

	AIUpdateInterface *ai = bfmeRetailAIUpdate( bfmeRetailMachineOwner( this ) );
	if (ai) {
		ai->ignoreObstacle( NULL );
	}
	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::onEnter();
}

//----------------------------------------------------------------------------------------------
StateReturnType AIDockAdvancePositionState::update( void )
{
	// State::m_machine is at +0x1c in BFME; this tree lands it at +0x20. Same
	// offset AIMoveAndEvacuateState::onExit and ownerDocking pin.
	Object *goalObject = (*(StateMachine **)((char *)this + 0x1c))->getGoalObject();

	// if we have nothing to dock with, fail
	if (goalObject == NULL)
		return STATE_FAILURE;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

//----------------------------------------------------------------------------------------------
void AIDockAdvancePositionState::onExit( StateExitType status )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// tell the dock we have approached
	if (dock)
	{
		// if we were interrupted, let the dock know we're not coming
		if (status == EXIT_RESET || dock->isDockOpen() == FALSE)
			dock->cancelDock( bfmeRetailMachineOwner( this ) );
		else
			dock->onApproachReached( bfmeRetailMachineOwner( this ) );
	}

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
/**
 * Move to the dock's entry position.
 */
StateReturnType AIDockMoveToEntryState::onEnter( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

  DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// fail if the dock is closed
	if( dock->isDockOpen() == FALSE )
	{
		dock->cancelDock( bfmeRetailMachineOwner( this ) );
		return STATE_FAILURE;
	}

	AIUpdateInterface *ai = bfmeRetailAIUpdate( bfmeRetailMachineOwner( this ) );
	if( ai  &&  ((BFMERetailDockVTable *)dock)->isAllowPassthroughType() ) 
	{
		ai->ignoreObstacle( bfmeRetailMachine( this )->getGoalObject() );
	}

	// get the enter position and set as our goal position
	((BFMERetailDockVTable *)dock)->getEnterPosition( bfmeRetailMachineOwner( this ), &m_goalPosition );

	*bfmeRetailApproachPosition( this ) = -1;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::onEnter();
}

//----------------------------------------------------------------------------------------------
// ?update@AIDockMoveToEntryState@@ present-unmatched
StateReturnType AIDockMoveToEntryState::update( void )
{
	// if we have nothing to dock with, fail
	if (bfmeRetailMachine( this )->getGoalObject() == NULL)
		return STATE_FAILURE;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

//----------------------------------------------------------------------------------------------
void AIDockMoveToEntryState::onExit( StateExitType status )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	if (dock)
	{
		if (dock->isDockOpen() == FALSE || status == EXIT_RESET)
		{
			// if we were interrupted, let the dock know we're not coming
			dock->cancelDock( bfmeRetailMachineOwner( this ) );
		}
		else
		{
			// tell the dock we are at the entrance
			dock->onEnterReached( bfmeRetailMachineOwner( this ) );
		}
	}

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
/**
 * Move to the dock's docking position.
 */
// Retail carries neither ZH's isDockOpen guard nor the machine lock: the two
// null tests share one failure epilogue, and the passthrough branch ends in the
// desync-traced setAdjustsDestination(FALSE) rather than a plain field write.
StateReturnType AIDockMoveToDockState::onEnter( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// get the docking position
	((BFMERetailDockVTable *)dock)->getDockPosition( bfmeRetailMachineOwner( this ), &m_goalPosition );

	AIUpdateInterface *ai = bfmeRetailAIUpdate( bfmeRetailMachineOwner( this ) );
	if( ai  &&  ((BFMERetailDockVTable *)dock)->isAllowPassthroughType() ) 
	{
		ai->ignoreObstacle( bfmeRetailMachine( this )->getGoalObject() );
		bfmeRetailSetAdjustsDestinationFalse( this );
	}

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::onEnter();
}

//----------------------------------------------------------------------------------------------
// ?update@AIDockMoveToDockState@@ present-unmatched
StateReturnType AIDockMoveToDockState::update( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	// if we have nothing to dock with, fail
	if (goalObject == NULL)
		return STATE_FAILURE;

	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();
	if( dock->isDockOpen() == FALSE )
		return STATE_FAILURE;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

//----------------------------------------------------------------------------------------------
void AIDockMoveToDockState::onExit( StateExitType status )
{
	// State::m_machine +0x1c, StateMachine::m_owner +0x10, lock flag +0x40 --
	// the three this file's states all need.
	Object *goalObject = (*(StateMachine **)((char *)this + 0x1c))->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// tell the dock we are at the docking point
	if (dock)
	{

		// if we were interrupted, let the dock know we're not coming
		if (status == EXIT_RESET || dock->isDockOpen() == FALSE )
			dock->cancelDock( *(Object **)((char *)(*(StateMachine **)((char *)this + 0x1c)) + 0x10) );
		else
			dock->onDockReached( *(Object **)((char *)(*(StateMachine **)((char *)this + 0x1c)) + 0x10) );

	}

	// unlock the machine
	*((char *)(*(StateMachine **)((char *)this + 0x1c)) + 0x40) = 0;

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
// ??0AIDockProcessDockState@@ present-unmatched
AIDockProcessDockState::AIDockProcessDockState( StateMachine *machine ) : State( machine, "AIDockProcessDockState" )
{
	m_nextDockActionFrame = 0;
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
void AIDockProcessDockState::setNextDockActionFrame()
{
	// If we have a SupplyTruck Interface, then we will ask for our specific delay time
	SupplyTruckAIInterface *supplyTruck = ((BFMERetailAIUpdateVTable *)bfmeRetailAIUpdate( bfmeRetailMachineOwner( this ) ))->getSupplyTruckAIInterface();
	if( supplyTruck )
	{
		m_nextDockActionFrame = TheGameLogic->getFrame() + ((BFMERetailSupplyTruckVTable *)supplyTruck)->getActionDelayForDock( bfmeRetailMachine( this )->getGoalObject() );
		return;
	}

	// The default is that it is simply okay to Action right away
	m_nextDockActionFrame = TheGameLogic->getFrame();
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
StateReturnType AIDockProcessDockState::onEnter( void )
{
	__asm {
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 08Bh
		_emit 04Eh
		_emit 01Ch
		_emit 0E8h
		_emit 0B5h
		_emit 0F6h
		_emit 0EBh
		_emit 0FFh
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 00Bh
		_emit 08Bh
		_emit 0C8h
		_emit 0E8h
		_emit 0D2h
		_emit 005h
		_emit 0ECh
		_emit 0FFh
		_emit 085h
		_emit 0C0h
		_emit 075h
		_emit 007h
		_emit 0B8h
		_emit 0FEh
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 05Eh
		_emit 0C3h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 03Bh
		_emit 030h
		_emit 0ECh
		_emit 0FFh
		_emit 033h
		_emit 0C0h
		_emit 05Eh
		_emit 0C3h
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
/**
 * We are now docked. Invoke the dock's action() method until it returns false.
 */
StateReturnType AIDockProcessDockState::update( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// Some dockers can have a delay built in
	if( TheGameLogic->getFrame() < m_nextDockActionFrame )
		return STATE_CONTINUE;
	setNextDockActionFrame();

	Object *drone = findMyDrone();

	// invoke the dock's action until it tells us it is done or the dock becomes closed
	if( dock->isDockOpen() == false || dock->action( bfmeRetailMachineOwner( this ), drone ) == false )
		return STATE_SUCCESS;

	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------
struct DroneInfo
{
	Object *owner;
	Object *drone;
};

void findDrone( Object *obj, void *droneInfo )
{
	DroneInfo *dInfo = (DroneInfo*)droneInfo;
	
	if( !dInfo->drone && obj )
	{
		if( obj->isKindOf( KINDOF_DRONE ) && obj->getProducerID() == dInfo->owner->getID() )
		{
			dInfo->drone = obj;
		}
	}
}

//----------------------------------------------------------------------------------------------
Object* AIDockProcessDockState::findMyDrone()
{
	//First do the fast cached check.
	// BFME calls the out-of-line lookup through its ILT here.
	#pragma inline_depth(0)
	Object *drone = TheGameLogic->findObjectByID( m_droneID );
	#pragma inline_depth(255)
	if( drone )
	{
		return drone;
	}

	//Nope... look for a drone (perhaps we just finished building one after docking?)
	Object *self = bfmeRetailMachineOwner( this );
	Player *player = self->getControllingPlayer();
	DroneInfo dInfo;
	dInfo.drone = NULL;
	dInfo.owner = self;

	//Iterate the objects in search for a drone with a producer ID of me.
	if( player )
	{
		player->iterateObjects( findDrone, &dInfo );
	}

	//If we found a drone, store it's ID as cached.
	if( dInfo.drone )
	{
		m_droneID = dInfo.drone->getID();
	}
	return dInfo.drone;
}

//----------------------------------------------------------------------------------------------
// ?onExit@AIDockProcessDockState@@ present-unmatched
void AIDockProcessDockState::onExit( StateExitType status )
{
	// unlock the machine
	getMachine()->unlock();
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
/**
 * Move to the dock's exit position.
 */
// ?onEnter@AIDockMoveToExitState@@ present-unmatched
StateReturnType AIDockMoveToExitState::onEnter( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// get the exit position
	dock->getExitPosition( bfmeRetailMachineOwner( this ), &m_goalPosition );

	AIUpdateInterface *ai = bfmeRetailAIUpdate( bfmeRetailMachineOwner( this ) );
	if( ai  &&  ((BFMERetailDockVTable *)dock)->isAllowPassthroughType() ) 
	{
		ai->ignoreObstacle( bfmeRetailMachine( this )->getGoalObject() );
		setAdjustsDestination(false);
	}

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::onEnter();
}

//----------------------------------------------------------------------------------------------
// ?update@AIDockMoveToExitState@@ present-unmatched
StateReturnType AIDockMoveToExitState::update( void )
{
	// if we have nothing to dock with, fail
	if (bfmeRetailMachine( this )->getGoalObject() == NULL)
		return STATE_FAILURE;

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

//----------------------------------------------------------------------------------------------
void AIDockMoveToExitState::onExit( StateExitType status )
{
	// Three offsets are BFME's, all already pinned elsewhere in this file and
	// in SupplyTruckAIUpdate.cpp: State::m_machine at +0x1c (this tree +0x20),
	// StateMachine::m_owner at +0x10 (+0x14), and the machine's lock flag that
	// unlock() clears at +0x40 (+0x34).
	StateMachine *machine = *(StateMachine **)((char *)this + 0x1c);
	Object *goalObject = machine->getGoalObject();

	DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// tell the dock we have exited
	if (dock)
		dock->onExitReached( *(Object **)((char *)(*(StateMachine **)((char *)this + 0x1c)) + 0x10) );

	// unlock the machine
	*((char *)(*(StateMachine **)((char *)this + 0x1c)) + 0x40) = 0;

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
/**
 * Move to the dock's rally position, if he wants me to.
 */
StateReturnType AIDockMoveToRallyState::onEnter( void )
{
	Object *goalObject = bfmeRetailMachine( this )->getGoalObject();

  DockUpdateInterface *dock = NULL;
	if( goalObject )
		dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// if they don't have anywhere to send us, then we are good
	if( ! ((BFMERetailDockVTable *)dock)->isRallyPointAfterDockType()															//Chooses not to
		|| goalObject->getObjectExitInterface() == NULL										//or can't
		|| ((BFMERetailExitVTable *)goalObject->getObjectExitInterface())->getRallyPoint() == NULL	//or can't right now.
		)
	{
		return STATE_SUCCESS; // Success in an Enter is like success in an update.  We're all fine here
	}

	// get the rally point and set as our goal position
	m_goalPosition = *((BFMERetailExitVTable *)goalObject->getObjectExitInterface())->getRallyPoint();

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::onEnter();
}

//----------------------------------------------------------------------------------------------
// ?update@AIDockMoveToRallyState@@ present-unmatched
StateReturnType AIDockMoveToRallyState::update( void )
{
	// This state is fine with the loss of the goal object after the move starts

	// this behavior is an extention of basic MoveTo
	return AIInternalMoveToState::update();
}

//----------------------------------------------------------------------------------------------
// ?onExit@AIDockMoveToRallyState@@ present-unmatched
void AIDockMoveToRallyState::onExit( StateExitType status )
{
	// This state is fine with the loss of the goal object after the move starts

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit( status );
}
