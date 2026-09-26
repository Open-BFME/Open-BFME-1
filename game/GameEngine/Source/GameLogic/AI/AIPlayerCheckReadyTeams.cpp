// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?checkReadyTeams@AIPlayer@@MAEXXZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::checkReadyTeams, 0x00162560, 729 bytes (ret at +0x231, the debug
// tail ends in a jmp at +0x2D4, int3 pad after).
// Identity: slot 16 (+0x40) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x0002403C here, the slot Zero Hour's AIPlayer.h gives checkReadyTeams
// (doBaseBuilding 15, checkQueuedTeams 17, doUpgradesAndSkills 19); the body
// is the Zero Hour twin, including the " - team activated." debug line
// (VA 0x010969B4) and the isSkirmishAI slot 11 test before clearTeamFlags.
//
// BFME differences: the team's +0xE7/+0xE6 flag setter at 0x000EC960 is
// called with false for every started team, before the reinforcement test;
// findScriptByName is ScriptEngine slot 53 taking the nullable team name,
// the condition name and an out name (TeamPrototypeScripts.cpp); the debug
// name is the prototype's AsciiString at +0x14, not the +0x10 name.
//
// Layout: AIPlayer ready queue head +0x08; TeamInQueue ready links +0x0C/+0x10
// (AIPlayer_aiPreTeamDestroyThunk.cpp), m_team +0x1C, then the Zero Hour order
// m_nextTeamInQueue +0x20, m_frameStarted +0x24, m_sentToStartLocation +0x28,
// m_stopQueueing +0x29, m_reinforcement +0x2A, m_reinforcementID +0x2C.
// Team: prototype +0x04, member head +0x0C, m_active +0x31, m_created +0x32.
// Object AI +0x204; AIUpdateInterface isIdle slot 96, joinTeam slot 89.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

#define NULL 0
#define TRUE 1
#define FALSE 0

enum { LOGICFRAMES_PER_SECOND = 5 };

extern const AsciiString Rva01336E50EmptyString;

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

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();
#define BFME_VIRTUAL_SLOT10(n) BFME_VIRTUAL_SLOT(n##0) BFME_VIRTUAL_SLOT(n##1) \
	BFME_VIRTUAL_SLOT(n##2) BFME_VIRTUAL_SLOT(n##3) BFME_VIRTUAL_SLOT(n##4) \
	BFME_VIRTUAL_SLOT(n##5) BFME_VIRTUAL_SLOT(n##6) BFME_VIRTUAL_SLOT(n##7) \
	BFME_VIRTUAL_SLOT(n##8) BFME_VIRTUAL_SLOT(n##9)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	BFME_VIRTUAL_SLOT10(0) BFME_VIRTUAL_SLOT10(1) BFME_VIRTUAL_SLOT10(2)
	BFME_VIRTUAL_SLOT10(3) BFME_VIRTUAL_SLOT10(4) BFME_VIRTUAL_SLOT10(5)
	BFME_VIRTUAL_SLOT10(6) BFME_VIRTUAL_SLOT10(7)
	BFME_VIRTUAL_SLOT(80) BFME_VIRTUAL_SLOT(81) BFME_VIRTUAL_SLOT(82)
	BFME_VIRTUAL_SLOT(83) BFME_VIRTUAL_SLOT(84) BFME_VIRTUAL_SLOT(85)
	BFME_VIRTUAL_SLOT(86) BFME_VIRTUAL_SLOT(87) BFME_VIRTUAL_SLOT(88)
	virtual void joinTeam(void);					// slot 89, +0x164
	BFME_VIRTUAL_SLOT(90) BFME_VIRTUAL_SLOT(91) BFME_VIRTUAL_SLOT(92)
	BFME_VIRTUAL_SLOT(93) BFME_VIRTUAL_SLOT(94) BFME_VIRTUAL_SLOT(95)
	virtual Bool isIdle(void) const;				// slot 96, +0x180
};

static inline AIUpdateInterface *bfmeObjectAI(const Object *obj)
{
	return *(AIUpdateInterface * const *)((const char *)obj + 0x204);
}

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return NULL;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return NULL;
		return (*it).second;
	}

private:
	char m_unmodelled000[0x3c];
	UnsignedInt m_frame;						// +0x3C
	char m_unmodelled040[0xb0 - 0x40];
	ObjectPtrHash m_objHash;					// buckets at +0xB4
};

