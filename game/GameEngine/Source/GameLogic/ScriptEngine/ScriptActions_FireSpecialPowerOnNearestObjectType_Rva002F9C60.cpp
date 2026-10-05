// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// FIRE_SPECIAL_POWER_ON_NEAREST_OBJECTTYPE, retail RVA 0x002F9C60, 249 bytes.
// executeAction (0x00303BF0) arm 445 calls this body through ILT 0x00039B30
// with the four parameter strings; ScriptEngine::init registers template 445
// as FIRE_SPECIAL_POWER_ON_NEAREST_OBJECTTYPE. It is the sibling of the
// _BY_PLAYER handler at 0x002F9A80 without the owning-player filter. The
// original method spelling is unproven, so the name keeps the address.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class ObjectTypes;
class Player;
class ScriptActions;
class Team;
class ThingTemplate;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) { }
	virtual ~PartitionFilter(void) { }
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterThing : public PartitionFilter
{
public:
	PartitionFilterThing(const ThingTemplate *thingTemplate, Bool match)
		: m_thingTemplate(thingTemplate), m_match(match) { }

protected:
	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_thingTemplate;
	Bool m_match;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class ThingFactory;

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class BfmeAsciiStringArg : public AsciiString
{
public:
	BfmeAsciiStringArg(const AsciiString &that) : AsciiString(that) {}
	~BfmeAsciiStringArg();
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
	virtual ObjectTypes *getObjectTypes(const AsciiString &name) = 0;
};

class BfmeNamedApplyCall
{
public:
	void apply(void *owner, const AsciiString &name, Object *target);
};

extern ScriptEngine *TheScriptEngine;
extern ThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;
extern void j_000241fe(void);
extern void j_000414d9(void);
extern void j_0004799c(void);

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	class BfmeTeamEstimatePositionCall
	{
	public:
		Coord3D *getEstimateTeamPosition(Coord3D *) const;
	};
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union { void (*raw)(void); Function member; } function;
	function.raw = j_000241fe;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		function.member)(position);
}

static __forceinline Object *bfmeFindClosestObject(ScriptActions *actions,
	const Coord3D *position, ObjectTypes *objectTypes, Player *player)
{
	class BfmeFindClosestObjectCall
	{
	public:
		Object *findClosestObject(const Coord3D *, ObjectTypes *, Player *);
	};
	typedef Object *(BfmeFindClosestObjectCall::*Function)(
		const Coord3D *, ObjectTypes *, Player *);
	union { void (*raw)(void); Function member; } function;
	function.raw = j_000414d9;
	return (reinterpret_cast<BfmeFindClosestObjectCall *>(actions)->*
		function.member)(position, objectTypes, player);
}

static __forceinline void bfmeApplyNamed(ScriptActions *actions,
	const AsciiString &owner, const AsciiString &name, Object *target)
{
	typedef void (BfmeNamedApplyCall::*Function)(void *, const AsciiString &,
		Object *);
	union { void (*raw)(void); Function member; } function;
	function.raw = j_0004799c;
	(reinterpret_cast<BfmeNamedApplyCall *>(actions)->*function.member)(
		(void *)&owner, name, target);
}

class ScriptActions
{
protected:
	void rva002F9C60(const AsciiString &player, const AsciiString &specialPower,
		const AsciiString &objectType, const AsciiString &teamName);
};

// ?rva002F9C60@ScriptActions@@IAEXABVAsciiString@@000@Z
void ScriptActions::rva002F9C60(const AsciiString &player,
	const AsciiString &specialPower, const AsciiString &objectType,
	const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D teamPosition;
	bfmeGetEstimateTeamPosition(team, &teamPosition);

	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectType);
	Object *object;
	if (objectTypes)
	{
		object = bfmeFindClosestObject(this, &teamPosition, objectTypes, 0);
	}
	else
	{
		const ThingTemplate *thingTemplate =
			((BfmeThingFactory *)TheThingFactory)->findTemplate(objectType);
		if (!thingTemplate)
			return;

		PartitionFilterThing thingFilter(thingTemplate, true);
		object = ThePartitionManager->getClosestObject(&teamPosition,
			1000000.0f, 0, &thingFilter);
	}

	if (object)
		bfmeApplyNamed(this, player, specialPower, object);
}
