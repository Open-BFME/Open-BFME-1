// ?queueDozer@AIPlayer@@MAEXXZ
// partial score=0.85 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?queueDozer@AIPlayer@@MAEXXZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::queueDozer, 0x001657E0, 490 bytes.
// Identity: slot 21 (+0x54) of the AIPlayer vtable 0x010968B0 routes through
// ILT 0x00033802 here, the slot Zero Hour's AIPlayer.h gives queueDozer
// (findDozer 20, selectTeamToBuild 22); the matched findDozer
// (AIPlayerDozer.cpp) makes this call when it finds no dozer. The body is the
// Zero Hour twin: dozerInQueue, the KINDOF_DOZER template walk, BFME's
// three-argument findFactory, the "DOZER - building one at the " debug line
// (VA 0x01096E70) and startTraining (slot 24).
//
// Layout: AIPlayer build queue head +0x04, m_player +0x0C, m_teamDelay +0x24;
// Player default team +0x230, can-build-units flag +0x294; ThingFactory first
// template +0x08; ThingTemplate KindOf word +0xC8 (KINDOF_DOZER bit 14), name
// +0x20, next template +0x38C; WorkOrder and TeamInQueue as in
// AIPlayerDozer.cpp and AIPlayerCheckReadyTeams.cpp. WorkOrder's constructor
// stores the existing retail table 0x01096964, as TeamInQueueXfer.cpp does;
// TeamInQueue's is the out-of-line 0x00161220.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define NULL 0
#define FALSE 0

enum { KINDOF_DOZER = 14 };

extern const AsciiString Rva01336E50EmptyString;

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;					// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return m_nameString; }
	UnsignedInt isKindOf(Int t) const { return m_kindOf & (1 << t); }
	const ThingTemplate *friend_getNextTemplate() const { return m_nextTemplate; }

private:
	unsigned char m_unmodelled008[0x20 - 0x08];
	AsciiString m_nameString;					// +0x20
	unsigned char m_unmodelled024[0xc8 - 0x24];
	UnsignedInt m_kindOf;						// +0xC8
	unsigned char m_unmodelled0cc[0x38c - 0xcc];
	ThingTemplate *m_nextTemplate;					// +0x38C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	const ThingTemplate *firstTemplate() { return m_firstTemplate; }
private:
	unsigned char m_unreconstructed_000[0x08];
	ThingTemplate *m_firstTemplate;					// +0x08
};

extern ThingFactory *TheThingFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (m_template && m_template->m_nextOverride)
			return (const ThingTemplate *)m_template->m_nextOverride->getFinalOverride();
		return m_template;
	}
private:
	void *m_vtable;
	const ThingTemplate *m_template;				// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }
private:
	char m_unreconstructed_000[0x3c];
	UnsignedInt m_frame;						// +0x3C
};

extern GameLogic *TheGameLogic;

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	const AsciiString &getName(void) const { return m_rva14Name; }
private:
	char m_unreconstructed_000[0x14];
	AsciiString m_rva14Name;					// +0x14
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	const AsciiString &getName(void) const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->getName();
	}
private:
	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool getCanBuildUnits(void) { return m_canBuildUnits; }
	void setCanBuildUnits(Bool canBuildUnits) { m_canBuildUnits = canBuildUnits; }
	Team *getDefaultTeam(void) { return m_defaultTeam; }
