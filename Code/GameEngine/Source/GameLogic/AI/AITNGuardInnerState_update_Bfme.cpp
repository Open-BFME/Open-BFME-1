// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME layout reconstruction of AITNGuardInnerState::update at 0x0018A570.

extern "C" void __cdecl _ReadWriteBarrier( void );
#pragma intrinsic(_ReadWriteBarrier)

typedef int ObjectID;

enum StateReturnType
{
	STATE_CONTINUE = 0
};

enum StateExitType
{
	EXIT_RESET = 1
};

class Object;
class Player;

class GameLogic
{
public:
	Object *findObjectByID( ObjectID id );
	unsigned int getFrame() const
	{
		return m_frame;
	}
	unsigned char m_fields[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class AIData
{
public:
	unsigned char m_fields[0x3c];
	unsigned int m_guardChaseUnitFrames;
};

class AI
{
public:
	unsigned char m_fields[0x14];
	AIData *m_data;
	AIData *getAiData()
	{
		return m_data;
	}
};

extern "C" AI *TheAIParseDefinitionAI;

class TunnelTracker
{
public:
	Object *getCurNemesis();
	void updateNemesis( const Object *object );
};

class Player
{
public:
	TunnelTracker *getTunnelSystem() const
	{
		return *(TunnelTracker **)((const unsigned char *)this + 0x22c);
	}
};

class Team
{
public:
	Object *getTeamTargetObject();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Team *getTeam() const
	{
		return *(Team **)((const unsigned char *)this + 0x23c);
	}
	ObjectID getID() const
	{
		return *(const ObjectID *)((const unsigned char *)this + 0x74);
	}
};

class Rva00189E80ObjectVision
{
public:
	Object *query();
};

class StateMachine
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
	virtual void setGoalObject( const Object *object );
};

class AIAttackState
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit( StateExitType status );
	virtual StateReturnType update();

	StateMachine *getMachine() const
	{
		return *(StateMachine **)((const unsigned char *)this + 0x1c);
	}
};

class AITNGuardMachine
{
public:
	unsigned char m_fields[0x10];
	Object *m_owner;
	unsigned char m_machineFields[0x3c];
	ObjectID m_nemesisID;

	Object *getOwner() const
	{
		return m_owner;
	}
	ObjectID getNemesisID() const
	{
		return m_nemesisID;
	}
	void setNemesisID( ObjectID id )
	{
		m_nemesisID = id;
	}
};

class AITNGuardInnerState
{
public:
	virtual StateReturnType update();

	unsigned char m_stateFields[0x18];
	AITNGuardMachine *m_machine;
	unsigned char m_unused[8];
	unsigned int m_attackGiveUpFrame;
	bool m_scanForEnemy;
	unsigned char m_padding[3];
	AIAttackState *m_attackState;

	AITNGuardMachine *getGuardMachine()
	{
		return m_machine;
	}
	Object *getMachineOwner()
	{
		return m_machine->getOwner();
	}
};

StateReturnType AITNGuardInnerState::update()
{
	GameLogic *logic = TheBfmeGameLogic;
	_ReadWriteBarrier();
	AITNGuardMachine *guardMachine = m_machine;
	Object *nemesis = logic->findObjectByID(guardMachine->m_nemesisID);
	Player *ownerPlayer = guardMachine->getOwner()->getControllingPlayer();
	TunnelTracker *tunnels = 0;
	if (ownerPlayer)
	{
		tunnels = ownerPlayer->getTunnelSystem();
	}
	Object *owner = getMachineOwner();
	Object *teamVictim = owner->getTeam()->getTeamTargetObject();
	if (nemesis == 0)
	{
		if (teamVictim)
		{
			getGuardMachine()->setNemesisID(teamVictim->getID());
			_ReadWriteBarrier();
			register AIData *data = TheAIParseDefinitionAI->getAiData();
			m_attackGiveUpFrame = data->m_guardChaseUnitFrames + TheBfmeGameLogic->getFrame();
			return STATE_CONTINUE;
		}
		if (tunnels)
		{
			nemesis = tunnels->getCurNemesis();
			if (nemesis)
			{
				getGuardMachine()->setNemesisID(nemesis->getID());
				_ReadWriteBarrier();
				register AIData *data = TheAIParseDefinitionAI->getAiData();
				m_attackGiveUpFrame = data->m_guardChaseUnitFrames + TheBfmeGameLogic->getFrame();
				return STATE_CONTINUE;
			}
		}
		if (m_scanForEnemy)
		{
			m_scanForEnemy = false;
			nemesis = ((Rva00189E80ObjectVision *)owner)->query();
			if (nemesis)
			{
				m_attackState->onExit(EXIT_RESET);
				m_attackState->getMachine()->setGoalObject(nemesis);
				if (tunnels)
				{
					tunnels->updateNemesis(nemesis);
				}
				return m_attackState->onEnter();
			}
		}
	}
	else
	{
		if (nemesis != teamVictim && teamVictim != 0)
		{
			tunnels->updateNemesis(nemesis);
			getGuardMachine()->setNemesisID(teamVictim->getID());
		}
	}
	return m_attackState->update();
}
