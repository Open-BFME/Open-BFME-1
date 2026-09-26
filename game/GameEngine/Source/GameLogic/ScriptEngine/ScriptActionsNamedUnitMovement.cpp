// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// readable body of ?doNamedFaceNamed@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doNamedFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// The four actions that give one named unit a movement or facing order:
//
//   0x00301A60  doNamedFollowWaypoints       aiFollowWaypointPath
//   0x00301B00  doNamedFollowWaypointsExact  aiFollowWaypointPathExact
//   0x00303100  doNamedFaceNamed             aiFaceObject
//   0x00303180  doNamedFaceWaypoint          aiFacePosition
//
// All four resolve the unit through ScriptEngine slot 26, reach its
// AICommandInterface at AIUpdateInterface+0x20, take it out of whatever group
// it is in, and issue exactly one command. They differ only in that command and
// in what they look up to feed it.

#include "StringInline.h"

typedef bool Bool;

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	unsigned char m_pad[0xc];
	Coord3D m_location;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFollowWaypointPath(const Waypoint *way, CommandSourceType source);
	void aiFollowWaypointPathExact(const Waypoint *way,
		CommandSourceType source);
	void aiFaceObject(Object *object, CommandSourceType source);
	// The pin at 0x00040732 spells this last argument H, a plain int, not the
	// W4CommandSourceType@@ its three neighbours take.
	void aiFacePosition(const Coord3D *position, int source);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void clearWaypointQueue();

private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void leaveGroup();

private:
	unsigned char m_pad0[0x38];

public:
	Coord3D m_position;
	unsigned char m_pad1[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
	// Slot 27 is not a rival spelling of slot 26: it is the adjacent entry that
	// takes the name by value, and doNamedFaceNamed calls both in one body.
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;
};

// The name the by-value call site casts through; it is this same vtable.
typedef ScriptEngine ScriptEngineByValue;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedFollowWaypoints(const AsciiString &, const AsciiString &);
	void doNamedFollowWaypointsExact(const AsciiString &, const AsciiString &);
	void doNamedFaceNamed(const AsciiString &, const AsciiString &);
	void doNamedFaceWaypoint(const AsciiString &, const AsciiString &);
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

void ScriptActions::doNamedFollowWaypointsExact(
	const AsciiString &unitName, const AsciiString &waypointPathLabel)
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
	aiUpdate->m_command.aiFollowWaypointPathExact(way, CMD_FROM_SCRIPT);
}

void ScriptActions::doNamedFaceNamed(const AsciiString &unitName, const AsciiString &faceUnitName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		Object *faceObj = ((ScriptEngineByValue *)TheScriptEngine)->getUnitNamedByValue(faceUnitName);
		if (faceObj)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				ai->clearWaypointQueue();
				obj->leaveGroup();
				ai->m_command.aiFaceObject(faceObj, CMD_FROM_SCRIPT);
			}
		}
	}
}

void ScriptActions::doNamedFaceWaypoint(const AsciiString &unitName, const AsciiString &waypointName)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		Waypoint *waypoint = ((TerrainLogicByValue *)TheTerrainLogic)->getWaypointByName(waypointName);
		if (waypoint)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				ai->clearWaypointQueue();
				obj->leaveGroup();
				ai->m_command.aiFacePosition(waypoint->getLocation(), 1);
			}
		}
	}
}
