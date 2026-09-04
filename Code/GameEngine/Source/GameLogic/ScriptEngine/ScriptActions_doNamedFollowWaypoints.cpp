// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: BFME's named follow-waypoints body at retail 0x00301A60.

#include "StringInline.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

class AICommandInterface
{
public:
	void aiFollowWaypointPath(const Waypoint *way, CommandSourceType source);
};

class AIUpdateInterface
{
private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

class Object
{
public:
	void leaveGroup();

private:
	unsigned char m_pad0[0x38];

public:
	Coord3D m_position;
	unsigned char m_pad1[0x204 - 0x44];

public:
	AIUpdateInterface *m_ai;
};

class Waypoint
{
};

class TerrainLogicByValue
{
public:
	virtual void _0() = 0; virtual void _1() = 0; virtual void _2() = 0;
	virtual void _3() = 0; virtual void _4() = 0; virtual void _5() = 0;
	virtual void _6() = 0; virtual void _7() = 0; virtual void _8() = 0;
	virtual void _9() = 0; virtual void _10() = 0; virtual void _11() = 0;
	virtual void _12() = 0; virtual void _13() = 0; virtual void _14() = 0;
	virtual void _15() = 0; virtual void _16() = 0; virtual void _17() = 0;
	virtual void _18() = 0; virtual void _19() = 0; virtual void _20() = 0;
	virtual void _21() = 0; virtual void _22() = 0; virtual void _23() = 0;
	virtual void _24() = 0; virtual void _25() = 0; virtual void _26() = 0;
	virtual void _27() = 0; virtual void _28() = 0; virtual void _29() = 0;
	virtual Waypoint *getFirstWaypoint() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
	virtual Waypoint *getWaypointByID(int id) = 0;
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos,
		AsciiString label) = 0;
};

class ScriptEngine
{
public:
	virtual void _0() = 0; virtual void _1() = 0; virtual void _2() = 0;
	virtual void _3() = 0; virtual void _4() = 0; virtual void _5() = 0;
	virtual void _6() = 0; virtual void _7() = 0; virtual void _8() = 0;
	virtual void _9() = 0; virtual void _10() = 0; virtual void _11() = 0;
	virtual void _12() = 0; virtual void _13() = 0; virtual void _14() = 0;
	virtual void _15() = 0; virtual void _16() = 0; virtual void _17() = 0;
	virtual void _18() = 0; virtual void _19() = 0; virtual void _20() = 0;
	virtual void _21() = 0; virtual void _22() = 0; virtual void _23() = 0;
	virtual void _24() = 0; virtual void _25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

class ScriptActions
{
protected:
	void doNamedFollowWaypoints(const AsciiString &, const AsciiString &);
};

void ScriptActions::doNamedFollowWaypoints(const AsciiString &unitName,
	const AsciiString &waypointPathLabel)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theUnit) {
		return;
	}

	Coord3D pos;
	pos.x = theUnit->m_position.x;
	pos.y = theUnit->m_position.y;
	pos.z = theUnit->m_position.z;
	AIUpdateInterface *aiUpdate = theUnit->m_ai;
	if (!aiUpdate) {
		return;
	}

	Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(&pos,
		waypointPathLabel);
	if (!way) {
		return;
	}

	theUnit->leaveGroup();
	aiUpdate->m_command.aiFollowWaypointPath(way, CMD_FROM_SCRIPT);
}
