// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?friend_onCondition@State@@: Code/GameEngine/Source/Common/StateMachine.cpp
// Open-BFME7: State::friend_onCondition, retail 0x000A1FB0, zh_sweep packet
// 000a1fb0.
//
// The Zero Hour body is a single push_back and needed no change at all.
// Compiled inside StateMachine.cpp it reproduced 99 of the 102 bytes; the
// three that differed were the three member displacements, each four too
// large -- [ecx+0x18]/[ecx+0x1c] and `add ecx,0x14` against retail's
// [ecx+0x14]/[ecx+0x18] and `add ecx,0x10`. Same uniform four-byte shift
// State_friend_checkForSleepTransitions_Thunk.cpp already recorded from the
// other side of the class, so this is one leading member fewer than the
// vendored class has, not a reordering. Its own TU rather than shifting the
// seven other rows StateMachine.cpp owns.
//
// TransitionInfo stays 12 bytes -- retail writes exactly three dwords into
// the stack temp and steps _M_finish by 0x0C -- so STATE_MACHINE_DEBUG's
// description field is absent from this build while the constructor still
// takes the argument. The vector is the real STLport one, because the whole
// point of the body is the shape push_back inlines to: the capacity test
// against _M_end_of_storage, the null-check before the three stores, and the
// _M_insert_overflow call on the full path.

#include <vector>

typedef unsigned int StateID;

class State;
class StateMachine;

typedef bool (*StateTransFuncPtr)( State *state, void *userData );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	void friend_onCondition( StateTransFuncPtr test, StateID toStateID, void *userData, const char *description = 0 );

private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
	struct TransitionInfo
	{
		StateTransFuncPtr	test;								///< +0x00
		StateID				toStateID;							///< +0x04
		void				*userData;							///< +0x08

		TransitionInfo(StateTransFuncPtr t, StateID id, void *ud, const char *desc) :
			test(t),
			toStateID(id),
			userData(ud)
		{ }
	};

	virtual void placeholder( void ) = 0;						///< vptr at +0x00

	StateID m_ID;												///< +0x04
	StateID m_successStateID;									///< +0x08
	StateID m_failureStateID;									///< +0x0C
	std::vector<TransitionInfo> m_transitions;					///< +0x10, three pointers
	StateMachine *m_machine;									///< +0x1C
};

// ?friend_onCondition@State@@QAEXP6A_NPAV1@PAX@ZI1PBD@Z
void State::friend_onCondition( StateTransFuncPtr test, StateID toStateID, void *userData, const char *description )
{
	m_transitions.push_back(TransitionInfo(test, toStateID, userData, description));
}
