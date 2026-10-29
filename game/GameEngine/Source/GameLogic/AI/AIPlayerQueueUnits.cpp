// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?queueUnits@AIPlayer@@IAEXXZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::queueUnits, 0x00167E80, 805 bytes (ret at +0x324, int3 after).
// Identity: EA names 0x00167E80 AIPlayer::queueUnits (direct, aligned) in
// GameEngine/Source/GameLogic/AI/AIPlayer.cpp, and the body is the Zero Hour
// twin: the build-queue walk over each work order, the recruit loop with the
// "Team '" / "' recruits " / " from team '" / "'" debug line, startTraining
// (AIPlayer slot 24) for a waiting order and the inlined
// WorkOrder::validateFactory otherwise. Its first call, through ILT
// 0x00026EE5 to 0x00165D50, is where Zero Hour calls queueSupplyTruck.
//
// BFME differences: without a template home location the recruit radius is
// the literal 100000.0f rather than TAiData::m_maxRecruitDistance; a
// recruited unit's AI is null-tested, and the team is marked active
// (Team +0x31/+0x32, as in AIPlayerCheckReadyTeams.cpp) after each recruit.
//
// Layout: AIPlayer build queue head +0x04, m_player +0x0C, m_baseCenter
// +0x34, m_baseCenterSet +0x40; TeamInQueue work orders +0x14, priority
// build +0x18, team +0x1C; WorkOrder thing +0x04, factory +0x08, next
// +0x0C, completed +0x10, required +0x14; TeamPrototype name +0x14, template
// info +0x130 (home +0x58, has-home +0x64); Object AI +0x204 (its
// AICommandInterface at +0x20), team +0x23C, setTeam slot 20.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
// This unit's local TeamPrototype view defines getTemplateInfo inline at its own offset
// (not +0x68) and emits that COMDAT copy; rename it so only retail's 0x003BCD70
// (lea eax,[ecx+0x68]) carries the name. Inlined calls are unchanged.
#define getTemplateInfo getTemplateInfo_LocalView
#include <hash_map>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int ObjectID;

#define NULL 0
#define INVALID_ID 0

extern const AsciiString Rva01336E50EmptyString;

#include "../command_source_type.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Zero Hour's Coord3D::set(const Coord3D *): retail copies the template home
// member by member, straight off the prototype, not as a 12-byte struct copy.
static inline void bfmeCoordSet(Coord3D *dst, const Coord3D *a)
{
	dst->x = a->x; dst->y = a->y; dst->z = a->z;
}
// StringBase<char>'s buffer header: refcount, length, capacity, data.
struct BfmeAsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

// Retail inlines AsciiString::concat(const AsciiString &) as
// concat(str(), getLength()), each accessor with its own null test.
class BfmeAsciiView
{
public:
	int getLength() const { return m_data ? m_data->m_length : 0; }
	const char *str() const { return m_data ? m_data->m_data : ""; }
private:
	const BfmeAsciiHeader *m_data;
};

static inline void bfmeConcat(AsciiString &dst, const AsciiString &src)
{
	const BfmeAsciiView &s = *(const BfmeAsciiView *)&src;
	((StringBase<char> *)&dst)->concat(s.str(), s.getLength());
}

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

class Object;
class Player;
class Team;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }
private:
	char m_unmodelled000[0x20];
	AsciiString m_nameString;					// +0x20
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamTemplateInfo
{
public:
	char m_unmodelled000[0x58];
	Coord3D m_homeLocation;						// +0x58
	Bool m_hasHomeLocation;						// +0x64
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_rva14Name; }
	const TeamTemplateInfo *getTemplateInfo(void) const { return &m_teamTemplate; }

	char m_unmodelled000[0x14];
	AsciiString m_rva14Name;					// +0x14
	char m_unmodelled018[0x130 - 0x18];
	TeamTemplateInfo m_teamTemplate;				// +0x130
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	const TeamPrototype *getPrototype(void) const { return m_proto; }
	const AsciiString &getName(void) const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->getName();
	}
	void setActive(void) { if (!m_active) { m_created = true; m_active = true; } }

private:
	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
	char m_unmodelled008[0x31 - 0x08];
	Bool m_active;							// +0x31
	Bool m_created;							// +0x32
};

// The recruit search at 0x000F2A00 (ILT 0x0001A2B2): Zero Hour's
// Team::tryToRecruit by call site; the body itself is still unnamed.
class Rva000F2A00Team
{
public:
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *teamHome, Real maxDist);
};

