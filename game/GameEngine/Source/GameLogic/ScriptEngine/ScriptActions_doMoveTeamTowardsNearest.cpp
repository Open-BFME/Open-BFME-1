// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// ScriptActions::doMoveTeamTowardsNearest, retail RVA 0x00302F00, 410 bytes.

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
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

class PolygonTrigger;
class ThingTemplate;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class AICommandInterface
{
public:
	void bfmeCommand01(Object *objectToEnter, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_beforeCommands[0x20];
	AICommandInterface m_commands;
};

static __forceinline AIUpdateInterface *bfmeGetAIUpdateInterface(Object *object)
{
	return *(AIUpdateInterface **)((unsigned char *)object + 0x204);
}

static __forceinline const Coord3D *bfmeGetPosition(const Object *object)
{
	return (const Coord3D *)((const unsigned char *)object + 0x38);
}

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

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
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur(void) const
	{
		return m_cur;
	}
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
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class PartitionFilter
{
public:
	PartitionFilter(void) {}
	PartitionFilter *link(PartitionFilter *next);

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterThing : public PartitionFilter
{
public:
	PartitionFilterThing(const ThingTemplate *thingTemplate, Bool match)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x010CFFD0;
		m_thingTemplate = thingTemplate;
		m_match = match;
	}

	~PartitionFilterThing(void)
	{
		m_vptr = 0x01083B5C;
	}

	const ThingTemplate *m_thingTemplate;
	Bool m_match;
};

class PartitionFilterPolygonTrigger : public PartitionFilter
{
public:
	PartitionFilterPolygonTrigger(const PolygonTrigger *trigger)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x01095714;
		m_trigger = trigger;
	}

	~PartitionFilterPolygonTrigger(void)
	{
		m_vptr = 0x01083B5C;
	}

	const PolygonTrigger *m_trigger;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x01085DD0;
		m_object = object;
	}

	~PartitionFilterSameMapStatus(void)
	{
		m_vptr = 0x01083B5C;
	}

	const Object *m_object;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;

class ScriptActions
{
protected:
	// ?doMoveTeamTowardsNearest@ScriptActions@@IAEXABVAsciiString@@0V2@@Z
	void doMoveTeamTowardsNearest(const AsciiString &teamName,
		const AsciiString &objectType, AsciiString triggerName);
};

void ScriptActions::doMoveTeamTowardsNearest(const AsciiString &teamName,
	const AsciiString &objectType, AsciiString triggerName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	const ThingTemplate *thingTemplate =
		TheThingFactory->findTemplate(objectType);
	if (!thingTemplate)
		return;

	PolygonTrigger *trigger =
		TheScriptEngine->getQualifiedTriggerAreaByName(triggerName);
	if (!trigger)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		AIUpdateInterface *ai = bfmeGetAIUpdateInterface(object);
		if (ai)
		{
			Object *nearestObject;
			{
				PartitionFilterSameMapStatus mapFilter(object);
				PartitionFilterPolygonTrigger triggerFilter(trigger);
				PartitionFilterThing thingFilter(thingTemplate, true);

				nearestObject = ThePartitionManager->getClosestObject(
					bfmeGetPosition(object), 1000000.0f, 0,
					thingFilter.link(triggerFilter.link(&mapFilter)));
			}
			if (!nearestObject)
				return;

			ai->m_commands.bfmeCommand01(nearestObject, CMD_FROM_SCRIPT);
		}
	}
}
