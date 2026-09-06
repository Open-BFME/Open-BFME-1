// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves

// Open-BFME7: near-miss twin of AIDockWaitForClearanceState::update (dump
// target 0x0014E880, near copy in the already-landed AIDock.cpp: same file,
// same field offsets, only one immediate differs). AIDock.cpp's own
// present-unmatched update() body multiplies 30*LOGICFRAMES_PER_SECOND using
// the shared ZH header's LOGICFRAMES_PER_SECOND==30 (Generals' 30fps logic
// rate), giving 0x384. Retail's compiled constant is 0x96 (=150=30*5): BFME
// runs its logic at 5 frames/sec, not 30 -- see the local
// "enum { LOGICFRAMES_PER_SECOND = 5 }" override already used in this same
// class hierarchy elsewhere in the tree (GameClient/GUI/ControlBar/
// ControlBar_getStarImage_Thunk.cpp, GameClient/ControlBar_updateContext
// OCLTimer.cpp). This is a byte-exact twin under an address-tagged name so
// it does not collide with the real mangled symbol already defined (with
// the wrong constant) in AIDock.cpp.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Module.h"
#include "Common/Player.h"
#include "GameLogic/Object.h"
#include "GameLogic/AIDock.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/UpdateModule.h"

static StateMachine *bfmeRetailMachine0014E880( const State *state )
{
	return *(StateMachine **)((char *)state + 0x1C);
}

static Object *bfmeRetailMachineOwner0014E880( const State *state )
{
	return *(Object **)((char *)bfmeRetailMachine0014E880( state ) + 0x10);
}

// Same layout as AIDockWaitForClearanceState : State -- m_enterFrame is the
// State's only added data member, at +0x24.
class Rva0014E880WaitForClearanceState : public State
{
public:
	StateReturnType update( void );
protected:
	UnsignedInt m_enterFrame;
};

StateReturnType Rva0014E880WaitForClearanceState::update( void )
{
	Object *goalObject = bfmeRetailMachine0014E880( this )->getGoalObject();

	if( goalObject == NULL )
		return STATE_FAILURE;

	DockUpdateInterface *dock = goalObject->getDockUpdateInterface();

	// if we have nothing to dock with, fail
	if (dock == NULL)
		return STATE_FAILURE;

	// fail if the dock is closed
	if( dock->isDockOpen() == FALSE )
	{
		dock->cancelDock( bfmeRetailMachineOwner0014E880( this ) );
		return STATE_FAILURE;
	}

	// if the dock says we can enter, our wait is over
	if (dock->isClearToEnter( bfmeRetailMachineOwner0014E880( this ) ))
		return STATE_SUCCESS;

	// BFME's real logic rate is 5 frames/sec, not the ZH header's 30
	// (LOGICFRAMES_PER_SECOND==30); 30*5 written as the literal to avoid
	// redefining the shared header's enumerator.
	if (m_enterFrame + 150 < TheGameLogic->getFrame()) {
		return STATE_FAILURE;
	}
	// continue to wait
	return STATE_CONTINUE;
}
