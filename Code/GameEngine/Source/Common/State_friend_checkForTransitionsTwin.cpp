// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?friend_checkForTransitions@State@@: Code/GameEngine/Source/Common/StateMachine.cpp
// Open-BFME: State::friend_checkForTransitions, retail 0x000A03B0.
//
// Same layout shift as the landed sibling State::friend_checkForSleepTransitions
// (0x000A05D0, in StateMachine.cpp): BFME's State object carries m_successStateID
// at this+0x08, m_failureStateID at this+0x0c, m_transitions (a std::vector) at
// this+0x10, and m_machine at this+0x1c, four bytes earlier for the last two
// than the tracked TU's current State class computes them (+0xc/+0x10/+0x14/
// +0x20 there). Reproduced here as an independent twin TU rather than editing
// the landed StateMachine.cpp.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Errors.h"
#include "Common/StateMachine.h"
#include "Common/ThingTemplate.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"

namespace {

struct BfmeTransitionInfo
{
	StateTransFuncPtr test;
	StateID toStateID;
	void *userData;
};

struct BfmeStateFields
{
	UnsignedByte m_unreconstructed_00[0x08];
	StateID m_successStateID;					///< retail this+0x08
	StateID m_failureStateID;					///< retail this+0x0c
	std::vector<BfmeTransitionInfo> m_transitions;	///< retail this+0x10
	StateMachine *m_machine;					///< retail this+0x1c
};

// counter shared with the tracked friend_checkForTransitions/friend_checkForSleepTransitions
// definitions is intentionally NOT shared here -- this twin owns its own static,
// matching how the sibling sleep-transitions twin already does the same.
static Int checkfortransitionsnum_twin = 0;

struct StIncrementerTwin
{
	Int &num;
	StIncrementerTwin(Int &n) : num(n) { ++num; }
	~StIncrementerTwin() { --num; }
};

} // namespace

// ?friend_checkForTransitions@State@@QAE?AW4StateReturnType@@W42@@Z
StateReturnType State::friend_checkForTransitions( StateReturnType status )
{
	StIncrementerTwin inc(checkfortransitionsnum_twin);
	if (checkfortransitionsnum_twin >= 20)
	{
		DEBUG_CRASH(("checkfortransitionsnum is > 20"));
		return STATE_FAILURE;
	}

	DEBUG_ASSERTCRASH(!IS_STATE_SLEEP(status), ("Please handle sleep states prior to this"));

	BfmeStateFields *self = (BfmeStateFields *)this;

	// handle transitions
	switch( status )
	{
		case STATE_SUCCESS:
			// check if machine should exit
			if (self->m_successStateID == EXIT_MACHINE_WITH_SUCCESS)
			{
				self->m_machine->internalSetState( MACHINE_DONE_STATE_ID );
				return STATE_SUCCESS;
			}
			else if (self->m_successStateID == EXIT_MACHINE_WITH_FAILURE)
			{
				self->m_machine->internalSetState( MACHINE_DONE_STATE_ID );
				return STATE_FAILURE;
			}

			// move to new state
			return self->m_machine->internalSetState( self->m_successStateID );

		case STATE_FAILURE:
			// check if machine should exit
			if (self->m_failureStateID == EXIT_MACHINE_WITH_SUCCESS)
			{
				self->m_machine->internalSetState( MACHINE_DONE_STATE_ID );
				return STATE_SUCCESS;
			}
			else if (self->m_failureStateID == EXIT_MACHINE_WITH_FAILURE)
			{
				self->m_machine->internalSetState( MACHINE_DONE_STATE_ID );
				return STATE_FAILURE;
			}

			// move to new state
			return self->m_machine->internalSetState( self->m_failureStateID );

		case STATE_CONTINUE:

			// check transition condition list
			if (!self->m_transitions.empty())
			{
				for(std::vector<BfmeTransitionInfo>::const_iterator it = self->m_transitions.begin(); it != self->m_transitions.end(); ++it)
				{
					if (it->test( this, it->userData ))
					{
						// test returned true, change to associated state

						// check if machine should exit
						if (it->toStateID == EXIT_MACHINE_WITH_SUCCESS)
						{
							return STATE_SUCCESS;
						}
						else if (it->toStateID == EXIT_MACHINE_WITH_FAILURE)
						{
							return STATE_FAILURE;//Lorenzen wants to know why...
						}

						// move to new state
						return self->m_machine->internalSetState( it->toStateID );
					}
				}
			}
			break;
	}

	// the machine keeps running
	return STATE_CONTINUE;
}
