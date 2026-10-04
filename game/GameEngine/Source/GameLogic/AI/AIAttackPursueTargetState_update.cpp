// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?update@AIAttackPursueTargetState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// Retail 0x001764E0: AIAttackPursueTargetState::update.

typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WhichTurretType
{
	TURRET_INVALID = -1
};

class Object;

// Opaque holder for the AIUpdate accessors below: retail reaches them through
// incremental-link thunks, so the call sites bind ?j_* and route to this type.
class Rva001764E0AIUpdate
{
};

extern void j_000346a3();
extern void j_00003f58();
extern void j_0001a0e1();

struct Rva001764E0Object
{
	unsigned char m_unreconstructed_000[0x204];
	Rva001764E0AIUpdate *m_ai;
};

struct Rva001764E0StateMachine
{
	unsigned char m_unreconstructed_000[0x10];
	Rva001764E0Object *m_owner;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackPursueTargetState
{
	unsigned char m_unreconstructed_004[0x18];
	Rva001764E0StateMachine *m_machine;
	unsigned char m_unreconstructed_020[0x43];
	Bool m_isInitialApproach;
	Bool m_isForceAttacking;

public:
	virtual StateReturnType update();
};

extern void j_00014ef2();
typedef StateReturnType (__fastcall *AIAttackPursueTargetStateBaseUpdate)(AIAttackPursueTargetState *state);

StateReturnType AIAttackPursueTargetState::update()
{
	StateReturnType code = ((AIAttackPursueTargetStateBaseUpdate)j_00014ef2)(this);
	Rva001764E0Object *source = m_machine->m_owner;
	Rva001764E0AIUpdate *ai = source->m_ai;

	typedef WhichTurretType (Rva001764E0AIUpdate::*GetWhichTurret)() const;
	union { void (*fn)(); GetWhichTurret call; } getWhich={j_000346a3};
	typedef Object *(Rva001764E0AIUpdate::*GetNextMoodTarget)(Bool calledByAI, Bool calledDuringIdle);
	union { void (*fn)(); GetNextMoodTarget call; } getNextMood={j_00003f58};
	typedef void (Rva001764E0AIUpdate::*SetTurretTargetObject)(WhichTurretType turret, Object *targetObject, Bool forceAttacking);
	union { void (*fn)(); SetTurretTargetObject call; } setTurretTarget={j_0001a0e1};

	if (m_isInitialApproach)
	{
		WhichTurretType turret = (ai->*getWhich.call)();
		if (turret != TURRET_INVALID)
		{
			Object *temporaryTarget = (ai->*getNextMood.call)(true, false);
			if (temporaryTarget)
			{
				(ai->*setTurretTarget.call)(turret, temporaryTarget, m_isForceAttacking);
				*((Bool *)((unsigned char *)ai + 0x335)) = true;
			}
		}
	}

	return code;
}
