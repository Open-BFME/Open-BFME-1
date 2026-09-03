// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?getClosestWaypointOnPath@TerrainLogic@@UAEPAVWaypoint@@PBUCoord3D@@VAsciiString@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// TerrainLogic::getClosestWaypointOnPath, retail body 0x001A8C70.

typedef bool Bool;
typedef float Real;

template <typename NUM>
inline NUM sqr(NUM x)
{
	return x * x;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed_06;
};

template <typename T> class StringBase;

class AsciiString;

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	__declspec(nothrow) int compareNoCase(const StringBase<T> &other) const;

	private:
	const BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	using StringBase<char>::compareNoCase;

	Bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_numChars == 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	AsciiString getPathLabel1(void) const;
	AsciiString getPathLabel2(void) const;
	AsciiString getPathLabel3(void) const;

	Coord3D *getLocation(void) const
	{
		return (Coord3D *)((const char *)this + 0x0c);
	}

	Waypoint *getNext(void) const
	{
		return *(Waypoint **)((const char *)this + 0x1c);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void _tl_00(void) = 0;
	virtual void _tl_01(void) = 0;
	virtual void _tl_02(void) = 0;
	virtual void _tl_03(void) = 0;
	virtual void _tl_04(void) = 0;
	virtual void _tl_05(void) = 0;
	virtual void _tl_06(void) = 0;
	virtual void _tl_07(void) = 0;
	virtual void _tl_08(void) = 0;
	virtual void _tl_09(void) = 0;
	virtual void _tl_10(void) = 0;
	virtual void _tl_11(void) = 0;
	virtual void _tl_12(void) = 0;
	virtual void _tl_13(void) = 0;
	virtual void _tl_14(void) = 0;
	virtual void _tl_15(void) = 0;
	virtual void _tl_16(void) = 0;
	virtual void _tl_17(void) = 0;
	virtual void _tl_18(void) = 0;
	virtual void _tl_19(void) = 0;
	virtual void _tl_20(void) = 0;
	virtual void _tl_21(void) = 0;
	virtual void _tl_22(void) = 0;
	virtual void _tl_23(void) = 0;
	virtual void _tl_24(void) = 0;
	virtual void _tl_25(void) = 0;
	virtual void _tl_26(void) = 0;
	virtual void _tl_27(void) = 0;
	virtual void _tl_28(void) = 0;
	virtual void _tl_29(void) = 0;
	virtual Waypoint *getFirstWaypoint(void) = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
	virtual Waypoint *getWaypointByID(int id) = 0;
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos,
		AsciiString label);
	virtual Waypoint *getWaypointByPath(AsciiString label) = 0;
	virtual Bool isPurposeOfPath(Waypoint *waypoint, AsciiString label) = 0;
};

extern Waypoint *g_waypointListHead;

Waypoint *TerrainLogic::getClosestWaypointOnPath(const Coord3D *pos,
	AsciiString label)
{
	Real distSqr;
	Waypoint *pClosestWay = 0;
	register Bool match = false;

	if (pos == 0) {
		return getWaypointByPath(label);
	}

	distSqr = 0;
	if (label.isEmpty())
		return 0;

	for (Waypoint *way = g_waypointListHead; way; way = way->getNext()) {
		match = false;
		if (label.compareNoCase(way->getPathLabel1()) == 0)
			match = true;
		if (label.compareNoCase(way->getPathLabel2()) == 0)
			match = true;
		if (label.compareNoCase(way->getPathLabel3()) == 0)
			match = true;

		if (match) {
			Real x = way->getLocation()->x;
			Real y = way->getLocation()->y;
			Real newDistSqr = sqr(y - pos->y) + sqr(x - pos->x);
			if (pClosestWay == 0) {
				pClosestWay = way;
				distSqr = newDistSqr;
			} else if (newDistSqr < distSqr) {
				pClosestWay = way;
				distSqr = newDistSqr;
			}
		}
	}

	return pClosestWay;
}
