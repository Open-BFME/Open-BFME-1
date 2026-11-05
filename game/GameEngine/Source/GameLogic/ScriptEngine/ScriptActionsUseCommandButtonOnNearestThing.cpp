// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x002FDAC0 (416 B): file-static nearest-object command helper shared by
// the named and team NEAREST_OBJECTTYPE script actions. Keeping it static next to
// its callers lets VC7.1 choose retail's private ABI (unit ESI, button EDI, template on stack).

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

class Object;
class ObjectTypes;
class Player;
class Team;

#include "../command_source_type.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BfmeOverridableView
{
public:
	void *m_vtable;
	BfmeOverridableView *m_nextOverride;
	const BfmeOverridableView *getFinalOverride() const;
};

class ThingTemplate : public BfmeOverridableView
{
public:
	unsigned char m_pad08[0xc8];
	UnsignedInt m_flagsD0;
};

// ZH Override.h: dereferencing yields null or the template's final override.
template <class T>
class OVERRIDE
{
public:
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return bfmeFinalOf(m_overridable);
	}
	operator const T *() const { return operator*(); }

private:
	const T *m_overridable;
};

// Object's DLINK pointer-to-member layout, as in inputs/reference/shims/objectdlink/
// ObjectDlinkPmf.h: vptr @ +0, DLINK base @ +4, vbptr-carrying base @ +0x68, so
// &Object::dlink_next_TeamMemberList encodes {0x00401140, -100, 0}. The field base
// keeps this TU's members at their retail offsets inside that skeleton.
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectFields
{
public:
	OVERRIDE<ThingTemplate> m_template;
	unsigned char m_beforePosition[0x30];
	Coord3D m_position;
	unsigned char m_afterPosition[0x64 - 0x40];
};

class CommandButton
{
public:
	Bool isReady(const Object *sourceObject) const;
	UnsignedInt getOptions() const { return m_options; }

	unsigned char m_pad00[0x18];
	UnsignedInt m_options;
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectFields, public BfmeObjectVbptrCarrier
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	const ThingTemplate *getTemplate() const { return m_template; }

	Bool bfmeCanUseCommandButton(const CommandButton *button) const;
	void doCommandButtonAtObject(const CommandButton *button, Object *target,
		CommandSourceType source, Bool playVoiceResponse);
	void doCommandButtonAtPosition(const CommandButton *button,
		const Coord3D *position, CommandSourceType source,
		Bool playVoiceResponse);
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *object) : m_object(object) {}

protected:
	virtual Bool allow(Object *object);

private:
	const Object *m_object;
};

class PartitionFilterThing : public PartitionFilter
{
public:
	PartitionFilterThing(const ThingTemplate *thingTemplate, Bool match)
		: m_tThing(thingTemplate), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_tThing;
	Bool m_match;
};

