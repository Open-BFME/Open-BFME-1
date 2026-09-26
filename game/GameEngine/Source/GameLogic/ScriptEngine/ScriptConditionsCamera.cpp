// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateCameraHitSpecificSplineWaypoint@ScriptConditions@@IAE_NPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateCameraEnteredArea@ScriptConditions@@IAE_NPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The two ScriptConditions conditions that ask where the camera is:
//
//   0x003260E0  evaluateCameraHitSpecificSplineWaypoint  has it reached this waypoint
//   0x00326130  evaluateCameraEnteredArea                is it inside this trigger area
//
// Both go through TheTacticalView, and that is the drift one file cannot show.
// One declared the global as a View with 27 slots ending at cameraHitWaypoint;
// the other declared the same global as a "TacticalView" with 70 slots ending
// at get3DCameraPosition, and nothing in either file said they were the same
// object. Declared once, both pinned slots sit in one vtable: cameraHitWaypoint
// at slot 26 (vtable+0x68) and get3DCameraPosition at slot 69 (vtable+0x114).
//
// The waypoint body's AsciiString had no members at all while the area body's
// held a char*; both pass one by value to a virtual, so the delegating slice
// is what they share.

typedef int Int;
typedef bool Bool;
typedef int WaypointID;

struct Coord3D
{
	float x, y, z;
};

struct ICoord3D
{
	Int x, y, z;
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	WaypointID getID(void) const { return m_id; }

private:
	unsigned char m_vftable[0x4];
	WaypointID m_id;					// this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0;	// slot 22, vtable+0x58
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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
	virtual Waypoint *getWaypointByName(AsciiString) = 0;		// slot 31, vtable+0x7C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
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
	virtual Bool cameraHitWaypoint(WaypointID) = 0;			// slot 26, vtable+0x68
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void get3DCameraPosition(Coord3D *) = 0;		// slot 69, vtable+0x114
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateCameraHitSpecificSplineWaypoint(Parameter *);
	Bool evaluateCameraEnteredArea(Parameter *);
};

// ?evaluateCameraHitSpecificSplineWaypoint@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateCameraHitSpecificSplineWaypoint(Parameter *waypointParm)
{
	Waypoint *waypoint = TheTerrainLogic->getWaypointByName(
		waypointParm->getString());
	if (waypoint) {
		View *view = TheTacticalView;
		WaypointID id = waypoint->getID();
		return view->cameraHitWaypoint(id);
	}

	return false;
}

// ?evaluateCameraEnteredArea@ScriptConditions@@IAE_NPAVParameter@@@Z
Bool ScriptConditions::evaluateCameraEnteredArea(Parameter *pTriggerParm)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(
		pTriggerParm->getString());
	if (pTrig) {
		Coord3D camera;
		TheTacticalView->get3DCameraPosition(&camera);
		ICoord3D iCoord;
		iCoord.x = (Int)camera.x;
		iCoord.y = (Int)camera.y;
		iCoord.z = (Int)camera.z;
		return pTrig->pointInTrigger(iCoord);
	}
	return false;
}
