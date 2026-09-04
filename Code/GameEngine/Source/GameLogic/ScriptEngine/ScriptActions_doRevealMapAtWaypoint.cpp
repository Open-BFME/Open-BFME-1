// cl: /DNDEBUG /DWIN32 /MD /Ireference/shims/stringinline
// Open-BFME: ScriptActions::doRevealMapAtWaypoint, retail 0x002F4290, 101 bytes.

#include "StringInline.h"

typedef bool Bool;
typedef float Real;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
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
	virtual void _terrain00() = 0; virtual void _terrain01() = 0;
	virtual void _terrain02() = 0; virtual void _terrain03() = 0;
	virtual void _terrain04() = 0; virtual void _terrain05() = 0;
	virtual void _terrain06() = 0; virtual void _terrain07() = 0;
	virtual void _terrain08() = 0; virtual void _terrain09() = 0;
	virtual void _terrain10() = 0; virtual void _terrain11() = 0;
	virtual void _terrain12() = 0; virtual void _terrain13() = 0;
	virtual void _terrain14() = 0; virtual void _terrain15() = 0;
	virtual void _terrain16() = 0; virtual void _terrain17() = 0;
	virtual void _terrain18() = 0; virtual void _terrain19() = 0;
	virtual void _terrain20() = 0; virtual void _terrain21() = 0;
	virtual void _terrain22() = 0; virtual void _terrain23() = 0;
	virtual void _terrain24() = 0; virtual void _terrain25() = 0;
	virtual void _terrain26() = 0; virtual void _terrain27() = 0;
	virtual void _terrain28() = 0; virtual void _terrain29() = 0;
	virtual void _terrain30() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
};

class PartitionManager
{
public:
	void doShroudReveal(const Coord3D *position, Real radius,
		UnsignedInt playerMask);
	void undoShroudReveal(const Coord3D *position, Real radius,
		UnsignedInt playerMask);
};

extern TerrainLogic *TheTerrainLogic;
extern BfmeScriptEngine_getPlayerMaskFromAsciiString *TheScriptEngine;
extern PartitionManager *TheShroudManager;

class ScriptActions
{
protected:
	void doRevealMapAtWaypoint(const AsciiString &waypointName,
		Real radiusToReveal, const AsciiString &playerName);
};

void ScriptActions::doRevealMapAtWaypoint(const AsciiString &waypointName,
	Real radiusToReveal, const AsciiString &playerName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (way)
	{
		UnsignedShort playerMask =
			TheScriptEngine->getPlayerMaskFromAsciiString(playerName, 0);
		TheShroudManager->doShroudReveal(&way->m_location,
			radiusToReveal, playerMask);
		TheShroudManager->undoShroudReveal(&way->m_location,
			radiusToReveal, playerMask);
	}
}
