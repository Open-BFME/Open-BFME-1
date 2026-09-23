// ?doSetPlayersNearestUnitOfTypeToReference@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@0@Z
// partial score=0.985 date=2026-09-23
// ?doSetPlayersNearestUnitOfTypeToReference@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@0@Z
// TEAM_SET_PLAYERS_NEAREST_UNIT_OF_TYPE_TO_REFERENCE at retail RVA 0x002F86D0.
// The action binds the nearest object of a type to a named unit reference.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

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

class Object;
class ObjectTypes;
class Player;
class Team;
class ThingTemplate;

class ScriptActionParameter
{
	friend class ScriptActions;

private:
	unsigned char m_unmodelled[0x10];
	AsciiString m_string;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) {}
	virtual ~PartitionFilter(void) {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterThing : public PartitionFilter
{
public:
	PartitionFilterThing(const ThingTemplate *thingTemplate, Bool match)
		: m_thingTemplate(thingTemplate), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_thingTemplate;
	Bool m_match;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class BfmeTeamEstimatePositionCall
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *) const;
};

class BfmeTeamControllingPlayerCall
{
public:
	Player *getControllingPlayer() const;
};

class BfmeFindClosestObjectCall
{
public:
	Object *findClosestObject(const Coord3D *, ObjectTypes *, Player *);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
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
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void bindUnitReference(Object *, const AsciiString &) = 0;

	void assignUnitReference(const AsciiString &, Object *);
};

class ScriptActions
{
protected:
	void doSetPlayersNearestUnitOfTypeToReference(
		const AsciiString &objectType,
		ScriptActionParameter *teamParameter,
		const AsciiString &referenceName);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;
extern void j_000241fe(void);
extern void j_0002369b(void);
extern void j_000414d9(void);

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000241fe;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		fn.member)(position);
}

static __forceinline Player *bfmeGetControllingPlayer(const Team *team)
{
	typedef Player *(BfmeTeamControllingPlayerCall::*Function)() const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002369b;
	return (reinterpret_cast<const BfmeTeamControllingPlayerCall *>(team)->*
		fn.member)();
}

static __forceinline Object *bfmeFindClosestObject(ScriptActions *actions,
	const Coord3D *position, ObjectTypes *objectTypes, Player *player)
{
	typedef Object *(BfmeFindClosestObjectCall::*Function)(
		const Coord3D *, ObjectTypes *, Player *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000414d9;
	return (reinterpret_cast<BfmeFindClosestObjectCall *>(actions)->*
		fn.member)(position, objectTypes, player);
}

// ?doSetPlayersNearestUnitOfTypeToReference@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@0@Z
void ScriptActions::doSetPlayersNearestUnitOfTypeToReference(
	const AsciiString &objectType, ScriptActionParameter *teamParameter,
	const AsciiString &referenceName)
{
	ScriptActions * volatile actions = this;
	ObjectTypes *objectTypes;
	Object *object;
	Team *team = TheScriptEngine->getTeamNamed(teamParameter->m_string, false);
	if (!team)
		return;

	Coord3D teamPosition;
	bfmeGetEstimateTeamPosition(team, &teamPosition);

	objectTypes = TheScriptEngine->getObjectTypes(objectType);
	if (objectTypes)
	{
		object = bfmeFindClosestObject((ScriptActions *)actions,
			&teamPosition, objectTypes,
			bfmeGetControllingPlayer(team));
	}
	else
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;

		PartitionFilterPlayer playerFilter(
			bfmeGetControllingPlayer(team), true);
		PartitionFilterThing thingFilter(thingTemplate, true);
		object = ThePartitionManager->getClosestObject(&teamPosition,
			1000000.0f, 0, thingFilter.link(&playerFilter));
	}

	if (!object)
		return;

	TheScriptEngine->assignUnitReference(referenceName, object);
	TheScriptEngine->bindUnitReference(object, referenceName);
}
