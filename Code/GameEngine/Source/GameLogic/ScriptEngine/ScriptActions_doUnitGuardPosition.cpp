// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: UNIT_GUARD_POSITION at retail RVA 0x00301CE0.

#include "StringInline.h"

typedef bool Bool;

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint
{
public:
	unsigned char m_pad[0xC];
	Coord3D m_location;
};

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode guardMode,
		CommandSourceType cmdSource);
};

class AIUpdateInterface
{
private:
	unsigned char m_pad[0x20];

public:
	AICommandInterface m_commands;
};

class Object
{
private:
	unsigned char m_pad[0x204];

public:
	AIUpdateInterface *m_ai;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class TerrainLogic
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

class ScriptActions
{
protected:
	void doUnitGuardPosition(const AsciiString &unitName,
		const AsciiString &waypointName);
};

void ScriptActions::doUnitGuardPosition(const AsciiString &unitName,
	const AsciiString &waypointName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (unit)
	{
		AIUpdateInterface *ai = unit->m_ai;
		if (ai)
		{
			if (way)
			{
				Coord3D position;
				position.x = way->m_location.x;
				position.y = way->m_location.y;
				position.z = way->m_location.z;
				ai->m_commands.aiGuardPosition(&position,
					GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
			}
		}
	}
}
