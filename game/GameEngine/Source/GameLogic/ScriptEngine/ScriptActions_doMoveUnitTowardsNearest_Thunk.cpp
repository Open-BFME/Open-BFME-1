// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// ScriptActions::doMoveUnitTowardsNearest, retail RVA 0x00302D70, 314 bytes.
//
// The executeAction dispatcher names this operation
// UNIT_MOVE_TOWARDS_NEAREST_OBJECT_TYPE (ScriptActions.cpp, around 0x8862).
// Retail first resolves the named unit, then its AIUpdateInterface at +0x204,
// finds one ThingTemplate, resolves the qualified trigger, and queries the
// three linked partition filters before issuing BFME command 0x01.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class PolygonTrigger;
class ThingTemplate;

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
	virtual void slot17(void) = 0;
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

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
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

class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}

	AIUpdateInterface *getAIUpdateInterface(void) const
	{
		return m_aiUpdate;
	}

private:
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
	unsigned char m_betweenPositionAndAI[0x1c0];
	AIUpdateInterface *m_aiUpdate;
};

class PartitionFilter
{
public:
	PartitionFilter(void) {}
	PartitionFilter *link(PartitionFilter *next);

	// Retail stores the filter vptr at +0 and the link at +4.  These are
	// explicit TU-local layout words because the shared filter declarations
	// do not expose the three BFME vtables; all four values are read directly
	// from this body's constructor/destructor stores.
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
		m_vptr = 0x010CFFD0; // retail PartitionFilterThing vtable
		m_thingTemplate = thingTemplate;
		m_match = match;
	}

	~PartitionFilterThing(void)
	{
		m_vptr = 0x01083B5C; // retail PartitionFilter base vtable
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
		m_vptr = 0x01095714; // retail PartitionFilterPolygonTrigger vtable
		m_trigger = trigger;
	}

	~PartitionFilterPolygonTrigger(void)
	{
		m_vptr = 0x01083B5C; // retail PartitionFilter base vtable
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
		m_vptr = 0x01085DD0; // retail PartitionFilterSameMapStatus vtable
		m_object = object;
	}

	~PartitionFilterSameMapStatus(void)
	{
		m_vptr = 0x01083B5C; // retail PartitionFilter base vtable
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
	// ?doMoveUnitTowardsNearest@ScriptActions@@IAEXABVAsciiString@@0V2@@Z
	void doMoveUnitTowardsNearest(const AsciiString &unitName,
		const AsciiString &objectType, AsciiString triggerName);
};

void ScriptActions::doMoveUnitTowardsNearest(const AsciiString &unitName,
	const AsciiString &objectType, AsciiString triggerName)
{
	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (!object)
	{
		return;
	}

	AIUpdateInterface *ai = object->getAIUpdateInterface();
	if (!ai)
	{
		return;
	}

	const ThingTemplate *thingTemplate =
		TheThingFactory->findTemplate(objectType);
	if (!thingTemplate)
	{
		return;
	}

	PolygonTrigger *trigger =
		TheScriptEngine->getQualifiedTriggerAreaByName(triggerName);
	if (!trigger)
	{
		return;
	}

	Object *nearestObject;
	{
		PartitionFilterSameMapStatus mapFilter(object);
		PartitionFilterPolygonTrigger triggerFilter(trigger);
		PartitionFilterThing thingFilter(thingTemplate, true);

		nearestObject = ThePartitionManager->getClosestObject(
			object->getPosition(), 1000000.0f, 0,
			thingFilter.link(triggerFilter.link(&mapFilter)));
	}

	if (!nearestObject)
	{
		return;
	}

	ai->m_commands.bfmeCommand01(nearestObject, CMD_FROM_SCRIPT);
}
