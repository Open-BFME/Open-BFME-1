// ?rva002f9a80@ScriptActions@@IAEPAVObject@@VAsciiString@@00_N@Z
// partial score=0.2 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// ScriptActions object-nearest action, retail 0x002F9A80, 382 bytes.
//
// Reached through executeAction's ILT 0x00037C31. Resolves a team by name
// (ScriptEngine::getTeamNamed, vtable+0x44), estimates that team's position
// (the same BfmeTeamXQ::bfmeEstimateXQ thunk 0x241FE
// ScriptActions_doTeamGuardNearestKindof.cpp calls as
// bfmeGetEstimateTeamPosition), resolves a player mask from an AsciiString
// name (ScriptEngineGetPlayerMaskFromAsciiString.cpp's
// getPlayerMaskFromAsciiString), then for each player in that mask calls
// ScriptActions::findClosestObject (proven at
// ScriptActions_findClosestObject.cpp) with an object-type-list resolved via
// TheScriptEngine's vtable+0x50; on a miss it falls back to
// BfmeThingFactory::findTemplate and a hand-built PartitionFilterPlayer
// query through PartitionManager::bfmeGo1050D. No BFME action-template name
// is proven for this shape, so it keeps the address token.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned short PlayerMaskType;

#include "StringInline.h"

class Object;
class Player;
class ThingTemplate;
class Team;

struct Coord3D
{
	Real x, y, z;
	Coord3D(void) { }
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) { }
};

class ObjectTypes;

class PartitionFilter
{
public:
	PartitionFilter(void) : m_next(0) { }
	virtual ~PartitionFilter(void) { }
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
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
extern BfmeThingFactory *TheThingRegistry;

class PartitionManagerLike
{
public:
	void bfmeGo1050D(PartitionFilter *filter, UnsignedInt maxDistanceBits,
		Int zero, const ThingTemplate *thing);
};
extern PartitionManagerLike *ThePartitionManager;

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};
extern PlayerList *ThePlayers;

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual Team *getTeamNamed(AsciiString name, Bool exact);	// slot 17, vtable+0x44
	virtual void slot18(); virtual void slot19();
	virtual ObjectTypes *getObjectTypeListNamed(const AsciiString &name);	// slot 20, vtable+0x50
	virtual PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name, Bool *matched);	// slot 21, vtable+0x54... placeholder
};
extern ScriptEngine *TheScriptEngine;

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team, Coord3D *position)
{
	extern void j_000241fe(void);
	typedef Coord3D *(ScriptEngine::*Function)(Coord3D *);
	union { void (*raw)(void); Function member; } function;
	function.raw = j_000241fe;
	return (reinterpret_cast<ScriptEngine *>(team)->*function.member)(position);
}

class ScriptActions
{
protected:
	Object *findClosestObject(const Coord3D *position, ObjectTypes *objectTypes, Player *player);
	Object *rva002f9a80(AsciiString teamName, AsciiString objectOrThingName,
		AsciiString skirmishPlayerName, Bool unusedFlag);
};

Object *ScriptActions::rva002f9a80(AsciiString teamName, AsciiString objectOrThingName,
	AsciiString skirmishPlayerName, Bool unusedFlag)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return 0;

	Coord3D position;
	bfmeGetEstimateTeamPosition(team, &position);

	Bool matchedSpecial = false;
	PlayerMaskType mask = TheScriptEngine->getPlayerMaskFromAsciiString(skirmishPlayerName, &matchedSpecial);
	if (mask == 0)
		return 0;

	Object *result = 0;
	while (mask)
	{
		Player *player = ThePlayers->getEachPlayerFromMask(mask);

		ObjectTypes *objectTypes = TheScriptEngine->getObjectTypeListNamed(objectOrThingName);
		if (objectTypes)
		{
			result = findClosestObject(&position, objectTypes, player);
		}
		else
		{
			const ThingTemplate *thing = TheThingRegistry->findTemplate(objectOrThingName);
			if (thing)
			{
				PartitionFilterPlayer playerFilter(player, true);
				ThePartitionManager->bfmeGo1050D(&playerFilter, 0x49742400u, 0, thing);
			}
		}
	}

	return result;
}
