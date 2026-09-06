// cl: /DNDEBUG /MD /EHsc
// stlport
// BFME layout reconstruction of AITNGuardReturnState::onEnter at 0x0018A870.
// The body is the old BFME return-state path: randomize the next return scan,
// find the nearest tunnel, set the state-machine goal, mirror it to the AI
// module, then enter through AIEnterState.

#include <list>

typedef int ObjectID;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class Player;
class AIUpdateInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	UnsignedInt getFrame() const
	{
		return *(const UnsignedInt *)((const unsigned char *)this + 0x3c);
	}
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData
{
public:
	unsigned char m_fields[0x44];
	UnsignedInt m_guardEnemyReturnScanRate;
};

class AI
{
public:
	unsigned char m_fields[0x14];
	TAiData *m_data;

	TAiData *getAiData()
	{
		return m_data;
	}
};

extern "C" AI *TheAIParseDefinitionAI;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	const std::list<ObjectID> *getContainerList() const
	{
		return &m_tunnelIDs;
	}

private:
	void *m_snapshotVtable;
	std::list<ObjectID> m_tunnelIDs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	TunnelTracker *getTunnelSystem()
	{
		return *(TunnelTracker **)((unsigned char *)this + 0x22c);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;

	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}

	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((const unsigned char *)this + 0x204);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void friend_setGoalObject(Object *obj);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
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
	virtual void setGoalObject(const Object *object);

	Object *getOwner() const
	{
		return *(Object **)((const unsigned char *)this + 0x10);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	unsigned char m_fields04[0x18];
	StateMachine *m_machine;
	unsigned char m_fields20[0x2c];
	unsigned char m_adjustDestinations;
};

class AIEnterState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	UnsignedInt m_entryToClear;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AITNGuard.h
class AITNGuardReturnState : public AIEnterState
{
public:
	virtual StateReturnType onEnter();

	UnsignedInt m_nextReturnScanTime;

	Object *getMachineOwner() const
	{
		return m_machine->getOwner();
	}

	StateMachine *getMachine() const
	{
		return m_machine;
	}
};

// Kept in this TU so MSVC uses the same internal-call shape as the original
// AITNGuard.cpp static helper (the canonical helper is matched separately at
// 0x0018A190).
static Object *findBestTunnel(Player *ownerPlayer, const Coord3D *pos)
{
	if (!ownerPlayer)
		return 0;

	TunnelTracker *tunnels = *(TunnelTracker **)((unsigned char *)ownerPlayer + 0x22c);
	Object *bestTunnel = 0;
	Real bestDistSqr = 0;
	const std::list<ObjectID> *allTunnels = tunnels->getContainerList();
	std::list<ObjectID>::const_iterator end = allTunnels->end();
	for (std::list<ObjectID>::const_iterator iter = allTunnels->begin(); iter != end; ++iter)
	{
		Object *currentTunnel = TheGameLogic->findObjectByID(*iter);
		if (currentTunnel)
		{
			Real dx = currentTunnel->getPosition()->x - pos->x;
			Real dy = currentTunnel->getPosition()->y - pos->y;
			Real distSqr = dx * dx + dy * dy;
			if (bestTunnel == 0 || distSqr < bestDistSqr)
			{
				bestDistSqr = distSqr;
				bestTunnel = currentTunnel;
			}
		}
	}
	return bestTunnel;
}

// ?onEnter@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardReturnState::onEnter()
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_nextReturnScanTime = now + GetGameLogicRandomValue(
		0,
		TheAIParseDefinitionAI->getAiData()->m_guardEnemyReturnScanRate,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AITNGuard.cpp",
		0x1fc);

	Object *bestTunnel = findBestTunnel(
		getMachineOwner()->getControllingPlayer(),
		getMachineOwner()->getPosition());
	if (bestTunnel == 0)
		return STATE_FAILURE;

	getMachine()->setGoalObject(bestTunnel);
	getMachineOwner()->getAI()->friend_setGoalObject(bestTunnel);
	return AIEnterState::onEnter();
}
