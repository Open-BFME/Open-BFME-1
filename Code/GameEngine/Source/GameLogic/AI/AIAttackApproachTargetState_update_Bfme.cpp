// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00182EA0: AIAttackApproachTargetState::update.
//
// This BFME state keeps the state-machine and AI fields at different offsets
// from the vendored Zero Hour declarations.  The small views below keep the
// retail layout local to this body while the known ILT thunks preserve the
// original call sites.

typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2
};

enum WhichTurretType
{
	TURRET_INVALID = -1
};

class Object;

class ThingTemplate
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;
};

struct StateMachine
{
	unsigned char m_unreconstructed_000[0x10];
	Object *m_owner;

	Object *getGoalObject();
};

class AIUpdateInterface
{
	unsigned char m_unreconstructed_000[0x335];

public:
	Bool m_bfmeTargeting;

	WhichTurretType getWhichTurretForCurWeapon() const;
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void setTurretTargetObject(WhichTurretType turret, Object *target,
		Bool forceAttacking);
};

class Object
{
	unsigned char m_unreconstructed_000[0x204];

public:
	AIUpdateInterface *m_ai;

	Bool isMobile() const;
};

class AIAttackApproachTargetState
{
	unsigned char m_unreconstructed_000[0x18];
	StateMachine *m_machine;
	unsigned char m_unreconstructed_020[0x50];
	Bool m_follow;
	Bool m_isAttackingObject;
	unsigned char m_unreconstructed_072;
	Bool m_isInitialApproach;
	Bool m_isForceAttacking;
	StateReturnType updateInternal();

public:
	virtual StateReturnType update();
};

StateReturnType AIAttackApproachTargetState::update()
{
	StateReturnType code = updateInternal();
	Object *source = m_machine->m_owner;
	AIUpdateInterface *ai = source->m_ai;

	if (m_follow && m_isAttackingObject)
	{
		Object *victim = m_machine->getGoalObject();
		if (victim && source->isMobile()
			&& !((Thing *)victim)->getTemplate()->isKindOf(KINDOF_IMMOBILE))
		{
			if (code != STATE_CONTINUE)
				m_isInitialApproach = false;
			code = STATE_CONTINUE;
		}
	}

	if (m_isInitialApproach)
	{
		WhichTurretType turret = ai->getWhichTurretForCurWeapon();
		if (turret != TURRET_INVALID)
		{
			Object *temporaryTarget = ai->getNextMoodTarget(true, false);
			if (temporaryTarget)
			{
				ai->setTurretTargetObject(turret, temporaryTarget, m_isForceAttacking);
				ai->m_bfmeTargeting = true;
			}
		}
	}

	return code;
}
