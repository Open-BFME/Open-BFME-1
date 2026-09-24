// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// ?doTeamSetPlayersNearestUnitOfTypeToReference@ScriptActions@@IAEXABVAsciiString@@PAVParameter@@0@Z
// TEAM_SET_PLAYERS_NEAREST_UNIT_OF_TYPE_TO_REFERENCE at retail RVA 0x002F86D0.
// The action binds the nearest object of a type to a named unit reference.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class ObjectTypes;
class Player;
class ThingTemplate;

class Parameter
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
		: m_tThing(thingTemplate), m_match(match) {}

	virtual Bool allow(Object *object);

private:
	const ThingTemplate *m_tThing;
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
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *) const;
	Player *getControllingPlayer() const;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

// BFME adds getTeamNamed at slot 17, getObjectTypes at slot 20 and
// an unidentified method at slot 29 (body 0x00349730, still an unnamed dump).
class ScriptEngine
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual Team *getTeamNamed(AsciiString name, Bool exact);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual ObjectTypes *getObjectTypes(const AsciiString &name);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void vslot29(Object *object, const AsciiString &name);

	void assignUnitReference(const AsciiString &name, Object *object);
};

class ScriptActions
{
protected:
	// The matched ScriptActions member at 0x002F5D50, reached through its ILT.
	Object *findClosestObject(const Coord3D *position,
		ObjectTypes *objectTypes, Player *player);

	void doTeamSetPlayersNearestUnitOfTypeToReference(
		const AsciiString &objectType,
		Parameter *teamParameter,
		const AsciiString &referenceName);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;

// ?doTeamSetPlayersNearestUnitOfTypeToReference@ScriptActions@@IAEXABVAsciiString@@PAVParameter@@0@Z
void ScriptActions::doTeamSetPlayersNearestUnitOfTypeToReference(
	const AsciiString &objectType, Parameter *teamParameter,
	const AsciiString &referenceName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParameter->m_string, false);
	if (!team)
		return;

	Coord3D teamPosition;
	team->getEstimateTeamPosition_000EDCD0(&teamPosition);

	Object *object;
	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectType);
	if (objectTypes)
	{
		object = findClosestObject(&teamPosition, objectTypes,
			team->getControllingPlayer());
	}
	else
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;

		PartitionFilterPlayer playerFilter(team->getControllingPlayer(), true);
		PartitionFilterThing thingFilter(thingTemplate, true);
		object = ThePartitionManager->getClosestObject(&teamPosition,
			1000000.0f, 0, thingFilter.link(&playerFilter));
	}

	if (!object)
		return;

	TheScriptEngine->assignUnitReference(referenceName, object);
	TheScriptEngine->vslot29(object, referenceName);
}