extern GameLogic *TheGameLogic;

struct GlobalData
{
	char m_unmodelled000[0xa88];
	Int m_debugAI;							// +0xA88
};

extern GlobalData *TheGlobalData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class Script
{
public:
	const void *getAction(void) const { return m_action20; }

private:
	char m_unmodelled000[0x20];
	void *m_action20;						// +0x20, ZH getAction()
};

class UnicodeString;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	BFME_VIRTUAL_SLOT10(0) BFME_VIRTUAL_SLOT10(1) BFME_VIRTUAL_SLOT10(2)
	BFME_VIRTUAL_SLOT10(3) BFME_VIRTUAL_SLOT10(4)
	BFME_VIRTUAL_SLOT(50) BFME_VIRTUAL_SLOT(51) BFME_VIRTUAL_SLOT(52)
	virtual Script *findScriptByName(const AsciiString *teamName,
		const AsciiString *scriptName, UnicodeString *outName);	// slot 53, +0xD4

	void clearTeamFlags(void);
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_rva14Name; }

	char m_unmodelled000[0x10];
	AsciiString m_name;						// +0x10
	AsciiString m_rva14Name;					// +0x14
	char m_unmodelled018[0x1e8 - 0x18];
	AsciiString m_productionCondition;				// +0x1E8
	Bool m_executeActions;						// +0x1EC
};

// Out-of-line Team members, opaque in the ledger.
class Rva000EDB30Team
{
public:
	Bool isIdle(void) const;
};

class Rva000EC960FlagUpdate
{
public:
	void update(unsigned char set);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	const TeamPrototype *getPrototype(void) { return m_proto; }
	const AsciiString &getName(void) const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->m_name;
	}
	Bool isIdle(void) const { return ((const Rva000EDB30Team *)this)->isIdle(); }
	void setActive(void) { if (!m_active) { m_created = true; m_active = true; } }
	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList, Object::dlink_next_TeamMemberList);
	}

	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
	char m_unmodelled008[0x0c - 0x08];
	Object *m_dlinkhead_TeamMemberList;				// +0x0C
	char m_unmodelled010[0x31 - 0x10];
	Bool m_active;							// +0x31
	Bool m_created;							// +0x32
};

class WorkOrder;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	virtual ~TeamInQueue();

	TeamInQueue *dlink_next_TeamReadyQueue() const { return m_dlink_TeamReadyQueue_next; }
	Bool dlink_isInList_TeamReadyQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_dlink_TeamReadyQueue_prev || m_dlink_TeamReadyQueue_next;
	}
	void dlink_removeFrom_TeamReadyQueue(TeamInQueue **pListHead)
	{
		if (m_dlink_TeamReadyQueue_next)
			m_dlink_TeamReadyQueue_next->m_dlink_TeamReadyQueue_prev = m_dlink_TeamReadyQueue_prev;
		if (m_dlink_TeamReadyQueue_prev)
			m_dlink_TeamReadyQueue_prev->m_dlink_TeamReadyQueue_next = m_dlink_TeamReadyQueue_next;
		else
			*pListHead = m_dlink_TeamReadyQueue_next;
		m_dlink_TeamReadyQueue_prev = 0;
		m_dlink_TeamReadyQueue_next = 0;
	}
	void deleteInstance(void) { delete this; }

	TeamInQueue *m_dlink_TeamBuildQueue_prev;			// +0x04
	TeamInQueue *m_dlink_TeamBuildQueue_next;			// +0x08
	TeamInQueue *m_dlink_TeamReadyQueue_prev;			// +0x0C
	TeamInQueue *m_dlink_TeamReadyQueue_next;			// +0x10
	WorkOrder *m_workOrders;					// +0x14
	Bool m_priorityBuild;						// +0x18
	Team *m_team;							// +0x1C
	TeamInQueue *m_nextTeamInQueue;					// +0x20
	Int m_frameStarted;						// +0x24
	Bool m_sentToStartLocation;					// +0x28
	Bool m_stopQueueing;						// +0x29
	Bool m_reinforcement;						// +0x2A
	ObjectID m_reinforcementID;					// +0x2C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	BFME_VIRTUAL_SLOT10(0)
	BFME_VIRTUAL_SLOT(10)
	virtual Bool isSkirmishAI(void);				// slot 11, +0x2C
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15)

