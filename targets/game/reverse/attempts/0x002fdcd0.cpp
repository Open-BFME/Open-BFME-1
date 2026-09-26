// ?d_002fdcd0@@YAXXZ
// partial score=0.55 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// NAMED_USE_COMMANDBUTTON_ON_NEAREST_OBJECTTYPE, executeAction template 429.
// Retail RVA 0x002FDCD0, 173 bytes.  The action registration and the sole
// retail executeAction caller identify this as the named-unit/object-type
// nearest-command action.  The object/template offsets below are the fields
// read by this body; they are kept as TU-local views because the owning BFME
// layouts are not complete in the public headers.
// The private d_002FDAC0 ABI remains unresolved: retail enters with EDI=button,
// inherited ESI=unit, and one stack ThingTemplate argument, while its body
// reads [EDI+0x18], saves ESI, forms ESI+0x38, and consumes that stack word.
// The wrapper below therefore records semantic recovery only, not a truthful
// one-argument cdecl declaration; score 0.55 reflects that unresolved ABI.

#include "StringInline.h"

typedef bool Bool;

class Object;
class ObjectTypes;
class Player;

class BfmeOverridableView
{
public:
	void *m_vtable;
	BfmeOverridableView *m_nextOverride;
	const BfmeOverridableView *getFinalOverride() const;
};

class ThingTemplate : public BfmeOverridableView
{
};

struct Coord3D
{
	float x;
	float y;
	float z;
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
	virtual void slot17() = 0;
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

class CommandButton
{
public:
	Bool isReady(const Object *sourceObject) const;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_beforePosition[0x30];
	Coord3D m_position;

	const Coord3D *getPosition() const
	{
		return &m_position;
	}

	Bool bfmeCanUseCommandButton(const CommandButton *button) const;
	const ThingTemplate *getTemplate() const { return m_template; }
};

// The override chain is read from the object template at +4.  The final
// override ILT is an existing matched route, but this action reaches it with
// the link object as its receiver, so keep the call ABI local to this TU.
extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
#define TheThingFactory (*(BfmeThingFactory **)0x012EF1D8)

extern void d_002fdac0();
extern void j_000022bb();
extern void j_000414d9();

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

static __forceinline void bfmeApplyNearestObjectTypeAction(
	const ThingTemplate *thingTemplate)
{
	typedef void (*Function)(const ThingTemplate *);
	union { void (*raw)(void); Function typed; } fn;
	fn.raw = d_002fdac0;
	fn.typed(thingTemplate);
}

class ScriptActions
{
protected:
	void doNamedUseCommandButtonOnNearestObjectType(
		const AsciiString &unitName, const AsciiString &commandAbility,
		const AsciiString &objectTypeName);
};

// ?doNamedUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doNamedUseCommandButtonOnNearestObjectType(
	const AsciiString &unitName, const AsciiString &commandAbility,
	const AsciiString &objectTypeName)
{
	const ThingTemplate *thingTemplate;
	const AsciiString *objectType = &objectTypeName;
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	if (ObjectTypes *objectTypes =
		TheScriptEngine->getObjectTypes(*objectType))
	{
		Object *nearest = bfmeFindClosestObject(unit->getPosition(), objectTypes,
			0, this);
		if (!nearest)
			return;

		thingTemplate = nearest->getTemplate();
		if (thingTemplate)
		{
			if (thingTemplate->m_nextOverride)
				thingTemplate = bfmeGetFinalOverride(
					thingTemplate->m_nextOverride);
		}
		else
		{
			thingTemplate = 0;
		}
	}
	else
	{
		thingTemplate = TheThingFactory->findTemplate(*objectType);
	}

	if (!thingTemplate)
		return;

	register const CommandButton *button =
		TheControlBar->findCommandButton(commandAbility);
	if (!button)
		return;
	if (!button->isReady(unit))
		return;
	if (!unit->bfmeCanUseCommandButton(button))
		return;

	bfmeApplyNearestObjectTypeAction(thingTemplate);
}
