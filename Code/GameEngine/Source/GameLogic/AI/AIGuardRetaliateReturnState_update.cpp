// cl: /DNDEBUG /MD
// readable body of ?update@AIGuardRetaliateReturnState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIGuardRetaliate.cpp
// AIGuardRetaliateReturnState::update — retail 0x0015EF50 (226B).
// ZH ReturnState::update plus inlined hasAttackedMeAndICanReturnFire and
// BFME melee-target resolve (testStatus 0x25 then bfmeResolveMeleeTarget).

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum Relationship
{
	ENEMIES = 0
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object;

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual ObjectID getClearableLastAttacker() const;
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;
	Bool isAbleToAttack() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType t, const Object *target, CommandSourceType cmd) const;
	Bool testStatus(int status) const;
	Object *bfmeResolveMeleeTarget(int index);
	Bool isEffectivelyDead() const { return (m_deadFlags & 1) != 0; }
	ObjectID getID() const { return m_id; }
	BodyModuleInterface *getBodyModule() const { return m_body; }

	unsigned char m_pad000[0x74];
	ObjectID m_id;
	unsigned char m_pad078[0x200 - 0x78];
	BodyModuleInterface *m_body;
	unsigned char m_pad204[0x344 - 0x204];
	unsigned char m_deadFlags;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	unsigned char m_pad000[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class AIData
{
public:
	unsigned char m_pad000[0x44];
	UnsignedInt m_guardEnemyReturnScanRate;
};

class AI
{
public:
	AIData *getAiData() { return m_aiData; }

	unsigned char m_pad000[0x14];
	AIData *m_aiData;
};

extern AI *TheAI;

class AIGuardRetaliateMachine
{
public:
	// thiscall: ecx = this (machine at State+0x1C). Bool in al.
	// ILT 0x0003F71F (j_0003f71f) -> body 0x0015ECE0.
	Bool lookForInnerTarget();

	unsigned char m_pad000[0x10];
	Object *m_owner;
	unsigned char m_pad014[0x50 - 0x14];
	ObjectID m_nemesisID;
};

class AIInternalMoveToState
{
public:
	// Retail ReturnState vtable 0x01096520: update is slot 6.
	virtual ~AIInternalMoveToState();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual StateReturnType update();
};

class AIGuardRetaliateReturnState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();

	unsigned char m_pad004[0x18];
	AIGuardRetaliateMachine *m_machine;
	unsigned char m_pad020[0x50 - 0x20];
	UnsignedInt m_nextReturnScanTime;
};

StateReturnType AIGuardRetaliateReturnState::update()
{
	Object *obj = m_machine->m_owner;
	BodyModuleInterface *bmi = obj ? obj->getBodyModule() : 0;
	if (obj && bmi)
	{
		Object *target = TheBfmeGameLogic->findObjectByID(bmi->getClearableLastAttacker());
		if (target && !target->isEffectivelyDead() &&
			obj->getRelationship(target) == ENEMIES &&
			obj->isAbleToAttack())
		{
			CanAttackResult result = obj->getAbleToAttackSpecificObject(ATTACK_NEW_TARGET, target, CMD_FROM_AI);
			if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
			{
				if (target->testStatus(0x25))
				{
					Object *resolved = target->bfmeResolveMeleeTarget(0);
					if (resolved)
						target = target->bfmeResolveMeleeTarget(0);
				}
				m_machine->m_nemesisID = target->getID();
				return STATE_FAILURE;
			}
		}
	}

	UnsignedInt now = TheBfmeGameLogic->m_frame;
	if (now >= m_nextReturnScanTime)
	{
		m_nextReturnScanTime = now + TheAI->getAiData()->m_guardEnemyReturnScanRate;
		if (m_machine->lookForInnerTarget())
			return STATE_FAILURE;
	}

	return AIInternalMoveToState::update();
}
