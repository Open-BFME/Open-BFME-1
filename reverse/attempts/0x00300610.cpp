// ?doNamedMoveToWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z
// partial score=0.98 date=2026-09-08
// Clean C++ recovery of ScriptActions::doNamedMoveToWaypoint.
// Retail RVA 0x00300610, 127 bytes.

typedef bool Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AsciiString
{
	void *m_data;
};

class Object;

class AsciiStringVX
{
	public:
	AsciiStringVX(const AsciiStringVX &other);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((AsciiStringVX *)this)->AsciiStringVX::AsciiStringVX(
			*(const AsciiStringVX *)&that);
	}

	~BfmeAsciiStringArg();

private:
	char *m_text;
};

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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		unsigned int xValue = other.x;
		unsigned int yValue = other.y;
		unsigned int zValue = other.z;
		x = xValue;
		y = yValue;
		z = zValue;
	}

	unsigned int x;
	unsigned int y;
	unsigned int z;
};

class Waypoint
{
public:
	unsigned char m_beforeLocation[0x0c];
	Coord3D m_location;
};

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
	virtual Waypoint *getWaypointByName(BfmeAsciiStringArg name) = 0;
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *position, int commandSource);
};

class AIUpdateInterface
{
public:
	void clearWaypointQueue();

	unsigned char m_beforeCommands[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x204);
	}
};

class BfmeObjectStopView
{
public:
	void bfmeStop1027();
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;

class ScriptActions
{
protected:
	void doNamedMoveToWaypoint(const AsciiString &unit,
		const AsciiString &waypoint);
};

// ?doNamedMoveToWaypoint@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doNamedMoveToWaypoint(const AsciiString &unit,
	const AsciiString &waypoint)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (!theObj)
		return;

	Waypoint *theWaypoint = TheTerrainLogic->getWaypointByName(waypoint);
	if (!theWaypoint)
		return;

	unsigned int destinationX = theWaypoint->m_location.x;
	unsigned int destinationY = theWaypoint->m_location.y;
	_ReadWriteBarrier();
	AIUpdateInterface *aiUpdate = theObj->getAIUpdateInterface();
	unsigned int destinationZ = theWaypoint->m_location.z;
	unsigned int destination[3];
	destination[0] = destinationX;
	destination[1] = destinationY;
	destination[2] = destinationZ;
	if (!aiUpdate)
		return;

	aiUpdate->clearWaypointQueue();
	((BfmeObjectStopView *)theObj)->bfmeStop1027();
	AICommandInterface *commands = &aiUpdate->m_commands;
	commands->aiMoveToPosition((const Coord3D *)destination, 1);
}
