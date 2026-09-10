// ?d_00302c70@@YAXXZ
// partial score=0.92 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME: clean C++ reconstruction of the team guard-for-framecount action.

typedef bool Bool;
typedef int Int;
typedef float Real;

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AsciiString
{
	char *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_beforePosition[0x34];
	Coord3D m_position;
	unsigned char m_afterPosition[0x24];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}
};

class ObjectPositionView
{
	unsigned char m_beforePosition[0x38];

public:
	Coord3D m_position;
};

__forceinline static void copyPosition(Coord3D *destination,
	const Coord3D *source)
{
	destination->x = source->x;
	destination->y = source->y;
	destination->z = source->z;
}

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *position, GuardMode guardMode,
		CommandSourceType commandSource);
};

class AIUpdateInterface
{
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

static AIUpdateInterface *getAIUpdateInterface(Object *object)
{
	return *(AIUpdateInterface **)((unsigned char *)object + 0x204);
}

class Team
{
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual Team *getTeamPrototypeNamed(BfmeAsciiStringArg) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;

	void setSequentialTimer(Team *, Int);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamGuardForFramecount(const AsciiString &, Int, Bool);
};

// ?doTeamGuardForFramecount@ScriptActions@@IAEXABVAsciiString@@H_N@Z
void ScriptActions::doTeamGuardForFramecount(const AsciiString &teamName,
	Int framecount, Bool seconds)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		AIUpdateInterface *ai = getAIUpdateInterface(object);
		if (!ai)
			continue;

		Coord3D position;
		const Coord3D *source = &object->m_position;
		__assume(source != &position);
		position.x = source->x;
		position.y = source->y;
		position.z = source->z;
		ai->m_command.aiGuardPosition(&position, GUARDMODE_NORMAL,
			CMD_FROM_SCRIPT);
	}
	if (seconds)
		TheScriptEngine->setSequentialTimer(theTeam, framecount * 5);
	else
		TheScriptEngine->setSequentialTimer(theTeam, framecount);
}
