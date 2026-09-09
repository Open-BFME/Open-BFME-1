// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/objectdlink
// partial score=0.94 date=2026-09-08
// TEAM_REPAIR_NEREST scans a team for the most damaged eligible object, then
// sends every eligible member of the named repair team to that object.

#include "StringInline.h"
#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef float Real;

class Team;
class Object;

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

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xc0];
	unsigned int m_repairFlags;
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void aiRepair(Object *object, CommandSourceType source);
};

class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_00[0x20];
	AICommandInterface m_command;
};

class BfmeBodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Real getHealth() const = 0;
};

static const ThingTemplate *bfmeGetTemplate(const Object *object)
{
	return *(const ThingTemplate **)((const unsigned char *)object + 4);
}

static BfmeBodyModuleInterface *bfmeGetBody(const Object *object)
{
	return *(BfmeBodyModuleInterface **)((const unsigned char *)object + 0x200);
}

static AIUpdateInterface *bfmeGetAI(const Object *object)
{
	return *(AIUpdateInterface **)((const unsigned char *)object + 0x204);
}

template <class ObjectType>
class BfmeDlinkIterator
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	BfmeDlinkIterator(ObjectType *cur, GetNextFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const
	{
		return m_cur == 0;
	}

	ObjectType *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

class Team
{
public:
	void *m_vptr;
	void *m_unmodelled0;
	void *m_unmodelled1;
	Object *m_head;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_head,
			Object::dlink_next_TeamMemberList);
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
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern void j_00001140();
extern void j_000022bb();
extern void j_00029c08();

#pragma comment(linker, "/alternatename:?dlink_next_TeamMemberList@BfmeObjectDlinkBase@@QBEPAVObject@@XZ=?j_00001140@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiRepair@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z=?j_00029c08@@YAXXZ")

static const ThingTemplate *bfmeFinalTemplate(const Overridable *value)
{
	typedef const Overridable *(Overridable::*Function)() const;
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_000022bb;
	return (const ThingTemplate *)(value->*function.member)();
}

static void bfmeAiRepair(AICommandInterface *command, Object *object,
	CommandSourceType source)
{
	typedef void (AICommandInterface::*Function)(Object *, CommandSourceType);
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_00029c08;
	(command->*function.member)(object, source);
}

class ScriptActions
{
protected:
	void doTeamRepairNearest(const AsciiString &repairTeamName,
		const AsciiString &targetTeamName);
};

void ScriptActions::doTeamRepairNearest(const AsciiString &repairTeamName,
	const AsciiString &targetTeamName)
{
	Team *repairTeam = TheScriptEngine->getTeamNamed(repairTeamName, false);
	Team *targetTeam = TheScriptEngine->getTeamNamed(targetTeamName, false);
	if (!repairTeam)
		return;

	Object *mostDamaged = 0;
	Real lowestHealth = 1.0f;
	BfmeDlinkIterator<Object> target = targetTeam->iterate_TeamMemberList();
	while (!target.done())
	{
		Object *object = target.cur();
		const ThingTemplate *thingTemplate = bfmeGetTemplate(object);
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = bfmeFinalTemplate(thingTemplate->m_nextOverride);
		if (*(const unsigned char *)&thingTemplate->m_repairFlags & 0x80)
		{
			BfmeBodyModuleInterface *body = bfmeGetBody(object);
			if (body)
			{
				if (body->getHealth() < lowestHealth)
				{
					mostDamaged = object;
					lowestHealth = body->getHealth();
				}
			}
		}
		target.advance();
	}

	if (mostDamaged)
	{
		BfmeDlinkIterator<Object> repair = repairTeam->iterate_TeamMemberList();
		while (!repair.done())
		{
			Object *object = repair.cur();
			const ThingTemplate *thingTemplate = bfmeGetTemplate(object);
			if (thingTemplate && thingTemplate->m_nextOverride)
				thingTemplate = bfmeFinalTemplate(thingTemplate->m_nextOverride);
			if (thingTemplate->m_repairFlags & 0x4000)
			{
				AIUpdateInterface *ai = bfmeGetAI(object);
				if (ai)
					bfmeAiRepair(&ai->m_command, mostDamaged,
						CMD_FROM_SCRIPT);
			}
			repair.advance();
		}
	}
}
