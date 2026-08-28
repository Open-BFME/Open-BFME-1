// cl: /DNDEBUG /MD /EHsc
// readable body of ?doTeamUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME: ScriptActions::doTeamUseCommandButtonAbilityAtWaypoint, retail
// 0x002F4B60, 144 bytes.  Ported from the Zero Hour body, which BFME kept
// verbatim except for the extra `if (!theGroup) return;` guard and the two
// BFME-only signature changes recovered here.
//
// The earlier blocker was read as "MSVC7.1 eight-byte AsciiString temporary
// construction schedule": retail pushes 0 and then a 4-byte slot, which was
// taken for the two halves of an _INTERNAL 8-byte AsciiString.  It is not.
// AsciiString is four bytes and the `push 0` is a SECOND ARGUMENT -- BFME's
// ScriptEngine::getTeamNamed is virtual slot +0x44 taking (AsciiString, Bool),
// exactly as the already-landed doTeamUseCommandButtonOnNamed sibling in this
// directory spells it.  TerrainLogic::getWaypointByName is virtual slot +0x7C
// and likewise takes its AsciiString BY VALUE, which is what produces the
// second in-place copy-ctor call; ControlBar::findCommandButton still takes a
// const reference.  Waypoint::getLocation is inline and yields waypoint+0x0C.

typedef bool Bool;

class AIGroup;
class Team;
struct Coord3D;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class CommandButton;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation(void) const { return (const Coord3D *)&m_location; }

private:
	unsigned char m_beforeLocation[0x0C];
	unsigned char m_location[0x0C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
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
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Waypoint *getWaypointByName(AsciiString) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupDoCommandButtonAtPosition(const CommandButton *, const Coord3D *, CommandSourceType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
};

extern AI *TheAI;
extern ControlBar *TheControlBar;
extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamUseCommandButtonAbilityAtWaypoint(
		const AsciiString &, const AsciiString &, const AsciiString &);
};

// ?doTeamUseCommandButtonAbilityAtWaypoint@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doTeamUseCommandButtonAbilityAtWaypoint(
	const AsciiString &team, const AsciiString &ability, const AsciiString &waypoint)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team, false);
	if (!theTeam) {
		return;
	}

	Waypoint *pWaypoint = TheTerrainLogic->getWaypointByName(waypoint);
	if (!pWaypoint) {
		return;
	}

	const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
	if (!commandButton) {
		return;
	}

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup) {
		return;
	}

	theTeam->getTeamAsAIGroup(theGroup);

	theGroup->groupDoCommandButtonAtPosition(commandButton, pWaypoint->getLocation(), CMD_FROM_SCRIPT);
}
