// cl: /DNDEBUG /MD /EHs-c-
// Lift the AIPanicState::onExit __emit thunk to clean C++.
//
// Zero Hour's AIStates.cpp has the two outer steps -- clear the panicking model
// condition on the machine owner, then chain to AIInternalMoveToState::onExit --
// and BFME wraps them in extra work: nothing runs unless bit 0x2000 of the word
// at Object+0x98 is set, a second model condition is cleared, and a kind-of test
// gates one further call.
//
// Retail pins the chain: the state machine is at this+0x1C and its owner at
// machine+0x10. isKindOf and the base onExit were already pinned by other work.
// The two remaining callees are unidentified bodies, so they are declared under
// address-derived names rather than invented ones -- the symbols.csv notes say
// so, and only the addresses are load-bearing.

#include <string.h>

typedef int Int;

enum StateExitType
{
	EXIT_NORMAL = 0
};

enum KindOfType
{
	KINDOF_FIRST = 0
};

enum ModelConditionFlagType
{
	MODELCONDITION_FIRST = 0
};

class ModelConditionFlags
{
public:
	ModelConditionFlags()
	{
		memset( m_bits, 0, sizeof( m_bits ) );
	}

	void set(ModelConditionFlagType bit)
	{
		m_bits[ (unsigned int)bit >> 5 ] |= 1u << ( (unsigned int)bit & 0x1f );
	}

	unsigned int m_bits[ 3 ];
};

class Object;

class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;										///< retail this+0x10
};

class Thing
{
public:
	bool isKindOf(KindOfType) const;						///< ILT thunk at 0x0003251F
};

class Object : public Thing
{
public:
	void clearModelConditionState(ModelConditionFlagType);	///< ILT thunk at 0x00031F7A

	// Unidentified two-argument body at 0x000F20F0, reached via 0x00019C54.
	__declspec(noinline) void unidentified_000F20F0(Int, Int);
	__declspec(noinline) void unidentified_0002181E(const ModelConditionFlags &, Int);

	unsigned char m_unreconstructed_00[0x98];
	unsigned int m_statusBits;								///< retail this+0x98
};

void Object::unidentified_000F20F0(Int index, Int value)
{
	ModelConditionFlags flags;
	flags.set((ModelConditionFlagType)index);
	unidentified_0002181E(flags, value);
}

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);						///< ILT thunk at 0x00029311

	Object *getMachineOwner(void) const { return m_machine->m_owner; }

protected:
	unsigned char m_unreconstructed_04[0x1C - 4];
	StateMachine *m_machine;								///< retail this+0x1C
};

class AIPanicState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

// ?onExit@AIPanicState@@UAEXW4StateExitType@@@Z
void AIPanicState::onExit(StateExitType status)
{
	Object *obj = getMachineOwner();
	if (obj && (obj->m_statusBits & 0x2000))
	{
		obj->clearModelConditionState((ModelConditionFlagType)0x4D);
		obj->clearModelConditionState((ModelConditionFlagType)3);

		if (obj->isKindOf((KindOfType)0x6C))
		{
			obj->unidentified_000F20F0(3, 0);
		}
	}

	AIInternalMoveToState::onExit(status);
}