class PartitionFilterValidCommandButtonTarget : public PartitionFilter
{
public:
	PartitionFilterValidCommandButtonTarget(Object *source,
		const CommandButton *button, Bool match, CommandSourceType sourceType)
		: m_source(source), m_button(button), m_match(match),
		  m_sourceType(sourceType) {}

protected:
	virtual Bool allow(Object *object);

private:
	Object *m_source;
	const CommandButton *m_button;
	Bool m_match;
	CommandSourceType m_sourceType;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class TerrainLogic
{
public:
	Coord3D *queryPointAt001A62D0(const Coord3D *, Real, Bool, Bool);
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
// Retail's global at 0x012EF1D8 is EA's `ThingFactory *TheThingFactory` (name
// from ?findByTemplateID@ThingFactory@@QAEPBVThingTemplate@@, class declared in
// common/System/game_engine_subsystems.h).  The member call below goes through
// the address-derived BfmeThingFactory view, reached by a cast.
class ThingFactory;
extern ThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;
extern TerrainLogic *TheTerrainLogic;

extern void j_000022bb();
extern void j_000414d9();
extern void j_0002990b();

class ScriptActions;

static __forceinline Object *bfmeFindClosestObject(const Coord3D *position,
	ObjectTypes *objectTypes, Player *player, ScriptActions *actions)
{
	class FindClosestObjectCall
	{
	public:
		Object *findClosestObject(const Coord3D *, ObjectTypes *, Player *);
	};
	typedef Object *(FindClosestObjectCall::*Function)(
		const Coord3D *, ObjectTypes *, Player *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000414d9;
	return (reinterpret_cast<FindClosestObjectCall *>(actions)->*fn.member)(
		position, objectTypes, player);
}

static __forceinline const ThingTemplate *bfmeGetFinalOverride(
	const BfmeOverridableView *nextOverride)
{
	typedef const BfmeOverridableView *(BfmeOverridableView::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000022bb;
	return (const ThingTemplate *)
		(reinterpret_cast<const BfmeOverridableView *>(nextOverride)->*
		fn.member)();
}

// ?useCommandButtonOnNearestThing_002FDAC0@@YAXPAVObject@@PBVCommandButton@@PBVThingTemplate@@@Z
// Position-targeted buttons fire at the nearest match; others validate the target and
// fall back to a terrain point when the template's 0xD0 flag 0x20000000 is set.
static void useCommandButtonOnNearestThing_002FDAC0(Object *unit,
	const CommandButton *button, const ThingTemplate *thingTemplate)
{
	if ((Bool)((button->getOptions() >> 5) & 1))
	{
		Object *target;
		{
			PartitionFilterSameMapStatus mapFilter(unit);
			PartitionFilterThing thingFilter(thingTemplate, true);
			target = ThePartitionManager->getClosestObject(unit->getPosition(),
				1000000.0f, 0, thingFilter.link(&mapFilter));
		}
		if (target)
			unit->doCommandButtonAtPosition(button, target->getPosition(),
				CMD_FROM_SCRIPT, false);
	}
	else
	{
		Object *target;
		{
			PartitionFilterSameMapStatus mapFilter(unit);
			PartitionFilterValidCommandButtonTarget validFilter(unit, button,
				true, CMD_FROM_SCRIPT);
			PartitionFilterThing thingFilter(thingTemplate, true);
			target = ThePartitionManager->getClosestObject(unit->getPosition(),
				1000000.0f, 0, thingFilter.link(validFilter.link(&mapFilter)));
		}
		if (!target)
		{
			if (thingTemplate->m_flagsD0 & 0x20000000)
			{
				Coord3D *point = TheTerrainLogic->queryPointAt001A62D0(
					unit->getPosition(), 10000000.0f, true, true);
				if (point)
					unit->doCommandButtonAtPosition(button, point,
						CMD_FROM_SCRIPT, false);
			}
		}
		else
		{
			unit->doCommandButtonAtObject(button, target, CMD_FROM_SCRIPT, false);
		}
	}
}

// Overridable::getFinalOverride inlined one level; the recursion calls the retail body.
static __forceinline const ThingTemplate *bfmeFinalOf(const ThingTemplate *t)
{
	if (t->m_nextOverride)
		return bfmeGetFinalOverride(t->m_nextOverride);
	return t;
}

class ScriptActions
{
protected:
	void doNamedUseCommandButtonOnNearestObjectType(
		const AsciiString &unitName, const AsciiString &commandAbility,
		const AsciiString &objectTypeName);
	void doTeamUseCommandButtonOnNearestObjectType(
		const AsciiString &teamName, const AsciiString &commandAbility,
		const AsciiString &objectTypeName);
};

// Retail 0x002FDCD0 (173 B), action 429; supplies the helper's private-ABI call site.
void ScriptActions::doNamedUseCommandButtonOnNearestObjectType(
	const AsciiString &unitName, const AsciiString &commandAbility,
	const AsciiString &objectTypeName)
{
	const ThingTemplate *thingTemplate;
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	if (ObjectTypes *objectTypes =
		TheScriptEngine->getObjectTypes(objectTypeName))
	{
		Object *nearest = bfmeFindClosestObject(unit->getPosition(), objectTypes,
			0, this);
		if (!nearest)
			return;

		thingTemplate = nearest->getTemplate();
	}
	else
	{
		thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate(objectTypeName);
	}

	if (!thingTemplate)
		return;

	const CommandButton *button =
		TheControlBar->findCommandButton(commandAbility);
	if (!button)
		return;
	if (!button->isReady(unit))
		return;
	if (!unit->bfmeCanUseCommandButton(button))
		return;

	useCommandButtonOnNearestThing_002FDAC0(unit, button, thingTemplate);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// Team member-list slice (head at +0x0C), as in the matched team walks.
class Team
{
private:
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// Retail 0x002FE110 (273 B, ret 0xC), the team twin of the named action above:
// executeAction's TEAM_ALL_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE arm calls it.
// The template comes from the object nearest the team's estimated position (or
// the factory), then every ready member runs the shared helper.
void ScriptActions::doTeamUseCommandButtonOnNearestObjectType(
	const AsciiString &teamName, const AsciiString &commandAbility,
	const AsciiString &objectTypeName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	const CommandButton *button =
		TheControlBar->findCommandButton(commandAbility);
	if (!button)
		return;

	const ThingTemplate *thingTemplate;
	if (ObjectTypes *objectTypes =
		TheScriptEngine->getObjectTypes(objectTypeName))
	{
		class FindClosestObjectCall
		{
		public:
			Object *findClosestObject(const Coord3D *, ObjectTypes *, Player *);
		};
		class EstimateTeamPositionCall
		{
		public:
			Coord3D *getEstimateTeamPosition(Coord3D *) const;
		};
		typedef Object *(FindClosestObjectCall::*FindFunction)(
			const Coord3D *, ObjectTypes *, Player *);
		typedef Coord3D *(EstimateTeamPositionCall::*EstimateFunction)(
			Coord3D *) const;
		union { void (*raw)(void); FindFunction member; } find;
		union { void (*raw)(void); EstimateFunction member; } estimate;
		find.raw = j_000414d9;
		estimate.raw = j_0002990b;

		Coord3D teamPosition;
		Object *nearest = (reinterpret_cast<FindClosestObjectCall *>(this)->*
			find.member)(
			(reinterpret_cast<const EstimateTeamPositionCall *>(team)->*
				estimate.member)(&teamPosition),
			objectTypes, 0);
		if (!nearest)
			return;

		thingTemplate = nearest->getTemplate();
	}
	else
	{
		thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate(objectTypeName);
	}

	if (!thingTemplate)
		return;

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *member = iter.cur();
		if (button->isReady(member))
			useCommandButtonOnNearestThing_002FDAC0(member, button, thingTemplate);
	}
}
