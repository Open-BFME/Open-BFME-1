// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// AIPlayer::onUnitProduced, retail 0x00168320 (595 bytes), AIPlayer vtable slot 7.
// Zero Hour body plus BFME's bfmeBlocksFormationRefresh test before the goal-position push.
// Build-list, team-queue and template views keep only the offsets this body reads.

#include <vector>
#include <hash_map>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef int ObjectID;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};

// Mask of the kind-of bit retail tests at ThingTemplate+0xC8.
enum KindOfType
{
	KINDOF_DOZER = 0x4000
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
	unsigned char m_pad08[0xc8 - 0x08];
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
	UnsignedInt m_kindOf;
};

template <class T> class OVERRIDE
{
public:
	operator const T *() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

class Thing
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;

	const ThingTemplate *getTemplate() const { return m_template; }

	Bool isKindOf(KindOfType kind) const
	{
		return (getTemplate()->m_kindOf & kind) != 0;
	}

	OVERRIDE<ThingTemplate> m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0x204 - 0x78];
	void *m_ai;
};

class Team;

class Object : public Thing
{
public:
	virtual void setTeam(Team *team);

	ObjectID getID() const { return m_id; }
	class AIUpdateInterface *getAIUpdateInterface() const { return (class AIUpdateInterface *)m_ai; }
};

class StateMachine
{
public:
	const Coord3D *getGoalPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x24);
	}
};

class AICommandInterface
{
public:
	void aiFollowExitProductionPath(const std::vector<Coord3D> *path,
		Object *ignoreObject, CommandSourceType source);
	void aiDock(Object *object, CommandSourceType source);

private:
	unsigned char m_subobject;
};

#define AIUPDATE_SLOT(n) virtual void slot##n() = 0;
class AIUpdatePrimary
{
public:
	AIUPDATE_SLOT(000) AIUPDATE_SLOT(004) AIUPDATE_SLOT(008)
	AIUPDATE_SLOT(00c) AIUPDATE_SLOT(010) AIUPDATE_SLOT(014)
	AIUPDATE_SLOT(018) AIUPDATE_SLOT(01c) AIUPDATE_SLOT(020)
	AIUPDATE_SLOT(024) AIUPDATE_SLOT(028) AIUPDATE_SLOT(02c)
	AIUPDATE_SLOT(030) AIUPDATE_SLOT(034) AIUPDATE_SLOT(038)
	AIUPDATE_SLOT(03c) AIUPDATE_SLOT(040) AIUPDATE_SLOT(044)
	AIUPDATE_SLOT(048) AIUPDATE_SLOT(04c) AIUPDATE_SLOT(050)
	AIUPDATE_SLOT(054) AIUPDATE_SLOT(058) AIUPDATE_SLOT(05c)
	AIUPDATE_SLOT(060) AIUPDATE_SLOT(064) AIUPDATE_SLOT(068)
	AIUPDATE_SLOT(06c) AIUPDATE_SLOT(070) AIUPDATE_SLOT(074)
	AIUPDATE_SLOT(078) AIUPDATE_SLOT(07c) AIUPDATE_SLOT(080)
	AIUPDATE_SLOT(084) AIUPDATE_SLOT(088) AIUPDATE_SLOT(08c)
	AIUPDATE_SLOT(090) AIUPDATE_SLOT(094) AIUPDATE_SLOT(098)
	AIUPDATE_SLOT(09c) AIUPDATE_SLOT(0a0) AIUPDATE_SLOT(0a4)
	AIUPDATE_SLOT(0a8) AIUPDATE_SLOT(0ac) AIUPDATE_SLOT(0b0)
	AIUPDATE_SLOT(0b4) AIUPDATE_SLOT(0b8) AIUPDATE_SLOT(0bc)
	AIUPDATE_SLOT(0c0) AIUPDATE_SLOT(0c4) AIUPDATE_SLOT(0c8)
	AIUPDATE_SLOT(0cc) AIUPDATE_SLOT(0d0) AIUPDATE_SLOT(0d4)
	AIUPDATE_SLOT(0d8) AIUPDATE_SLOT(0dc) AIUPDATE_SLOT(0e0)
	AIUPDATE_SLOT(0e4) AIUPDATE_SLOT(0e8) AIUPDATE_SLOT(0ec)
	AIUPDATE_SLOT(0f0) AIUPDATE_SLOT(0f4) AIUPDATE_SLOT(0f8)
	AIUPDATE_SLOT(0fc) AIUPDATE_SLOT(100) AIUPDATE_SLOT(104)
	AIUPDATE_SLOT(108) AIUPDATE_SLOT(10c) AIUPDATE_SLOT(110)
	AIUPDATE_SLOT(114) AIUPDATE_SLOT(118) AIUPDATE_SLOT(11c)
	AIUPDATE_SLOT(120) AIUPDATE_SLOT(124) AIUPDATE_SLOT(128)
	AIUPDATE_SLOT(12c) AIUPDATE_SLOT(130) AIUPDATE_SLOT(134)
	AIUPDATE_SLOT(138) AIUPDATE_SLOT(13c) AIUPDATE_SLOT(140)
	unsigned char m_primaryPad[0x1c];
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void setForceWantingState(Bool forceWanting);
};

class AIUpdateInterface : public AIUpdatePrimary, public AICommandInterface
{
public:
	Bool bfmeBlocksFormationRefresh();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface() = 0;

	StateMachine *getStateMachine() const
	{
		return *(StateMachine *const *)((const char *)this + 0x30);
	}

	const Coord3D *getGoalPosition() const
	{
		return getStateMachine()->getGoalPosition();
	}
};


