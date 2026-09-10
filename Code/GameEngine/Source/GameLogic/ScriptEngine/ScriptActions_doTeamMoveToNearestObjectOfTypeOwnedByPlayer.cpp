// ?doTeamMoveToNearestObjectOfTypeOwnedByPlayer@ScriptActions@@IAEXABVAsciiString@@0PAVParameter@@@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// TEAM_MOVE_TO_NEAREST_OBJECT_OF_TYPE_OWNED_BY_PLAYER at retail RVA
// 0x002F60A0 (519 bytes).
//
// Action-template arm 394 supplies a team name, object type, and player
// Parameter.  The action resolves the team's average position, walks the
// player mask, and submits a move packet for the nearest matching object.

#include "StringInline.h"
#include <math.h>

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef float Real;

class Object;
class Player;
class Parameter;
class ThingTemplate;
class ObjectTypes;
class AIGroup;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

};

class Object
{
public:
	virtual void slot0(void);

	unsigned char m_unreconstructed[0x34];
	Coord3D m_position;

	const Coord3D *getPosition(void) const { return &m_position; }
};

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

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *) const;
	void getTeamAsAIGroup(AIGroup *group);
};

class AI
{
public:
	AIGroup *createGroup(void);
};

// BFME adds getTeamNamed at slot 17 and getObjectTypes at slot 20.
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
	UnsignedShort unidentified_0034DB40(Parameter *parameter);
};

struct Rva0015A190Packet
{
	void *m_first;
	unsigned char m_flag;
	void *m_objA;
	void *m_objB;
};

typedef char PacketSizeCheck[sizeof(Rva0015A190Packet) == 16 ? 1 : -1];
typedef char CoordSizeCheck[sizeof(Coord3D) == 12 ? 1 : -1];
typedef char PlayerFilterSizeCheck[sizeof(PartitionFilterPlayer) == 16 ? 1 : -1];
typedef char ThingFilterSizeCheck[sizeof(PartitionFilterThing) == 16 ? 1 : -1];

class Rva0015A190Owner
{
public:
	void applyPacket(Rva0015A190Packet *packet, Int command);
};

extern ScriptEngine *TheScriptEngine;
extern BfmeThingFactory *TheThingFactory;
extern PartitionManager *ThePartitionManager;
extern PlayerList *ThePlayerList;
extern AI *TheAI;

class ScriptActions
{
protected:
	// The real helper is the matched ScriptActions member at 0x002F5D50.
	// Keeping this declaration direct lets the resolver select retail's ILT
	// encoding without a generated alias or function-pointer punning.
	Object *findClosestObject(const Coord3D *position,
		ObjectTypes *objectTypes, Player *player);

	void doTeamMoveToNearestObjectOfTypeOwnedByPlayer(
		const AsciiString &teamName, const AsciiString &objectType,
		Parameter *playerParameter);
};

// ?doTeamMoveToNearestObjectOfTypeOwnedByPlayer@ScriptActions@@IAEXABVAsciiString@@0PAVParameter@@@Z
void ScriptActions::doTeamMoveToNearestObjectOfTypeOwnedByPlayer(
	const AsciiString &teamName, const AsciiString &objectType,
	Parameter *playerParameter)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	Coord3D teamPosition;
	team->getEstimateTeamPosition_000EDCD0(&teamPosition);

	ObjectTypes *objectTypes = TheScriptEngine->getObjectTypes(objectType);
	const ThingTemplate *thingTemplate = 0;
	if (!objectTypes)
	{
		thingTemplate = TheThingFactory->findTemplate(objectType);
		if (!thingTemplate)
			return;
	}

	Object *bestObject = 0;
	Real bestDistance = 99999.0f;
	UnsignedShort playerMask =
		TheScriptEngine->unidentified_0034DB40(playerParameter);
	if (!playerMask)
		return;

	while (playerMask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		Object *object = 0;
		if (objectTypes)
		{
			object = findClosestObject(&teamPosition, objectTypes, player);
		}
		else
		{
			PartitionFilterPlayer playerFilter(player, true);
			PartitionFilterThing thingFilter(thingTemplate, true);
			object = ThePartitionManager->getClosestObject(&teamPosition,
				1000000.0f, 0, thingFilter.link(&playerFilter));
		}

		if (object)
		{
			const Coord3D *objectPosition = object->getPosition();
			Real delta[3];
			delta[0] = objectPosition->x;
			delta[1] = objectPosition->y;
			delta[2] = objectPosition->z;
			delta[0] -= teamPosition.x;
			delta[1] -= teamPosition.y;
			delta[2] -= teamPosition.z;
			Real distance = (Real)sqrt(
				delta[0] * delta[0] + delta[1] * delta[1] +
				delta[2] * delta[2]);
			if (!bestObject || distance < bestDistance)
			{
				bestDistance = distance;
				bestObject = object;
			}
		}
	}

	if (!bestObject)
		return;

	AIGroup *group = TheAI->createGroup();
	if (!group)
		return;

	team->getTeamAsAIGroup(group);
	{
		Rva0015A190Packet packet;
		packet.m_first = (void *)bestObject->getPosition();
		packet.m_flag = 0;
		packet.m_objA = 0;
		packet.m_objB = 0;
		((Rva0015A190Owner *)group)->applyPacket(&packet, 1);
	}
}
