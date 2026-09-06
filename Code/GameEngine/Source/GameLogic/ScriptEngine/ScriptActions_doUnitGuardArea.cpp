// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: UNIT_GUARD_AREA_FROM_POSITION handler at retail RVA 0x00301DD0.

#include "StringInline.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

struct Coord3D
{
	float x, y, z;
};

class PolygonTrigger;

class AICommandInterface
{
public:
	void aiGuardArea(const PolygonTrigger *area, GuardMode mode,
		CommandSourceType source);
	void aiBfmeCommand44(const PolygonTrigger *area, int mode,
		CommandSourceType source, const Coord3D *position);
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
	AIUpdateInterface *getAIUpdateInterface(void) const
	{
		return m_ai;
	}
};

class Waypoint
{
public:
	unsigned char m_pad[0xC];
	Coord3D m_location;
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
	virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual Object *getUnitNamed(const AsciiString &name);
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern void j_000171c0();
extern void j_0004ad9a();

static __forceinline void bfmeGuardArea(AICommandInterface *commands,
	const PolygonTrigger *area)
{
	typedef void (AICommandInterface::*GuardAreaCall)(const PolygonTrigger *,
		GuardMode, CommandSourceType);
	union { void (*raw)(void); GuardAreaCall member; } call;
	call.raw = j_000171c0;
	(reinterpret_cast<AICommandInterface *>(commands)->*call.member)(area,
		GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}

static __forceinline void bfmeGuardAreaFromPosition(
	AICommandInterface *commands, const PolygonTrigger *area,
	const Coord3D *position)
{
	typedef void (AICommandInterface::*GuardAreaFromPositionCall)(
		const PolygonTrigger *, int, CommandSourceType, const Coord3D *);
	union { void (*raw)(void); GuardAreaFromPositionCall member; } call;
	call.raw = j_0004ad9a;
	(reinterpret_cast<AICommandInterface *>(commands)->*call.member)(area, 0,
		CMD_FROM_SCRIPT, position);
}

class ScriptActions
{
protected:
	void doUnitGuardArea(const AsciiString &unitName,
		const AsciiString &areaName, const AsciiString &waypointName);
};

void ScriptActions::doUnitGuardArea(const AsciiString &unitName,
	const AsciiString &areaName, const AsciiString &waypointName)
{
	PolygonTrigger *area = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (unit)
	{
		if (unit->getAIUpdateInterface())
		{
			if (area)
			{
				Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
				AICommandInterface *commands = &unit->getAIUpdateInterface()->m_commands;
				if (way)
					bfmeGuardAreaFromPosition(commands, area, &way->m_location);
				else
					bfmeGuardArea(commands, area);
			}
		}
	}
}