template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class WorkOrder
{
public:
	void *m_vtable;
	ThingTemplate *m_thing;
	ObjectID m_factoryID;
	WorkOrder *m_next;
	Int m_numCompleted;
	Int m_numRequired;
	Bool m_required;
	Bool m_isResourceGatherer;
};

class TeamInQueue
{
public:
	virtual ~TeamInQueue();

	TeamInQueue *dlink_next_TeamBuildQueue() const;

	TeamInQueue *m_dlinkPreviousBuild;
	TeamInQueue *m_dlinkNextBuild;
	TeamInQueue *m_dlinkPreviousReady;
	TeamInQueue *m_dlinkNextReady;
	WorkOrder *m_workOrders;
	Bool m_priorityBuild;
	unsigned char m_pad19[3];
	Team *m_team;
	TeamInQueue *m_nextTeamInQueue;
	Int m_frameStarted;
	Bool m_sentToStartLocation;
	Bool m_stopQueueing;
	Bool m_reinforcement;
	unsigned char m_pad2b;
	ObjectID m_reinforcementID;
};

class TeamPrototype
{
public:
	unsigned char m_pad00[0x188];
	Coord3D m_homeLocation;
	Bool m_hasHomeLocation;
};

class Team
{
public:
	void *m_vtable;
	TeamPrototype *m_prototype;
	TeamPrototype *getPrototype() const { return m_prototype; }
};

class BuildListInfo
{
public:
	Bool isSupplyBuilding() const { return *(const Bool *)((const char *)this + 0x7c); }
	Int getDesiredGatherers() const { return *(const Int *)((const char *)this + 0x80); }
	Int getCurrentGatherers() const { return *(const Int *)((const char *)this + 0x84); }
	void setCurrentGatherers(Int count) { *(Int *)((char *)this + 0x84) = count; }
	ObjectID getObjectID() const { return *(const ObjectID *)((const char *)this + 0x48); }
	BuildListInfo *getNext() const { return *(BuildListInfo *const *)((const char *)this + 0x2c); }
};

class Player
{
public:
	BuildListInfo *getBuildList() const
	{
		return *(BuildListInfo *const *)((const char *)this + 0x1c0);
	}
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	// Visible but out of line, so MSVC keeps the gatherer count across the call.
	__declspec(noinline) Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

private:
	unsigned char m_pad00[0xb0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class AIPlayerVtable
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
};

class AIPlayer : public AIPlayerVtable
{
public:
	virtual void onUnitProduced(Object *factory, Object *unit);

	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}

	TeamInQueue *m_teamBuildQueue;
	unsigned char m_pad08[4];
	Player *m_player;
	unsigned char m_pad10[0x18 - 0x10];
	Int m_structureTimer;
	unsigned char m_pad1c[4];
	Int m_buildDelay;
	Int m_teamDelay;
	unsigned char m_pad28[0x50 - 0x28];
	ObjectID m_repairDozer;
	unsigned char m_pad54[0x64 - 0x54];
	Bool m_dozerQueuedForRepair;
};

void AIPlayer::onUnitProduced(Object *factory, Object *unit)
{
	Bool found = false;
	Bool supplyTruck = false;

	if (factory == 0)
		return;

	for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		WorkOrder *order;
		if (found)
			break;
		for (order = team->m_workOrders; order; order = order->m_next)
		{
			if (order->m_factoryID == factory->getID() && order->m_numCompleted < order->m_numRequired &&
				unit->getTemplate()->isEquivalentTo(order->m_thing))
			{
				order->m_numCompleted++;
				if (team->m_team)
					unit->setTeam(team->m_team);
				if (team->m_reinforcement)
					team->m_reinforcementID = unit->getID();
				AIUpdateInterface *ai = unit->getAIUpdateInterface();
				if (team->m_team->getPrototype()->m_hasHomeLocation)
				{
					if (ai)
					{
						std::vector<Coord3D> path;
						if (ai->bfmeBlocksFormationRefresh())
							path.push_back(*ai->getGoalPosition());
						path.push_back(team->m_team->getPrototype()->m_homeLocation);
						ai->aiFollowExitProductionPath(&path, 0, CMD_FROM_AI);
					}
				}

				order->m_factoryID = 0;
				if (ai)
				{
					SupplyTruckAIInterface *supplyTruckAI = ai->getSupplyTruckAIInterface();
					if (supplyTruckAI)
					{
						if (order->m_isResourceGatherer)
							supplyTruck = true;
						else
							supplyTruck = false;
						supplyTruckAI->setForceWantingState(supplyTruck);
						if (supplyTruck)
						{
							for (BuildListInfo *info = m_player->getBuildList(); info; info = info->getNext())
							{
								if (info->isSupplyBuilding() && info->getDesiredGatherers() > 0 &&
									info->getDesiredGatherers() > info->getCurrentGatherers())
								{
									Object *obj = TheGameLogic->findObjectByID(info->getObjectID());
									if (obj)
									{
										info->setCurrentGatherers(info->getCurrentGatherers() + 1);
										ai->aiDock(obj, CMD_FROM_PLAYER);
									}
								}
							}
						}
					}
				}
				found = true;
				break;
			}
		}
	}
	if (!supplyTruck && unit->isKindOf(KINDOF_DOZER))
	{
		if (m_dozerQueuedForRepair)
		{
			m_repairDozer = unit->getID();
			m_dozerQueuedForRepair = false;
		}
		else
		{
			m_buildDelay = 0;
			m_structureTimer = 1;
		}
	}

	m_teamDelay = 0;
}

#undef AIUPDATE_SLOT
