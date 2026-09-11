// ?checkQueuedTeams@AIPlayer@@MAEXXZ
// partial score=0.9 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/objectdlink

// BFME's AIPlayer::checkQueuedTeams, retail RVA 0x00161E20 (697 bytes).
// The queue and prototype offsets are BFME witnesses; the Zero Hour twin is
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class ScriptAction;
class Script;
class Team;
class TeamInQueue;

// The local output object is the BFME AsciiString ABI whose release body is
// already landed at 0x00887940.  The private base and inline forwarding
// destructor preserve the retail by-value string construction shape.
template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;
	friend class BFMERetailUnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() {}
};

class BFMERetailUnicodeString : private StringBase<char>
{
public:
	BFMERetailUnicodeString() : StringBase<char>() {}
	~BFMERetailUnicodeString() {}
};

class Script
{
public:
	ScriptAction *getAction() const
	{
		return *(ScriptAction **)((const char *)this + 0x20);
	}
};

class ScriptEngine
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24();
	virtual void friend_executeAction(BFMERetailUnicodeString *outName,
		ScriptAction *action, Team *team);
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52();
virtual Script *findScriptByName(BFMERetailAsciiString *teamName,
        BFMERetailAsciiString *scriptName, BFMERetailUnicodeString *outName);

	void clearTeamFlags();
};

extern ScriptEngine *TheScriptEngine;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class TeamTemplateInfo
{
public:
	unsigned char m_pad[0x13c];
	Int m_initialIdleFrames;
	unsigned char m_pad140[0x180 - 0x140];
	BFMERetailAsciiString m_productionCondition;
	Bool m_executeActions;
};

class TeamPrototypeProductionView
{
public:
	unsigned char m_pad[0x1e8];
	BFMERetailAsciiString m_productionCondition;
	Bool m_executeActions;
};

class TeamPrototype
{
public:
	void *m_vptr;
	void *m_factory;
	void *m_owner;
	Int m_id;
	BFMERetailAsciiString m_name;
	unsigned char m_pad14[0x1a4 - 0x14];
	Int m_initialIdleFrames;
	unsigned char m_pad1a8[0x1e8 - 0x1a8];
	BFMERetailAsciiString m_productionCondition;
	Bool m_executeActions;

	TeamTemplateInfo *getTemplateInfo()
	{
		return (TeamTemplateInfo *)((char *)this + 0x68);
	}

        TeamPrototypeProductionView *getProductionView()
        {
                return (TeamPrototypeProductionView *)this;
        }

};

static BFMERetailAsciiString *rva00161e20_teamName(TeamPrototype *prototype)
{
        if (prototype == 0)
                return (BFMERetailAsciiString *)0x01336e50;
        return &prototype->m_name;
}

class Rva00161E20ObjectIterator
{
public:
	typedef BfmeGetNextTeamMemberFunc GetNextFunc;

	Rva00161E20ObjectIterator(Object *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }

private:
	Object *m_cur;
	GetNextFunc m_getNext;
};

class Team
{
public:
	void *m_vptr;
	TeamPrototype *m_proto;
	void *m_id;
	Object *m_head;

	TeamPrototype *getPrototype() const { return m_proto; }

