// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/objectdlink
// RVA 00303910, 340 bytes; action index480 uses two team-name parameters.
// The bank's TEAM_REPAIR_NEREST attribution belongs to action479 / RVA00303670.
// Both redundant object guards are needed for retail's unpadded loop shape.
// Body-interface slot5 reads a health ratio, not the adjacent raw-health getter.
// Naming, table and boundary evidence: identity_evidence/00303910-team-repair-action.md.

#include "ascii_string.h"
#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef float Real;

class Team;
class Object;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xc0];
	unsigned int m_kindof[1];
};

#include "../command_source_type.h"

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

// BFME BodyModuleInterface view: ctor00211A50 installs table010A7718 at+10.
class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual Real rva00303910Slot14() const = 0;
};

static const ThingTemplate *bfmeGetTemplate(const Object *object)
{
	return *(const ThingTemplate **)((const unsigned char *)object + 4);
}

static BodyModuleInterface *bfmeGetBody(const Object *object)
{
	return *(BodyModuleInterface **)((const unsigned char *)object + 0x200);
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
		if (m_cur)
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
	struct DlinkHead
	{
		Object *m_head;
	} m_dlinkhead_TeamMemberList;

	BfmeDlinkIterator<Object> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<Object>(m_dlinkhead_TeamMemberList.m_head,
			Object::dlink_next_TeamMemberList);
	}

};

// Only slot44 and its by-value string/bool call contract are needed here.
class Rva00303910ScriptEngineView
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
	virtual Team *rva00303910Slot44(AsciiString name, Bool exact) = 0;
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static const ThingTemplate *bfmeFinalTemplate(const Overridable *value)
{
	return (const ThingTemplate *)value->getFinalOverride();
}

static void bfmeAiRepair(AICommandInterface *command, Object *object,
	CommandSourceType source)
{
	command->aiRepair(object, source);
}

class ScriptActions
{
protected:
	void rva00303910(const AsciiString &repairTeamName,
		const AsciiString &targetTeamName);
};

void ScriptActions::rva00303910(const AsciiString &repairTeamName,
	const AsciiString &targetTeamName)
{
	Team *repairTeam = ((Rva00303910ScriptEngineView *)TheScriptEngine)->rva00303910Slot44(repairTeamName, false);
	Team *targetTeam = ((Rva00303910ScriptEngineView *)TheScriptEngine)->rva00303910Slot44(targetTeamName, false);
	if (!repairTeam)
		return;

	Object *mostDamaged = 0;
	Real lowestHealth = 1.0f;
	BfmeDlinkIterator<Object> target = targetTeam->iterate_TeamMemberList();
	for (; !target.done(); target.advance())
	{
		Object *object = target.cur();
		if (!object) continue;
		const ThingTemplate *thingTemplate = bfmeGetTemplate(object);
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = bfmeFinalTemplate(thingTemplate->m_nextOverride);
		if (*(const unsigned char *)&thingTemplate->m_kindof[0] & 0x80)
		{
			BodyModuleInterface *body = bfmeGetBody(object);
			if (body)
			{
				if (body->rva00303910Slot14() < lowestHealth)
				{
					mostDamaged = object;
					lowestHealth = body->rva00303910Slot14();
				}
			}
		}
	}

	if (mostDamaged)
	{
		BfmeDlinkIterator<Object> repair = repairTeam->iterate_TeamMemberList();
		for (; !repair.done(); repair.advance())
		{
			Object *object = repair.cur();
			if (!object) continue;
			const ThingTemplate *thingTemplate = bfmeGetTemplate(object);
			if (thingTemplate && thingTemplate->m_nextOverride)
				thingTemplate = bfmeFinalTemplate(thingTemplate->m_nextOverride);
			if (thingTemplate->m_kindof[0] & 0x4000)
			{
				AIUpdateInterface *ai = bfmeGetAI(object);
				if (ai)
					bfmeAiRepair(&ai->m_command, mostDamaged,
						CMD_FROM_SCRIPT);
			}
		}
	}
}
