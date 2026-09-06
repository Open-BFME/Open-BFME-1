// cl: /DNDEBUG /MD /EHsc
// stlport
// BFME layout reconstruction of AITNGuardIdleState::update at 0x0018A910.

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
class ContainModuleInterface;

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

class AIData
{
public:
	unsigned char m_fields[0x40];
	UnsignedInt m_guardEnemyScanRate;
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
	const std::list<ObjectID> *getContainerList() const
	{
		return &m_tunnelIDs;
	}

private:
	void *m_snapshotVtable;
	std::list<ObjectID> m_tunnelIDs;
};

class Player
{
public:
	TunnelTracker *getTunnelSystem()
	{
		return *(TunnelTracker **)((unsigned char *)this + 0x22c);
	}
};

class ExitInterface
{
public:
	virtual bool isExitBusy();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void exitObjectInAHurry(Object *object);
};

class ContainModuleInterface
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
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual ExitInterface *getContainExitInterface();
};

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

	void *getContainedBy() const
	{
		return *(void **)((const unsigned char *)this + 0x214);
	}

	ContainModuleInterface *getContain() const
	{
		return *(ContainModuleInterface **)((const unsigned char *)this + 0x1fc);
	}
};

class AIUpdateInterface
{
public:
	void friend_setGoalObject(Object *object);

	ObjectID getCrateID() const
	{
		return *(const ObjectID *)((const unsigned char *)this + 0x218);
	}
};

class AITNGuardMachine
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
	virtual void setState(int state);

	unsigned char m_fields04[0x0c];
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

	bool lookForInnerTarget();
};

class AITNGuardIdleState
{
public:
	virtual StateReturnType update();

	unsigned char m_stateFields04[0x18];
	AITNGuardMachine *m_machine;
	unsigned char m_unused20[4];
	UnsignedInt m_nextEnemyScanTime;
};

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

// ?update@AITNGuardIdleState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardIdleState::update()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now < m_nextEnemyScanTime)
		return (StateReturnType)(m_nextEnemyScanTime - now);

	m_nextEnemyScanTime = now + TheAIParseDefinitionAI->getAiData()->m_guardEnemyScanRate;
	m_machine->getOwner()->getAI()->friend_setGoalObject(0);
	Object *owner = m_machine->getOwner();
	AIUpdateInterface *ai = owner->getAI();

	if (ai->getCrateID() != 0)
	{
		m_machine->setState(0x138c);
		return (StateReturnType)(m_nextEnemyScanTime - now);
	}

	if (m_machine->lookForInnerTarget())
	{
		AITNGuardMachine *guardMachine = m_machine;
		Object *nemesis = TheGameLogic->findObjectByID(guardMachine->getNemesisID());
		if (nemesis == 0)
			return (StateReturnType)0;

		if (guardMachine->getOwner()->getContainedBy())
		{
			Object *bestTunnel = findBestTunnel(
				owner->getControllingPlayer(), nemesis->getPosition());
			ExitInterface *goalExitInterface = bestTunnel->getContain()
				? bestTunnel->getContain()->getContainExitInterface() : 0;
			if (goalExitInterface == 0)
				return STATE_FAILURE;
			if (goalExitInterface->isExitBusy())
				return (StateReturnType)0;
			goalExitInterface->exitObjectInAHurry(m_machine->getOwner());
			return (StateReturnType)0;
		}
		return STATE_SUCCESS;
	}

	if (!owner->getContainedBy() &&
		findBestTunnel(owner->getControllingPlayer(), owner->getPosition()))
		return STATE_FAILURE;

	return (StateReturnType)(m_nextEnemyScanTime - now);
}
