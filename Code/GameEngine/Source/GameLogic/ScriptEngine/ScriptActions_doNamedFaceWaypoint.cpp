// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef bool Bool;

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	unsigned char m_pad[0xc];
	Coord3D m_location;
};

class AICommandInterface
{
public:
	void aiFacePosition(const Coord3D *position, int source);
};

class AIUpdateInterface
{
public:
	void clearWaypointQueue();

private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_command;
};

class Object
{
public:
	void leaveGroup();
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

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
};

class TerrainLogicByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

class ScriptEngineByValue
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0;
	virtual Object *getUnitNamedByValue(AsciiString name) = 0;
};

class ScriptActions
{
protected:
	void doNamedFaceWaypoint(const AsciiString &, const AsciiString &);
};

// ?doNamedFaceWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z
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
