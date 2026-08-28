// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// AIMoveAwayFromRepulsorsState::onExit — BFME retail body at RVA 0x00173EE0 (54B).
//
// Lives in its own TU (same pattern as GameWindowFields / ObjectFields /
// LocomotorAccessors) because the body needs the BFME State/StateMachine
// layout (m_machine@+0x1c, m_owner@+0x10) and Object model-condition word
// at +0x118. AIStates.cpp still resolves the ZH dual-vtable State header
// (m_machine@+0x20), so converting this leaf there would either fail the
// byte match or disturb every other matched AIStates row.
//
// Identity (certified packet 357):
//   constructor-owned vtable 0x00C9A368 slot 5 -> thunk -> 0x00173EE0
//   calls AIInternalMoveToState::onExit @0x00029311, then clears bit 0x1000
//   (MODELCONDITION_PANICKING) at Object+0x118 and notifies via 0x0002191D.
//
// Source semantics match AIStates.cpp's ZH body:
//   AIInternalMoveToState::onExit(status);
//   Object *obj = getMachineOwner();
//   if (obj) obj->clearModelConditionState(MODELCONDITION_PANICKING);

typedef unsigned int UnsignedInt;

enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};

// BFME Object leaf used only for the model-condition word at +0x118 and the
// post-clear notify thunk (retail ILT 0x2191d -> body 0x1be1c0).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// Inline clear of MODELCONDITION_PANICKING (bit 0x1000). Retail call sites
	// of clearModelConditionState(PANICKING) compile to this exact shape:
	// load [this+0x118], test bit, clear, notify — not a push-enum + call.
	void clearModelConditionStatePanicking()
	{
		UnsignedInt bits = m_modelConditionWord;
		if (bits & 0x1000u)
		{
			m_modelConditionWord = bits & ~0x1000u;
			notifyModelConditionChanged();
		}
	}

	// Pin target: ILT thunk 0x0002191D (body FUN 0x001BE1C0).
	void notifyModelConditionChanged();

private:
	unsigned char _bfme_pad_000[0x118];
	UnsignedInt m_modelConditionWord; // @+0x118
};

// BFME StateMachine: single vptr (Snapshot base dropped, same lesson as
// Locomotor) + 12-byte map storage => m_owner @+0x10.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() { return m_owner; }

private:
	virtual void _bfme_sm_vslot0() {}
	void *_bfme_stateMap[3]; // 12B STLport map body
	Object *m_owner;         // @+0x10
};

// BFME State: single vptr + 3x StateID + 12B vector => m_machine @+0x1c.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	Object *getMachineOwner() { return m_machine->getOwner(); }

private:
	virtual void _bfme_state_vslot0() {}
	UnsignedInt m_ID;
	UnsignedInt m_successStateID;
	UnsignedInt m_failureStateID;
	void *_bfme_transitions[3]; // 12B STLport vector body
	StateMachine *m_machine;    // @+0x1c
};

// Base whose onExit is a matched external (REL32 -> 0x00029311).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAwayFromRepulsorsState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@AIMoveAwayFromRepulsorsState@@UAEXW4StateExitType@@@Z
void AIMoveAwayFromRepulsorsState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Object *obj = getMachineOwner();
	if (obj)
	{
		obj->clearModelConditionStatePanicking();
	}
}
