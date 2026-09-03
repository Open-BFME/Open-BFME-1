// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: UNIT_TELEPORT_TO_WAYPOINT handler at retail RVA 0x002F7220.

#include "StringInline.h"

typedef bool Bool;

class Object;
class Waypoint;

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class BFMERetailScriptEngineVTable
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class TerrainLogicVTable
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual void _slot26() = 0;
	virtual void _slot27() = 0;
	virtual void _slot28() = 0;
	virtual void _slot29() = 0;
	virtual void _slot30() = 0;
	virtual Waypoint *getWaypointByName(BfmeAsciiStringArg name) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine : public BFMERetailScriptEngineVTable
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic : public TerrainLogicVTable
{
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
private:
	char m_beforePosition[0xc];

public:
	Coord3D m_position;
};

class StructureCollapsePosition
{
};

class StructureCollapseRetailObject
{
public:
	void setPosition(const StructureCollapsePosition &position, Bool unknown);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doUnitTeleportToWaypoint(const AsciiString &unitName,
		const AsciiString &waypointName);
};

void ScriptActions::doUnitTeleportToWaypoint(const AsciiString &unitName,
	const AsciiString &waypointName)
{
	Object *object = TheScriptEngine->getUnitNamed(unitName);
	if (object)
	{
		Waypoint *waypoint = TheTerrainLogic->getWaypointByName(waypointName);
		if (waypoint)
		{
			const StructureCollapsePosition *position =
				(const StructureCollapsePosition *)&waypoint->m_position;
			((StructureCollapseRetailObject *)object)->setPosition(*position, false);
		}
	}
}
