// cl: /DNDEBUG /MD /EHsc
// readable body of ?doRotateCameraTowardWaypoint@ScriptActions@@IAEXABVAsciiString@@MMM_N@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME5: clean C++ reconstruction of ScriptActions::doRotateCameraTowardWaypoint.

typedef int Int;
typedef float Real;
typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

public:
	struct Header;
	Header *m_data;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation(void) const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0xc);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void d00(void) {}
	virtual void d01(void) {}
	virtual void d02(void) {}
	virtual void d03(void) {}
	virtual void d04(void) {}
	virtual void d05(void) {}
	virtual void d06(void) {}
	virtual void d07(void) {}
	virtual void d08(void) {}
	virtual void d09(void) {}
	virtual void d10(void) {}
	virtual void d11(void) {}
	virtual void d12(void) {}
	virtual void d13(void) {}
	virtual void d14(void) {}
	virtual void d15(void) {}
	virtual void d16(void) {}
	virtual void d17(void) {}
	virtual void d18(void) {}
	virtual void d19(void) {}
	virtual void d20(void) {}
	virtual void d21(void) {}
	virtual void d22(void) {}
	virtual void d23(void) {}
	virtual void d24(void) {}
	virtual void d25(void) {}
	virtual void d26(void) {}
	virtual void d27(void) {}
	virtual void d28(void) {}
	virtual void d29(void) {}
	virtual void d30(void) {}
	virtual Waypoint *getWaypointByName(AsciiString);
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
	virtual void d00(void) {}
	virtual void d01(void) {}
	virtual void d02(void) {}
	virtual void d03(void) {}
	virtual void d04(void) {}
	virtual void d05(void) {}
	virtual void d06(void) {}
	virtual void d07(void) {}
	virtual void d08(void) {}
	virtual void d09(void) {}
	virtual void d10(void) {}
	virtual void d11(void) {}
	virtual void d12(void) {}
	virtual void d13(void) {}
	virtual void d14(void) {}
	virtual void d15(void) {}
	virtual void d16(void) {}
	virtual void d17(void) {}
	virtual void d18(void) {}
	virtual void d19(void) {}
	virtual void d20(void) {}
	virtual void d21(void) {}
	virtual void d22(void) {}
	virtual void d23(void) {}
	virtual void d24(void) {}
	virtual void d25(void) {}
	virtual void d26(void) {}
	virtual void d27(void) {}
	virtual void d28(void) {}
	virtual void d29(void) {}
	virtual void d30(void) {}
	virtual void d31(void) {}
	virtual void d32(void) {}
	virtual void d33(void) {}
	virtual void d34(void) {}
	virtual void d35(void) {}
	virtual void d36(void) {}
	virtual void d37(void) {}
	virtual void d38(void) {}
	virtual void d39(void) {}
	virtual void d40(void) {}
	virtual void d41(void) {}
	virtual void d42(void) {}
	virtual void d43(void) {}
	virtual void d44(void) {}
	virtual void d45(void) {}
	virtual void d46(void) {}
	virtual void d47(void) {}
	virtual void d48(void) {}
	virtual void d49(void) {}
	virtual void d50(void) {}
	virtual void d51(void) {}
	virtual void rotateCameraTowardPosition(const Coord3D *, Int, Real, Real, Bool) = 0;
};

extern View *TheTacticalView;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doRotateCameraTowardWaypoint(const AsciiString &, Real, Real, Real, Bool);
};

// ?doRotateCameraTowardWaypoint@ScriptActions@@IAEXABVAsciiString@@MMM_N@Z
void ScriptActions::doRotateCameraTowardWaypoint(const AsciiString &waypointName,
	Real sec, Real easeIn, Real easeOut, Bool reverseRotation)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (way == 0)
		return;
	TheTacticalView->rotateCameraTowardPosition(way->getLocation(), sec * 1000.0f,
		easeIn * 1000.0f, easeOut * 1000.0f, reverseRotation);
}
