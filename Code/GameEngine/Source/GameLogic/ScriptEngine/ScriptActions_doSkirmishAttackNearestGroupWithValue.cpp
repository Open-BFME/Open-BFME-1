// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Retail 0x002F5380 is the executeAction arm for
// doSkirmishAttackNearestGroupWithValue. The two private partition calls are
// kept as address-derived ABI views: the retail body calls the PlayerList
// relationship helper first, then the ShroudManager forwarding body at
// 0x008F7460.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short PlayerMaskType;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum Comparison
{
	COMPARISON_GREATER_EQUAL = 3,
	COMPARISON_GREATER = 4
};

enum PlayerTypes
{
	ALLOW_ENEMIES = 4
};

enum ValueOrThreat
{
	VOT_CashValue = 0
};

class Player
{
public:
	Int getPlayerIndex() const
	{
		return m_playerIndex;
	}

private:
	unsigned char m_beforePlayerIndex[0x24];
	Int m_playerIndex;
};

class AIGroup
{
public:
	bool getCenter(Coord3D *center);
	void groupAttackMoveToPosition(const Coord3D *position, Int maxShots,
		CommandSourceType commandSource);
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	Player *getControllingPlayer() const;
};

class AI
{
public:
	AIGroup *createGroup();
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16();
	virtual Team *getTeamNamed(AsciiString name, Bool exact);
};

class PlayerList
{
public:
	PlayerMaskType getPlayersWithRelationship(Int playerIndex,
		Int whichPlayerTypes, Bool exact);
};

// Engine initialization identifies TheShroudManager at VA012ED5BC;
// ThePartitionManager is a distinct global at VA012ED5B8. Retail008F7460
// forwards these five arguments through its implementation pointer at+0x0C
// to008FBD00. Keep the method address-derived pending full callee identity.
class ShroudManager
{
public:
	void rva008F7460(const Coord3D *sourceLocation, UnsignedInt allowedPlayers,
		ValueOrThreat valueType, Int valueRequired, Coord3D *outLocation);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;
extern PlayerList *ThePlayerList;
extern ShroudManager *TheShroudManager;

class ScriptActions
{
protected:
	void doSkirmishAttackNearestGroupWithValue(const AsciiString &teamName,
		Int comparison, Int value);
};

// ?doSkirmishAttackNearestGroupWithValue@ScriptActions@@IAEXABVAsciiString@@HH@Z
void ScriptActions::doSkirmishAttackNearestGroupWithValue(
	const AsciiString &teamName, Int comparison, Int value)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	team->getTeamAsAIGroup(theGroup);

	Player *player = team->getControllingPlayer();
	if (!player)
		return;

	Coord3D loc;
	Coord3D groupLoc;
	theGroup->getCenter(&groupLoc);
	if (comparison == COMPARISON_GREATER_EQUAL ||
		comparison == COMPARISON_GREATER)
	{
		TheShroudManager->rva008F7460(&groupLoc,
			ThePlayerList->getPlayersWithRelationship(
				player->getPlayerIndex(), ALLOW_ENEMIES, false),
			VOT_CashValue, value, &loc);
	}

	theGroup->groupAttackMoveToPosition(&loc, 0x7fffffff,
		CMD_FROM_SCRIPT);
}
