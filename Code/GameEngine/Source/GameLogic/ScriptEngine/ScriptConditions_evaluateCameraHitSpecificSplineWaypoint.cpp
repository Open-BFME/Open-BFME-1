// cl: /DNDEBUG /MD /EHsc
// BFME reconstruction of the camera waypoint-arrival condition.

typedef bool Bool;
typedef int WaypointID;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Waypoint
{
public:
	WaypointID getID(void) const { return m_id; }

private:
	unsigned char m_vftable[0x4];
	WaypointID m_id;
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
	virtual Waypoint *getWaypointByName(AsciiString) = 0;
};

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
	virtual Bool cameraHitWaypoint(WaypointID) = 0;
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptConditions
{
protected:
	Bool evaluateCameraHitSpecificSplineWaypoint(Parameter *);
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