class AIUpdatePrimary
{
public:
	virtual void bfmePrimarySlot0();
	unsigned char m_primaryPad[0x1c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void bfmeCommandSlot0();
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AIUpdatePrimary, public AICommandInterface
{
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(01) BFME_VIRTUAL_SLOT(02)
	BFME_VIRTUAL_SLOT(03) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(05)
	BFME_VIRTUAL_SLOT(06) BFME_VIRTUAL_SLOT(07) BFME_VIRTUAL_SLOT(08)
	BFME_VIRTUAL_SLOT(09) BFME_VIRTUAL_SLOT(10) BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15) BFME_VIRTUAL_SLOT(16) BFME_VIRTUAL_SLOT(17)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(19)
	virtual void setTeam(Team *team);				// slot 20

	Team *getTeam() const { return m_team; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Player *getControllingPlayer() const;

private:
	char m_unmodelled004[0x204 - 0x04];
	AIUpdateInterface *m_ai;					// +0x204
	char m_unmodelled208[0x23c - 0x208];
	Team *m_team;							// +0x23C
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
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
	char m_unmodelled000[0xb0];
	ObjectPtrHash m_objHash;					// buckets at +0xB4
};

extern GameLogic *TheGameLogic;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct TAiData
{
	char m_unmodelled000[0x5c];
	Real m_maxRecruitDistance;					// +0x5C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	char m_unmodelled000[0x14];
	TAiData *m_aiData;						// +0x14
};

extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	Bool isWaitingToBuild(void) const
	{
		return m_factoryID == INVALID_ID && m_numCompleted < m_numRequired;
	}
	void validateFactory(Player *thisPlayer)
	{
		if (m_factoryID == INVALID_ID)
			return;
		Object *factory = TheGameLogic->findObjectByID( m_factoryID );
		if ( factory == NULL) {
			m_factoryID = INVALID_ID;
			return;
		}
		if (factory->getControllingPlayer()!=thisPlayer) {
			m_factoryID = INVALID_ID;
		}
	}

	void *m_vptr;
	const ThingTemplate *m_thing;					// +0x04
	ObjectID m_factoryID;						// +0x08
	WorkOrder *m_next;						// +0x0C
	Int m_numCompleted;						// +0x10
	Int m_numRequired;						// +0x14
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	virtual ~TeamInQueue();

	TeamInQueue *dlink_next_TeamBuildQueue() const;

	TeamInQueue *m_dlink_TeamBuildQueue_prev;			// +0x04
	TeamInQueue *m_dlink_TeamBuildQueue_next;			// +0x08
	TeamInQueue *m_dlink_TeamReadyQueue_prev;			// +0x0C
	TeamInQueue *m_dlink_TeamReadyQueue_next;			// +0x10
	WorkOrder *m_workOrders;					// +0x14
	Bool m_priorityBuild;						// +0x18
	Team *m_team;							// +0x1C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(01) BFME_VIRTUAL_SLOT(02)
	BFME_VIRTUAL_SLOT(03) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(05)
	BFME_VIRTUAL_SLOT(06) BFME_VIRTUAL_SLOT(07) BFME_VIRTUAL_SLOT(08)
	BFME_VIRTUAL_SLOT(09) BFME_VIRTUAL_SLOT(10) BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15) BFME_VIRTUAL_SLOT(16) BFME_VIRTUAL_SLOT(17)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(19) BFME_VIRTUAL_SLOT(20)
	BFME_VIRTUAL_SLOT(21) BFME_VIRTUAL_SLOT(22) BFME_VIRTUAL_SLOT(23)

protected:
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);	// slot 24

	void queueSupplyTruck(void);
	void queueUnits(void);

	Bool getBaseCenter(Coord3D *pos) const { *pos = m_baseCenter; return m_baseCenterSet; }

	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_dlinkhead_TeamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;			// +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue;			// +0x08
	Player *m_player;						// +0x0C
	char m_unmodelled010[0x34 - 0x10];
	Coord3D m_baseCenter;						// +0x34
	Bool m_baseCenterSet;						// +0x40
};

#undef BFME_VIRTUAL_SLOT

void AIPlayer::queueUnits( void )
{

	queueSupplyTruck();

	// For each member of the current team to build, try to find a faction building to build it.
	//
	for ( DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		for( WorkOrder *order = team->m_workOrders; order; order = order->m_next )
		{
			// check if there is a unit on the map that we can steal (recruit) instead of building
			Coord3D home;
			bfmeCoordSet(&home, &team->m_team->getPrototype()->getTemplateInfo()->m_homeLocation);
			Bool hasHome = false;
			if (team->m_team->getPrototype()->getTemplateInfo()->m_hasHomeLocation) {
				hasHome = true;
			} else {
				hasHome = getBaseCenter(&home);
			}
			while (order->isWaitingToBuild()) {

				Object *unit;
				if (hasHome) {
					unit = ((Rva000F2A00Team *)team->m_team)->tryToRecruit(order->m_thing, &home, TheAI->getAiData()->m_maxRecruitDistance);
				} else {
					unit = ((Rva000F2A00Team *)team->m_team)->tryToRecruit(order->m_thing, &home, 100000.0f);
				}
				if (unit)
				{
					order->m_numCompleted++;

					AsciiString teamStr = "Team '";
					bfmeConcat(teamStr, team->m_team->getPrototype()->getName());
					((StringBase<char> *)&teamStr)->concat("' recruits ", 11);
					bfmeConcat(teamStr, order->m_thing->getName());
					((StringBase<char> *)&teamStr)->concat(" from team '", 12);
					bfmeConcat(teamStr, unit->getTeam()->getPrototype()->getName());
					((StringBase<char> *)&teamStr)->concat("'", 1);
					TheScriptEngine->AppendDebugMessage(teamStr, false);

					unit->setTeam(team->m_team);

					AIUpdateInterface *ai = unit->getAIUpdateInterface();
					if (ai) {
						if (hasHome) {
							ai->aiMoveToPosition( &home, CMD_FROM_AI);
						} else {
							ai->aiIdle(CMD_FROM_AI); // stop, you've been recruited.
						}
					}
					team->m_team->setActive();
				}	else {
					break;
				}
			}
			if (order->isWaitingToBuild())
			{

				// start the creation of a new unit
				startTraining( order, team->m_priorityBuild, team->m_team->getName());
			}
			else
			{
				// we are under construction, verify our factory still exists
				order->validateFactory(m_player);
			}
		}
	}
}