protected:
	virtual void checkReadyTeams(void);				// slot 16, +0x40

public:
	DLINK_ITERATOR<TeamInQueue> iterate_TeamReadyQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamReadyQueue, &TeamInQueue::dlink_next_TeamReadyQueue);
	}
	void removeFrom_TeamReadyQueue(TeamInQueue *o)
	{
		if (o->dlink_isInList_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue))
			o->dlink_removeFrom_TeamReadyQueue(&m_dlinkhead_TeamReadyQueue);
	}

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;			// +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue;			// +0x08
};

#undef BFME_VIRTUAL_SLOT10
#undef BFME_VIRTUAL_SLOT

void AIPlayer::checkReadyTeams( void )
{
	// See if any ready teams are gathered at their rally point
	{	// needed to scope iter.  silly ms c++.
		for ( DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamReadyQueue(); !iter.done(); iter.advance())
		{
			TeamInQueue *team = iter.cur();
			// If 60 seconds passed, start anyway.
			Bool timeExpired = team->m_frameStarted+60*LOGICFRAMES_PER_SECOND < TheGameLogic->getFrame();
			Bool allIdle=TRUE;
			Bool anyIdle = FALSE;
			if (team->m_reinforcement) {
				Object *obj = TheGameLogic->findObjectByID(team->m_reinforcementID);
				if (obj && bfmeObjectAI(obj)) {
					allIdle = bfmeObjectAI(obj)->isIdle();
					anyIdle = allIdle;
				}
			} else {
				allIdle = team->m_team->isIdle();
				for (DLINK_ITERATOR<Object> iter = team->m_team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
					Object *obj = iter.cur();
					if (bfmeObjectAI(obj) && bfmeObjectAI(obj)->isIdle()) {
						anyIdle = true;
					}
				}
			}
			if (anyIdle && team->m_team->getPrototype()->m_executeActions) {
				const Script *script = TheScriptEngine->findScriptByName(&team->m_team->getName(),
					&team->m_team->getPrototype()->m_productionCondition, NULL);
				if (script && script->getAction()) {
					// we have a start action.  So don't wait for allIdle as the team may be guarding.
					allIdle = true;
				}
			}
			if (timeExpired) allIdle = true;
			if (allIdle) {
				if (!team->m_sentToStartLocation) {
					team->m_sentToStartLocation = true;
				}
				// Start the team up.
				removeFrom_TeamReadyQueue(team);
				((Rva000EC960FlagUpdate *)team->m_team)->update(false);
				if (team->m_reinforcement) {
					Object *obj = TheGameLogic->findObjectByID(team->m_reinforcementID);
					if (obj&&bfmeObjectAI(obj)) {
						bfmeObjectAI(obj)->joinTeam();
					}
				} else {
					// mark our completed team as "active" - this will invoke any OnCreate scripts, etc.
					team->m_team->setActive();
					if (isSkirmishAI()) {
						TheScriptEngine->clearTeamFlags();
					}
					if (TheGlobalData->m_debugAI) {
						AsciiString teamName = team->m_team->getPrototype()->getName();
						// StringBase<char>::concat(const char *, int) at 0x00887D60, length folded.
						((StringBase<char> *)&teamName)->concat(" - team activated.", 18);
						TheScriptEngine->AppendDebugMessage(teamName, false);
					}
				}
				team->deleteInstance();
				iter = iterate_TeamReadyQueue();
			}
		}
	}
}