	Rva00161E20ObjectIterator iterate_TeamMemberList() const
	{
		return Rva00161E20ObjectIterator(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class WorkOrder
{
public:
	void *m_vptr;
	void *m_thing;
	Int m_factoryID;
	WorkOrder *m_next;
	Int m_numCompleted;
	Int m_numRequired;
	Bool m_required;
};

class TeamInQueue
{
public:
	virtual ~TeamInQueue();

	Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_prevReady || m_nextReady;
	}

	void dlink_prependTo_TeamReadyQueue(TeamInQueue **pListHead)
	{
		m_nextReady = *pListHead;
		if (*pListHead)
			(*pListHead)->m_prevReady = this;
		*pListHead = this;
	}
	TeamInQueue *next();

	Bool isBuildTimeExpired()
	{
		if (m_team->getPrototype()->getTemplateInfo()->m_initialIdleFrames < 1)
			return false;
		if (TheGameLogic->getFrame() >
			m_frameStarted +
				m_team->getPrototype()->getTemplateInfo()->m_initialIdleFrames)
			return true;
		return false;
	}

	Bool isAllBuilt()
	{
		WorkOrder *order;
		Bool stillBuilding = false;
		for (order = m_workOrders; order; order = order->m_next)
		{
			if (order->m_numRequired > order->m_numCompleted)
				stillBuilding = true;
		}
		return !stillBuilding;
	}

	Bool isMinimumBuilt()
	{
		WorkOrder *order;
		for (order = m_workOrders; order; order = order->m_next)
		{
			Int count = order->m_numCompleted;
			if (order->m_factoryID != 0)
				++count;
			if (order->m_numRequired > count && order->m_required)
				return false;
		}
		return true;
	}

	Bool areBuildsComplete()
	{
		WorkOrder *order;
		for (order = m_workOrders; order; order = order->m_next)
		{
			if (order->m_factoryID != 0)
				return false;
		}
		return true;
	}

	void disband();

	TeamInQueue *m_prevBuild;
	TeamInQueue *m_nextBuild;
	TeamInQueue *m_prevReady;
	TeamInQueue *m_nextReady;
	WorkOrder *m_workOrders;
	Bool m_priorityBuild;
	char m_pad19[3];
	Team *m_team;
	char m_pad20[4];
	UnsignedInt m_frameStarted;
};

class TeamInQueueIterator
{
public:
	typedef TeamInQueue *(TeamInQueue::*GetNextFunc)();

	TeamInQueueIterator(TeamInQueue *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

	Bool done() const { return m_cur == 0; }
	TeamInQueue *cur() const { return m_cur; }

private:
	TeamInQueue *m_cur;
	GetNextFunc m_getNext;
};

class Rva00160740Node
{
public:
	unsigned char m_pad[4];
	Rva00160740Node *m_next;
	Rva00160740Node *m_prev;
};

class Rva00160740
{
public:
	void remove(Rva00160740Node *node);
};

class Rva000EC960FlagUpdate
{
public:
	void update(unsigned char enabled);
};

class Rva00161E20HighSlots
{
public:
	virtual void s000(); virtual void s004(); virtual void s008(); virtual void s00c();
	virtual void s010(); virtual void s014(); virtual void s018(); virtual void s01c();
	virtual void s020(); virtual void s024(); virtual void s028(); virtual void s02c();
	virtual void s030(); virtual void s034(); virtual void s038(); virtual void s03c();
	virtual void s040(); virtual void s044(); virtual void s048(); virtual void s04c();
	virtual void s050(); virtual void s054(); virtual void s058(); virtual void s05c();
	virtual void s060(); virtual void s064(); virtual void s068(); virtual void s06c();
	virtual void s070(); virtual void s074(); virtual void s078(); virtual void s07c();
	virtual void s080(); virtual void s084(); virtual void s088(); virtual void s08c();
	virtual void s090(); virtual void s094(); virtual void s098(); virtual void s09c();
	virtual void s0a0(); virtual void s0a4(); virtual void s0a8(); virtual void s0ac();
	virtual void s0b0(); virtual void s0b4(); virtual void s0b8(); virtual void s0bc();
	virtual void s0c0(); virtual void s0c4(); virtual void s0c8(); virtual void s0cc();
	virtual void s0d0(); virtual void s0d4(); virtual void s0d8(); virtual void s0dc();
	virtual void s0e0(); virtual void s0e4(); virtual void s0e8(); virtual void s0ec();
	virtual void s0f0(); virtual void s0f4(); virtual void s0f8(); virtual void s0fc();
	virtual void s100(); virtual void s104(); virtual void s108(); virtual void s10c();
	virtual void s110(); virtual void s114(); virtual void s118(); virtual void s11c();
	virtual void s120(); virtual void s124(); virtual void s128(); virtual void s12c();
	virtual void s130(); virtual void s134(); virtual void s138(); virtual void s13c();
	virtual void s140(); virtual void s144(); virtual void s148(); virtual void s14c();
	virtual void s150(); virtual void s154(); virtual void s158(); virtual void s15c();
	virtual void s160(); virtual void s164(); virtual void s168(); virtual void s16c();
	virtual void s170(); virtual void s174(); virtual void s178(); virtual void s17c();
};

class AIUpdateInterface : public Rva00161E20HighSlots
{
public:
	virtual Bool isIdle() const = 0;
};

struct Rva00161E20ObjectAIView
{
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

class Rva00161E20AIPlayer
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10();
	virtual Bool isSkirmishAI();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();

	TeamInQueueIterator iterate_TeamBuildQueue() const
	{
		return TeamInQueueIterator(m_buildQueueHead, &TeamInQueue::next);
	}

	void removeFrom_TeamBuildQueue(TeamInQueue *team)
	{
		((Rva00160740 *)this)->remove((Rva00160740Node *)team);
	}

	void removeFrom_TeamBuildQueueInline(TeamInQueue *team)
	{
		if (m_buildQueueHead != team && team->m_prevBuild == 0 &&
			team->m_nextBuild == 0)
			return;
		if (team->m_nextBuild)
			team->m_nextBuild->m_prevBuild = team->m_prevBuild;
		if (team->m_prevBuild)
			team->m_prevBuild->m_nextBuild = team->m_nextBuild;
		else
			m_buildQueueHead = team->m_nextBuild;
		team->m_prevBuild = 0;
		team->m_nextBuild = 0;
	}

	void prependTo_TeamReadyQueue(TeamInQueue *team)
	{
		if (!team->dlink_isInList_TeamReadyQueue(&m_readyQueueHead))
			team->dlink_prependTo_TeamReadyQueue(&m_readyQueueHead);
	}

protected:
	// ?checkQueuedTeams@AIPlayer@@MAEXXZ
	virtual void checkQueuedTeams();

private:
	TeamInQueue *m_buildQueueHead;
	TeamInQueue *m_readyQueueHead;
};

// ?checkQueuedTeams@AIPlayer@@MAEXXZ
void Rva00161E20AIPlayer::checkQueuedTeams()
{
	{
		for (TeamInQueueIterator iter = iterate_TeamBuildQueue();
			!iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team && team->isBuildTimeExpired())
			{
				if (team->isMinimumBuilt())
				{
					if (team->areBuildsComplete())
					{
						removeFrom_TeamBuildQueue(team);
						((Rva000EC960FlagUpdate *)team->m_team)->update(0);
						prependTo_TeamReadyQueue(team);
					}
					else
						continue;
				}
				else
				{
					removeFrom_TeamBuildQueue(team);
					team->disband();
					delete team;
					if (isSkirmishAI())
						TheScriptEngine->clearTeamFlags();
				}
				iter = iterate_TeamBuildQueue();
			}
		}
	}

	{
		for (TeamInQueueIterator iter = iterate_TeamBuildQueue();
			!iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			if (team && team->isAllBuilt())
			{
				removeFrom_TeamBuildQueueInline(team);
				((Rva000EC960FlagUpdate *)team->m_team)->update(0);
				prependTo_TeamReadyQueue(team);
				iter = iterate_TeamBuildQueue();
				continue;
			}

			Bool anyIdle = false;
			for (Rva00161E20ObjectIterator objIter =
				team->m_team->iterate_TeamMemberList();
				!objIter.done(); objIter.advance())
			{
				Object *obj = objIter.cur();
				AIUpdateInterface *ai =
					((Rva00161E20ObjectAIView *)obj)->m_ai;
				if (obj && ai && ai->isIdle())
					anyIdle = true;
			}

			if (anyIdle)
			{
				if (team->m_team->getPrototype()->m_executeActions)
				{
                                        BFMERetailUnicodeString outName;
                                        TeamPrototype *prototype = team->m_team->getPrototype();
        BFMERetailAsciiString *teamName =
                rva00161e20_teamName(prototype);
        BFMERetailAsciiString *condition =
                &prototype->m_productionCondition;
        Script *script = TheScriptEngine->findScriptByName(
                teamName,
                condition,
                &outName);
				if (script)
					TheScriptEngine->friend_executeAction(
						&outName, script->getAction(), team->m_team);
				}
			}
		}
	}
}
