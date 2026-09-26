// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// SET_REF_TO_NEREST_TEAM_OF_TYPE_OWNED_BY_PLAYER at retail RVA 0x002F7050.
//
// Action template 491 supplies an object-type list, a player, a team, and a
// unit reference.  The retail body resolves the player's mask, finds the
// team's position, searches the requested type near that position, and binds
// the resulting object to the reference.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned short PlayerMaskType;

class Object;
class ObjectTypes;
class Player;
class Team;
class ThingTemplate;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class ScriptActionParameter
{
	friend class ScriptActions;

private:
	unsigned char m_unmodelled[0x10];
	AsciiString m_string;
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

class Object
{
public:
	virtual void slot0(void);

	unsigned char m_unreconstructed[0x34];
	Coord3D m_position;

	const Coord3D *getPosition(void) const { return &m_position; }
};

class ThingTemplate;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
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

class Team
{
};

class BfmeTeamEstimatePositionCall
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *) const;
};

class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

class BfmePlayerListGetPlayerFromMask
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
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

extern ScriptEngine *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern PlayerList *ThePlayerList;
extern PartitionManager *ThePartitionManager;
extern void j_0002990b(void);
extern void j_000414d9(void);
extern void j_0001dde5(void);

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002990b;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		fn.member)(position);
}

static __forceinline Player *bfmeGetPlayerFromMask(PlayerList *players,
	PlayerMaskType mask)
{
	typedef Player *(BfmePlayerListGetPlayerFromMask::*Function)(
		PlayerMaskType);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001dde5;
	return (reinterpret_cast<BfmePlayerListGetPlayerFromMask *>(players)->*
		fn.member)(mask);
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
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000414d9;
	return (reinterpret_cast<BfmeFindClosestObjectCall *>(actions)->*
		fn.member)(position, objectTypes, player);
}

class ScriptActions
{
protected:
	void doSetRefToNearestTeamOfTypeOwnedByPlayer(
		ScriptActionParameter *objectTypeList,
		ScriptActionParameter *player,
		ScriptActionParameter *team,
		ScriptActionParameter *reference);
};

// ?doSetRefToNearestTeamOfTypeOwnedByPlayer@ScriptActions@@IAEXPAVScriptActionParameter@@000@Z
void ScriptActions::doSetRefToNearestTeamOfTypeOwnedByPlayer(
	ScriptActionParameter *objectTypeList,
	ScriptActionParameter *player,
	ScriptActionParameter *team,
	ScriptActionParameter *reference)
{
	PlayerMaskType playerMask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	Player *thePlayer = bfmeGetPlayerFromMask(ThePlayerList, playerMask);
	if (!thePlayer)
		return;

	Team *theTeam = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (!theTeam)
		return;

	Coord3D teamPosition;
	bfmeGetEstimateTeamPosition(theTeam, &teamPosition);

	ObjectTypes *objectTypes =
		TheScriptEngine->getObjectTypes(objectTypeList->m_string);
	Object *object;
	if (objectTypes)
	{
		object = bfmeFindClosestObject(this, &teamPosition, objectTypes,
			thePlayer);
	}
	else
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(objectTypeList->m_string);
		if (!thingTemplate)
			return;

		PartitionFilterPlayer playerFilter(thePlayer, true);
		PartitionFilterThing thingFilter(thingTemplate, true);
		object = ThePartitionManager->getClosestObject(&teamPosition,
			1000000.0f, 0, thingFilter.link(&playerFilter));
	}

	if (!object)
		return;

	TheScriptEngine->assignUnitReference(reference->m_string, object);
	TheScriptEngine->bindUnitReference(object, reference->m_string);
}
