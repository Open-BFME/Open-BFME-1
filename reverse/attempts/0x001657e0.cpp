// ?queueDozer@AIPlayer@@MAEXXZ
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AIPlayer::queueDozer, retail 0x001657E0 (490 bytes).
//
// This local view follows the BFME body and leaves the shared Generals
// headers untouched: findFactory has its BFME build-index argument,
// ThingTemplate's template-chain link is at +0x38C, and Player's production
// flag is at +0x294.

typedef bool Bool;
typedef int Int;
enum { KINDOF_DOZER = 1 << 14 };

class AsciiString;

template <typename T> struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
friend class AsciiString;

	private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	public:
	void concat(const T *text, int length);

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	void concat(const AsciiString &other)
	{
		StringInlineData<char> *data = other.m_data;
		const char *text;
		unsigned short length;
		if (data)
		{
			length = data->m_length;
			text = data->m_text;
		}
		else
		{
			length = 0;
			text = (const char *)0x0107388B;
		}
		concat(text, length);
	}
};

class Team;
class Object;

class Player
{
private:
	unsigned char m_unreconstructed_000[0x230];

public:
	Team *m_defaultTeam;
	unsigned char m_unreconstructed_234[0x294 - 0x234];
	Bool m_canBuildUnits;

	Bool getCanBuildUnits() const { return m_canBuildUnits; }
	void setCanBuildUnits(Bool value) { m_canBuildUnits = value; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
};

class TeamPrototype
{
private:
	unsigned char m_unreconstructed_000[0x14];

public:
	AsciiString m_name;
	const AsciiString &getName() const { return m_name; }
};

class Team
{
private:
	void *m_vtable;

public:
	TeamPrototype *m_proto;
	TeamPrototype *getPrototype() const { return m_proto; }
	const AsciiString &getName() const
	{
		return m_proto ? m_proto->getName() : *(const AsciiString *)0x01336E50;
	}
};

class ThingTemplate
{
private:
	void *m_vtable;
	void *m_nextOverride;
	unsigned char m_unreconstructed_008[0x20 - 0x08];

public:
	AsciiString m_name;

private:
	unsigned char m_unreconstructed_024[0xC8 - 0x24];

public:
	unsigned int m_kindOf;
	unsigned char m_unreconstructed_0CC[0x38C - 0xCC];
	ThingTemplate *m_nextTemplate;

	ThingTemplate *friend_getNextTemplate() const { return m_nextTemplate; }
	ThingTemplate *getNextOverride() const
	{
		return (ThingTemplate *)m_nextOverride;
	}
};

class ThingFactory
{
private:
	unsigned char m_unreconstructed_000[8];

public:
	ThingTemplate *m_firstTemplate;
	ThingTemplate *firstTemplate() const { return m_firstTemplate; }
};

class Object
{
public:
	ThingTemplate *getTemplate() const
	{
		return *(ThingTemplate **)((const char *)this + 4);
	}
};

class GameLogic
{
private:
	unsigned char m_unreconstructed_000[0x3C];

public:
	Int m_frame;
	Int getFrame() const { return m_frame; }
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

class WorkOrder
{
public:
	WorkOrder()
	{
		m_thing = 0;
		m_factoryID = 0;
		m_next = 0;
		m_numCompleted = 0;
		m_vtable = (void *)0x01096964;
		m_numRequired = 1;
		m_isResourceGatherer = false;
	}

	void *m_vtable;
	ThingTemplate *m_thing;
	Int m_factoryID;
	WorkOrder *m_next;
	Int m_numCompleted;
	Int m_numRequired;
	Bool m_required;
	Bool m_isResourceGatherer;
};

class TeamInQueue
{
public:
	void *m_vtable;
	TeamInQueue *m_buildPrevious;
	TeamInQueue *m_buildNext;
	TeamInQueue *m_readyPrevious;
	TeamInQueue *m_readyNext;
	WorkOrder *m_workOrders;
	Bool m_priorityBuild;
	unsigned char m_unreconstructed_019[3];
	Team *m_team;
	TeamInQueue *m_nextTeamInQueue;
	Int m_frameStarted;
	Bool m_sentToStartLocation;
	Bool m_stopQueueing;
	Bool m_reinforcement;
	unsigned char m_unreconstructed_02F;
};

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual Object *findDozer(const void *position);
	virtual void queueDozer();
	virtual void slot58();
	virtual void slot5c();
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);

