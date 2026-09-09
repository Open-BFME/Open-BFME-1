// ?doTeamGuard@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.995 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/stringinline
// The TEAM_GUARD arm at executeAction 0x00303BF0 calls this body at retail
// RVA 0x00301C10. It walks the team's Object list and issues one guard order
// for each eligible member.

#include "StringInline.h"

extern "C" void *memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

typedef bool Bool;

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

union CoordComponent
{
	float value;
	unsigned int bits;
};

struct Coord3D
{
	CoordComponent x;
	CoordComponent y;
	CoordComponent z;
	Coord3D(void) { }
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
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

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

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

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];

	AIUpdateInterface *getAIUpdateInterface(void) const
	{
		return *(AIUpdateInterface **)(
			(unsigned char *)this + 0x204);
	}

	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}

	Bool hasStatus94Bit20(void) const
	{
		return (*(const unsigned char *)((const unsigned char *)this + 0x94) &
			0x20) != 0;
	}

	Bool hasStatus90Bit04(void) const
	{
		return (*(const unsigned char *)((const unsigned char *)this + 0x90) &
			0x04) != 0;
	}
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance(void)
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done(void) const { return m_cur == 0; }
	OBJCLASS *cur(void) const { return m_cur; }
};

class Team
{
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamGuard(const AsciiString &teamName);
};

// ?doTeamGuard@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamGuard(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		if (object->hasStatus94Bit20())
			continue;
		if (object->hasStatus90Bit04())
			continue;

		Coord3D position;
		unsigned int newY;
		unsigned int newX;
		unsigned int newZ;
		AIUpdateInterface *const ai = object->getAIUpdateInterface();
		if (!ai)
			continue;

		newX = object->getPosition()->x.bits;
		newY = object->getPosition()->y.bits;
		position.x.bits = newX;
		newZ = object->getPosition()->z.bits;
		position.y.bits = newY;
		position.z.bits = newZ;
		ai->m_command.aiGuardPosition(&position, GUARDMODE_NORMAL,
			CMD_FROM_SCRIPT);
	}
}
