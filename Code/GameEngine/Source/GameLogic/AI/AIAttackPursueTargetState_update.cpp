// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

class Rva001764E0AIUpdate
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void setTurretTargetObject(WhichTurretType turret, Object *target, Bool forceAttacking);
};

#pragma comment(linker, "/alternatename:?getWhichTurretForCurWeapon@Rva001764E0AIUpdate@@QBE?AW4WhichTurretType@@XZ=?j_000346a3@@YAXXZ")
#pragma comment(linker, "/alternatename:?getNextMoodTarget@Rva001764E0AIUpdate@@QAEPAVObject@@_N0@Z=?j_00003f58@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTurretTargetObject@Rva001764E0AIUpdate@@QAEXW4WhichTurretType@@PAVObject@@_N@Z=?j_0001a0e1@@YAXXZ")

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

	if (m_isInitialApproach)
	{
		WhichTurretType turret = ai->getWhichTurretForCurWeapon();
		if (turret != TURRET_INVALID)
		{
			Object *temporaryTarget = ai->getNextMoodTarget(true, false);
			if (temporaryTarget)
			{
				ai->setTurretTargetObject(turret, temporaryTarget, m_isForceAttacking);
				*((Bool *)((unsigned char *)ai + 0x335)) = true;
			}
		}
	}

	return code;
}
