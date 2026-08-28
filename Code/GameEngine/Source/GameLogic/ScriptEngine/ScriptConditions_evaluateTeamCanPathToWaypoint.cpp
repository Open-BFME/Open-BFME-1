// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of ScriptConditions::evaluateTeamCanPathToWaypoint.

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = -1
};

struct Coord3D;
class Object;
class Pathfinder;
class Team;
class Waypoint;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Object *getFirstItemIn_TeamMemberList() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation(void) const
	{
		return (const Coord3D *)((const char *)this + 0x0C);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool slowDoesPathExist(Object *, const Coord3D *, const Coord3D *, ObjectID);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return *(Pathfinder **)((char *)this + 0x0C);
	}
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamCanPathToWaypoint(Parameter *, Parameter *);
};

// ?evaluateTeamCanPathToWaypoint@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamCanPathToWaypoint(
	Parameter *pTeamParm, Parameter *pWaypointParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam) {
		return false;
	}

	Object *firstUnit = theTeam->getFirstItemIn_TeamMemberList();
	if (!firstUnit) {
		return false;
	}

	Waypoint *waypoint = TheTerrainLogic->getWaypointByName(pWaypointParm->getString());
	if (!waypoint) {
		return false;
	}

	return TheAI->pathfinder()->slowDoesPathExist(
		firstUnit, firstUnit->getPosition(), waypoint->getLocation(), (ObjectID)0);
}
