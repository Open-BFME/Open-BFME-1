// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves

// Open-BFME7: near-miss twin of AIDockMachine::ableToAdvance (dump target
// 0x0014E6B0, near copy in the already-landed AIDock.cpp). AIDock.cpp's own
// ableToAdvance body reads thisState->getMachine() (this tree's State
// layout, m_machine at +0x20) and myMachine->m_approachPosition (this
// tree's AIDockMachine layout, +0x38) directly instead of going through the
// file's bfmeRetailMachine()/bfmeRetailApproachPosition() helpers the way
// every sibling AIDockMachine method in that file does, so it compiles 2
// bytes off retail (state+0x1c, not +0x20; approach position at +0x44, not
// +0x38 -- see AIDock.cpp's own comment above bfmeRetailApproachPosition).
// This is a byte-exact twin of the same source function, written under an
// address-tagged name so it does not collide with the real mangled symbol
// already defined (with the wrong offsets) in AIDock.cpp.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Module.h"
#include "Common/Player.h"
#include "GameLogic/Object.h"
#include "GameLogic/AIDock.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/UpdateModule.h"

// Same retail-offset story as AIDock.cpp: State::m_machine is at +0x1c (not
// this tree's +0x20), StateMachine::m_owner at +0x10, and AIDockMachine's
// m_approachPosition at +0x44 (not +0x38). Retail re-derives the machine
// pointer from thisState at each use rather than caching it in one
// register, so these stay forced-inline one-liners re-evaluated at each
// call site to reproduce that shape.
static __forceinline StateMachine *bfmeRetailMachine0014E6B0( const State *state )
{
	return *(StateMachine **)((char *)state + 0x1C);
}

static __forceinline Object *bfmeRetailMachineOwner0014E6B0( const State *state )
{
	return *(Object **)((char *)bfmeRetailMachine0014E6B0( state ) + 0x10);
}

class Rva0014E6B0AIDockMachine
{
public:
	static Bool ableToAdvance( State *thisState, void *userData );
};

/* static */ Bool Rva0014E6B0AIDockMachine::ableToAdvance( State *thisState, void *userData )
{
	Object *goalObject = bfmeRetailMachine0014E6B0( thisState )->getGoalObject();
	StateMachine *myMachine = bfmeRetailMachine0014E6B0( thisState );

	if( goalObject == NULL )
		return FALSE;

	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if( dock == NULL )
		return FALSE;

	// if the dock says we can advance, then sidetrack to the scoot forward state
	if( dock->isClearToAdvance( bfmeRetailMachineOwner0014E6B0( thisState ), *(Int *)((char *)myMachine + 0x44) ) )
		return TRUE;

	// continue to wait
	return FALSE;
}
