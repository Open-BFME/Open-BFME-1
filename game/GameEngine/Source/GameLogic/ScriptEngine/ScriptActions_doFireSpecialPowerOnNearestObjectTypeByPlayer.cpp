// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// FIRE_SPECIAL_POWER_ON_NEAREST_OBJECTTYPE_BY_PLAYER, retail RVA 0x002F9A80.
// Action template 446 resolves a team position and the nearest matching object.
// The final named apply body is shared with the BFME named-apply cluster.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;
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
	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_thingTemplate;
	Bool m_match;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) { }
	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
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

class ScriptEnginePlayerMask
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class BfmeNamedApplyCall
{
public:
	void apply(void *owner, const AsciiString &name, Object *target);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern PlayerList *ThePlayers;
extern PartitionManager *ThePartitionManager;
extern void j_000241fe(void);
extern void j_0002ee60(void);
extern void j_000414d9(void);
extern void j_0004799c(void);
extern void j_0004b290(void);

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

static __forceinline Player *bfmeGetEachPlayer(PlayerList *players,
	PlayerMaskType &mask)
{
	typedef Player *(PlayerList::*Function)(PlayerMaskType &);
	union { void (*raw)(void); Function member; } function;
	function.raw = j_0002ee60;
	return (players->*function.member)(mask);
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

static __forceinline PlayerMaskType bfmeGetPlayerMask(ScriptEngine *engine,
	const AsciiString &name)
{
	typedef PlayerMaskType (ScriptEnginePlayerMask::*Function)(
		const AsciiString &, Bool *);
	union { void (*raw)(void); Function member; } function;
	function.raw = j_0004b290;
	return (reinterpret_cast<ScriptEnginePlayerMask *>(engine)->*
		function.member)(name, 0);
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
	void rva002F9A80(
		const AsciiString &player, const AsciiString &specialPower,
		const AsciiString &objectType, const AsciiString &teamName,
		const AsciiString &owningPlayer);
};

// ?rva002F9A80@ScriptActions@@IAEXABVAsciiString@@0000@Z
void ScriptActions::rva002F9A80(
	const AsciiString &player, const AsciiString &specialPower,
	const AsciiString &objectType, const AsciiString &teamName,
	const AsciiString &owningPlayer)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D teamPosition;
	bfmeGetEstimateTeamPosition(team, &teamPosition);

	PlayerMaskType playerMask = bfmeGetPlayerMask(TheScriptEngine,
		owningPlayer);
	if (!playerMask)
		return;

	while (playerMask)
	{
		Player *thePlayer = bfmeGetEachPlayer(ThePlayers, playerMask);
		ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectType);
		Object *object;
		if (objectTypes)
		{
			object = bfmeFindClosestObject(this, &teamPosition, objectTypes,
				thePlayer);
		}
		else
		{
			const ThingTemplate *thingTemplate =
				TheThingFactory->findTemplate(objectType);
			if (!thingTemplate)
				continue;

			PartitionFilterPlayer playerFilter(thePlayer, true);
			PartitionFilterThing thingFilter(thingTemplate, true);
			object = ThePartitionManager->getClosestObject(&teamPosition,
				1000000.0f, 0, thingFilter.link(&playerFilter));
		}

		if (object)
		{
			bfmeApplyNamed(this, player, specialPower, object);
			return;
		}
	}
}
