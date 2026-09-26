// cl: /DNDEBUG /MD /EHsc
// Authentic body from GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp.

typedef bool Bool;

enum WhichTurretType { TURRET_INVALID = -1 };
enum PlayerType { PLAYER_COMPUTER = 1 };
enum CrushSquishTestType { TEST_TYPE_2 = 2 };
enum KindOfType { KINDOF_DONT_AUTO_CRUSH_INFANTRY = 0x5b };

class Object;

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }
private:
	unsigned char m_pad000[0x2c];
	PlayerType m_playerType;
};

class ThingTemplate
{
public:
	ThingTemplate *getFinalOverride();
	void *m_vtable;
	ThingTemplate *m_override;
	unsigned char m_pad008[0x495];
	Bool m_hasAI;
};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}
	Bool hasAI() const
	{
		ThingTemplate *finalTemplate = m_template;
		if (finalTemplate && finalTemplate->m_override)
			finalTemplate = finalTemplate->m_override->getFinalOverride();
		return finalTemplate->m_hasAI;
	}
	Object *getContainedBy() const { return m_containedBy; }
	Player *getControllingPlayer() const;
	Bool crushPolicy(Object *victim, CrushSquishTestType test) const;

private:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad008[0x1fc];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x0c];
	Object *m_containedBy;
};

class StateMachine
{
public:
	Object *getGoalObject();
	unsigned char m_pad000[0x10];
	Object *m_owner;
};

class State
{
public:
	Object *getMachineOwner() { return m_machine->m_owner; }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }
private:
	unsigned char m_pad000[0x1c];
	StateMachine *m_machine;
};

struct AIData
{
	unsigned char m_pad000[0x8c];
	Bool m_aiCrushesInfantry;
};

class AI
{
public:
	unsigned char m_pad000[0x14];
	AIData *m_aiData;
};

extern AI *TheAI;

Bool wantToSquishTarget(State *thisState, void *)
{
	Object *obj = thisState->getMachineOwner();
	Object *victim = thisState->getMachineGoalObject();

	if (obj && victim)
	{
		if (obj->hasAI())
		{
			if (victim->getContainedBy())
				return false;
			if (obj->getAI() && obj->getAI()->getWhichTurretForCurWeapon() != TURRET_INVALID)
			{
				if (TheAI->m_aiData->m_aiCrushesInfantry)
				{
					if (obj->getControllingPlayer() && obj->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
					{
						if (obj->crushPolicy(victim, TEST_TYPE_2))
						{
							if (!obj->isKindOf(KINDOF_DONT_AUTO_CRUSH_INFANTRY))
								return true;
						}
					}
				}
			}
		}
	}

	return false;
}