	Bool dozerInQueue();

	void prependTo_TeamBuildQueue(TeamInQueue *team)
	{
		if (m_teamBuildQueue == team)
			return;
		if (team->m_buildPrevious || team->m_buildNext)
			return;
		team->m_buildNext = m_teamBuildQueue;
		if (m_teamBuildQueue)
			m_teamBuildQueue->m_buildPrevious = team;
		m_teamBuildQueue = team;
	}

private:
	TeamInQueue *m_teamBuildQueue;
	unsigned char m_unreconstructed_008[4];
	Player *m_player;
	unsigned char m_unreconstructed_010[0x14];
	Int m_teamDelay;
};

#define TheThingFactory (*(ThingFactory **)0x012EF1D8)
#define TheGameLogic (*(GameLogic **)0x012F0898)
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)

extern void j_000022bb();
extern void j_00028ce0();
extern void j_0001f7a8();
extern void j_0002b62f();

static ThingTemplate *bfmeFinalOverride(ThingTemplate *thing)
{
	typedef ThingTemplate *(ThingTemplate::*FinalOverride)();
	union { void (*raw)(); FinalOverride member; } call;
	call.raw = j_000022bb;
	return (thing->*call.member)();
}

static TeamInQueue *newTeamInQueue()
{
	TeamInQueue *team = (TeamInQueue *)operator new(0x30);
	if (team)
	{
		typedef void (TeamInQueue::*Constructor)();
		union { void (*raw)(); Constructor member; } call;
		call.raw = j_0001f7a8;
		(team->*call.member)();
	}
	return team;
}

static Object *bfmeFindFactory(AIPlayer *player, const ThingTemplate *thing,
	Bool busyOK)
{
	typedef Object *(AIPlayer::*FindFactory)(const ThingTemplate *, Bool, Int *);
	union { void (*raw)(); FindFactory member; } call;
	call.raw = j_0002b62f;
	return (player->*call.member)(thing, busyOK, 0);
}

static __forceinline void bfmeAppendDebugMessage(ScriptEngine *engine,
	const AsciiString &message, Bool forcePause)
{
	typedef void (ScriptEngine::*Append)(const AsciiString &, Bool);
	union { void (*raw)(); Append member; } call;
	call.raw = j_00028ce0;
	(engine->*call.member)(message, forcePause);
}

// ?queueDozer@AIPlayer@@MAEXXZ
void AIPlayer::queueDozer()
{
	if (dozerInQueue())
		return;

	Bool canBuildUnits = m_player->getCanBuildUnits();
	m_player->setCanBuildUnits(true);
	const ThingTemplate *tTemplate = TheThingFactory->firstTemplate();
	register const Int zero = 0;
	WorkOrder *order = (WorkOrder *)zero;
	while (tTemplate != (const ThingTemplate *)zero)
	{
		unsigned int kindOf = tTemplate->m_kindOf;
		if ((kindOf & KINDOF_DOZER) != 0)
		{
			register Object *factory = bfmeFindFactory(this, tTemplate, true);
			if (factory != (Object *)zero)
			{
				order = new WorkOrder;
				order->m_thing = (ThingTemplate *)tTemplate;
				order->m_factoryID = 0;
				order->m_numRequired = 1;
				order->m_required = true;
				order->m_isResourceGatherer = false;
				order->m_next = 0;

				TeamInQueue *team = newTeamInQueue();
				prependTo_TeamBuildQueue(team);
				team->m_priorityBuild = true;
				team->m_workOrders = order;
				team->m_frameStarted = TheGameLogic->getFrame();
				team->m_team = m_player->getDefaultTeam();

				AsciiString teamName = (const char *)0x01096E70;
				ThingTemplate *factoryTemplate = factory->getTemplate();
				if (factoryTemplate->getNextOverride())
					factoryTemplate = bfmeFinalOverride(factoryTemplate->getNextOverride());
				teamName.concat(factoryTemplate->m_name);
				bfmeAppendDebugMessage(TheScriptEngine, teamName, false);
				m_teamDelay = 0;
				startTraining(order, team->m_priorityBuild, team->m_team->getName());
				break;
			}
		}
		tTemplate = tTemplate->friend_getNextTemplate();
	}
	m_player->setCanBuildUnits(canBuildUnits);
}