private:
	char m_unreconstructed_000[0x230];
	Team *m_defaultTeam;						// +0x230
	char m_unreconstructed_234[0x294 - 0x234];
	Bool m_canBuildUnits;						// +0x294
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	WorkOrder()
		: m_vptr((void *)0x01096964), m_thing(NULL), m_factoryID(0), m_next(NULL),
		  m_numCompleted(0), m_numRequired(1), m_isResourceGatherer(false)
	{
	}

	void *m_vptr;
	const ThingTemplate *m_thing;					// +0x04
	Int m_factoryID;						// +0x08
	WorkOrder *m_next;						// +0x0C
	Int m_numCompleted;						// +0x10
	Int m_numRequired;						// +0x14
	Bool m_required;						// +0x18
	Bool m_isResourceGatherer;					// +0x19
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	Bool dlink_isInList_TeamBuildQueue(TeamInQueue *const *pListHead) const
	{
		return *pListHead == this || m_dlink_TeamBuildQueue_prev || m_dlink_TeamBuildQueue_next;
	}
	void dlink_prependTo_TeamBuildQueue(TeamInQueue **pListHead)
	{
		m_dlink_TeamBuildQueue_next = *pListHead;
		if (*pListHead)
			(*pListHead)->m_dlink_TeamBuildQueue_prev = this;
		*pListHead = this;
	}

	void *m_vptr;
	TeamInQueue *m_dlink_TeamBuildQueue_prev;			// +0x04
	TeamInQueue *m_dlink_TeamBuildQueue_next;			// +0x08
	TeamInQueue *m_dlink_TeamReadyQueue_prev;			// +0x0C
	TeamInQueue *m_dlink_TeamReadyQueue_next;			// +0x10
	WorkOrder *m_workOrders;					// +0x14
	Bool m_priorityBuild;						// +0x18
	Team *m_team;							// +0x1C
	TeamInQueue *m_nextTeamInQueue;					// +0x20
	Int m_frameStarted;						// +0x24
	char m_unmodelled028[0x30 - 0x28];
};

// The retail TeamInQueue constructor at 0x00161220 (ILT 0x0001F7A8), whose
// owner name the ledger keeps address-derived.
class Rva00161220
{
public:
	Rva00161220() throw();
private:
	char m_storage[0x30];
};

class Object;

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

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

protected:
	virtual void queueDozer(void);					// slot 21
	BFME_VIRTUAL_SLOT(22) BFME_VIRTUAL_SLOT(23)
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);	// slot 24

	Bool dozerInQueue(void);
	Object *findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex);

	void prependTo_TeamBuildQueue(TeamInQueue *o)
	{
		if (!o->dlink_isInList_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue))
			o->dlink_prependTo_TeamBuildQueue(&m_dlinkhead_TeamBuildQueue);
	}

private:
	TeamInQueue *m_dlinkhead_TeamBuildQueue;			// +0x04
	TeamInQueue *m_dlinkhead_TeamReadyQueue;			// +0x08
	Player *m_player;						// +0x0C
	char m_unreconstructed_010[0x24 - 0x10];
	Int m_teamDelay;						// +0x24
};

#undef BFME_VIRTUAL_SLOT

void AIPlayer::queueDozer( void )
{

	if (dozerInQueue()) return;
	// Find a factory that can build a dozer.

	Bool canBuildUnits = m_player->getCanBuildUnits();
	// If we need a dozer, turn on unit building for a moment.
	m_player->setCanBuildUnits(true);
	const ThingTemplate *tTemplate = TheThingFactory->firstTemplate();
	while (tTemplate) {
		if (tTemplate->isKindOf(KINDOF_DOZER)) {
			Object *factory = findFactory(tTemplate, true, NULL);
			if (factory) {
				// we can build one.
				WorkOrder *order = new WorkOrder;
				order->m_thing = tTemplate;
				order->m_factoryID = 0;
				order->m_numRequired = 1;
				order->m_required = true;
				order->m_isResourceGatherer = FALSE;
				// prepend to head of list
				order->m_next = NULL;
				TeamInQueue *team = (TeamInQueue *)new Rva00161220;
				// Put in front of queue.
				prependTo_TeamBuildQueue(team);
				team->m_priorityBuild = true;
				team->m_workOrders = order;
				team->m_frameStarted = TheGameLogic->getFrame();
				// Stick it on the default team
				team->m_team = m_player->getDefaultTeam();
				AsciiString teamName = "DOZER - building one at the ";
				bfmeConcat(teamName, factory->getTemplate()->getName());
				TheScriptEngine->AppendDebugMessage(teamName, false);
				m_teamDelay = 0;
				startTraining( order, team->m_priorityBuild, team->m_team->getName());
				break;
			}
		}
		tTemplate = tTemplate->friend_getNextTemplate();
	}
	// restore canbuildunits.
	m_player->setCanBuildUnits(canBuildUnits);
}
