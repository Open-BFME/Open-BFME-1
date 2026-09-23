// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?getWaypointByName@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?getClosestWaypointOnPath@TerrainLogic@@UAEPAVWaypoint@@PBUCoord3D@@VAsciiString@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?isPurposeOfPath@TerrainLogic@@UAE_NPAVWaypoint@@VAsciiString@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?getWaterHandleByName@TerrainLogic@@UAEPBVWaterHandle@@VAsciiString@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

// The four TerrainLogic lookups that take a name the map author typed and walk
// a global list comparing it:
//
//   getWaypointByName        0x001AA900  vtable slot 31  waypoint of that name
//   getClosestWaypointOnPath 0x001A8C70  vtable slot 33  nearest waypoint on a path
//   getWaypointByPath       0x001A8EB0  vtable slot 34  first waypoint on a path
//   isPurposeOfPath          0x001AAAC0  vtable slot 35  does a waypoint carry a label
//   getWaterHandleByName     0x001AAFD0  vtable slot 26  water trigger of that name
//
// Slots read off retail's TerrainLogic vtable at 0x0109C428, which the
// destructor at 0x001ADD90 installs; the numbering is load-bearing, because
// getClosestWaypointOnPath dispatches its null-position case through slot 34.
//
// Each of the four used to live alone and carry its own account of the classes
// all four share. The AsciiString header was spelled two ways (four shorts, or
// an int followed by two shorts) for the same eight bytes; the class was
// spelled four ways, once plain, once deriving from an "AsciiStringCompareShim"
// invented to name compare(), once privately deriving from StringBase<char> to
// name compareNoCase(), once with compare() written out inline. Waypoint was
// two disjoint classes, one with getName() over a 0x1c-byte prefix, one with
// only the three path-label getters. And three of the four declared TerrainLogic
// with a SINGLE virtual, which silently placed the body at vtable slot 0.
//
// Declared once below: an eight-byte AsciiString header whose characters begin
// at +0x08, retail's own string members left out of line (the StringBase<char>
// copy at 0x00887B60, the destructor at 0x00887940, compare at 0x000220C5,
// compare(const char *) at 0x0004B01A and compareNoCase at 0x00027471), a
// Waypoint holding its location at +0x0c and its chain link at +0x1c, and the
// TerrainLogic vtable slice the slot numbers above come from.

#include <string.h>

#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct BfmeAsciiStringData
{
	unsigned short m_refCount;		// +0x00
	unsigned short m_numCharsAllocated;	// +0x02
	unsigned short m_numChars;		// +0x04
	unsigned short m_unreconstructed_06;
	// the characters follow at +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/string_base.h
// BFME's AsciiString holds nothing of its own, so a caller that copies one
// encodes the StringBase<char> copy constructor at 0x00887B60 directly and the
// derivation has to be visible for this TU to reach that body rather than the
// AsciiString-named forwarder at 0x0005EE50.
template <typename T> class StringBase
{
public:
	StringBase(const StringBase<T> &other);	// retail 0x00887B60

	const BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();						// retail 0x00887940

	__declspec(nothrow) int compare(const AsciiString &other) const;		// retail 0x000220C5
	int compare(const char *text) const;					// retail 0x0004B01A
	__declspec(nothrow) int compareNoCase(const AsciiString &other) const;	// retail 0x00027471

	Bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_numChars == 0;
	}
};

class TerrainLogic;

// Waypoint::getName returns by value, and the destructor of that return is the
// same StringBase body at 0x00887940 -- named apart here so this TU does not
// also emit the AsciiString spelling the ledger resolves through a thunk.
class BfmeWaypointNameString
{
friend class TerrainLogic;

private:
	~BfmeWaypointNameString();

public:
	const BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	BfmeWaypointNameString getName(void) const;
	AsciiString getPathLabel1(void) const;
	AsciiString getPathLabel2(void) const;
	AsciiString getPathLabel3(void) const;

	Coord3D *getLocation(void) const
	{
		return (Coord3D *)&m_location;
	}

	Waypoint *getNext(void) const
	{
		return m_next;
	}
	Waypoint *getLinkSource(void) const
	{
		return m_linkSource;
	}

private:
	unsigned char m_unreconstructed_00[0x0c];
	Coord3D m_location;			// +0x0c
	unsigned char m_unreconstructed_18[4];
	Waypoint *m_next;			// +0x1c
	unsigned char m_unreconstructed_20[0x40 - 0x20];
	Waypoint *m_linkSource;		// +0x40, set by addWaypointLink
};

class PolygonTrigger;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class WaterHandle
{
public:
	PolygonTrigger *m_polygon;
};

// The name and water-area offsets are independently visible in the retail
// body: m_triggerName is at +0x08 and m_isWaterArea is at +0x32.  The other
// members are deliberately not modeled because this TU only dispatches
// getNext, isWaterArea, and getWaterHandle.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	PolygonTrigger *getNext() const
	{
		return m_nextPolygonTrigger;
	}

	const AsciiString &getTriggerName() const
	{
		return m_triggerName;
	}

	Bool isWaterArea() const
	{
		return m_isWaterArea;
	}

	const WaterHandle *getWaterHandle() const;

private:
	void *m_vtable;
	PolygonTrigger *m_nextPolygonTrigger;
	AsciiString m_triggerName;			// +0x08
	unsigned char m_unreconstructed_0c[0x26];
	Bool m_isWaterArea;				// +0x32
};

struct BfmePolygonTriggerTable
{
	PolygonTrigger *m_head;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// Vtable slice of retail's 0x0109C428, forty-eight slots wide; only the four
// bodies this TU owns are given here, and the rest stay pure so no vftable is
// emitted.  Slot 34 is named because getClosestWaypointOnPath calls it.
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
	virtual const WaterHandle *getWaterHandleByName(AsciiString name);
	virtual void _tl_27(void) = 0;
	virtual void _tl_28(void) = 0;
	virtual void _tl_29(void) = 0;
	virtual Waypoint *getFirstWaypoint(void) = 0;
	virtual Waypoint *getWaypointByName(AsciiString name);
	virtual Waypoint *getWaypointByID(int id) = 0;
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos,
		AsciiString label);
	virtual Waypoint *getWaypointByPath(AsciiString label) = 0;
	virtual Bool isPurposeOfPath(Waypoint *waypoint, AsciiString label);
};

extern Waypoint *g_waypointListHead;

extern "C" BfmePolygonTriggerTable *g_bfmePolygonTriggerTable;
extern "C" WaterHandle g_bfmeGridWaterHandle;

// getWaypointByName compares the by-value AsciiString argument against the
// by-value name Waypoint::getName hands back, and retail wrote that comparison
// out rather than calling the string body.
static Int compareWaypointName(const BfmeWaypointNameString &self,
	const AsciiString &other)
{
	const BfmeAsciiStringData *otherData = other.m_data;
	Int otherLength;
	const char *otherChars;
	if (otherData) {
		otherLength = otherData->m_numChars;
		otherChars = (const char *)(otherData + 1);
	} else {
		otherLength = 0;
		otherChars = "";
	}
	const BfmeAsciiStringData *selfData = self.m_data;
	Int selfLength;
	if (selfData)
		selfLength = *(volatile const unsigned short *)((const char *)selfData + 4);
	else
		selfLength = 0;
	register unsigned int selfAddress;
	if (self.m_data)
		selfAddress = (unsigned int)(self.m_data + 1);
	else
		selfAddress = (unsigned int)"";
	Int length = selfLength < otherLength ? selfLength : otherLength;
	Int result = memcmp((const char *)selfAddress, otherChars, length);
	if (result == 0)
		result = selfLength - otherLength;
	return result;
}

static Int compareWaypointPathLabel(const AsciiString &self,
	const AsciiString &other)
{
	const BfmeAsciiStringData *selfData = self.m_data;
	Int selfLength;
	if (selfData)
		selfLength = *(volatile const unsigned short *)((const char *)selfData + 4);
	else
		selfLength = 0;
	register unsigned int selfAddress;
	if (self.m_data)
		selfAddress = (unsigned int)(self.m_data + 1);
	else
		selfAddress = (unsigned int)"";
	const BfmeAsciiStringData *otherData = other.m_data;
	Int otherLength;
	const char *otherChars;
	if (otherData) {
		otherLength = otherData->m_numChars;
		otherChars = (const char *)(otherData + 1);
	} else {
		otherLength = 0;
		otherChars = "";
	}
	Int length = otherLength < selfLength ? otherLength : selfLength;
	Int result = _memicmp(otherChars, (const char *)selfAddress, length);
	if (result != 0)
		return result;
	return otherLength - selfLength;
}

// getWaterHandleByName inlines the same comparison over two AsciiStrings, in
// its own shape: the early return on an unequal prefix is retail's.
static Int compareTriggerName(const AsciiString &self, const AsciiString &other)
{
	const BfmeAsciiStringData *otherData = other.m_data;
	Int otherLength = otherData ? otherData->m_numChars : 0;
	const char *otherChars = otherData ? (const char *)(otherData + 1) : "";
	Int selfLength = self.m_data ? self.m_data->m_numChars : 0;
	const char *selfChars = self.m_data ? (const char *)(self.m_data + 1) : "";
	Int length = selfLength < otherLength ? selfLength : otherLength;
	Int result = memcmp(selfChars, otherChars, length);
	if (result != 0)
		return result;
	return selfLength - otherLength;
}

// TerrainLogic::getWaypointByName, retail 0x001AA900.
//
// BFME keeps the waypoint chain in the same process-global list used by the
// Waypoint constructor/destructor bodies.
Waypoint *TerrainLogic::getWaypointByName(AsciiString name)
{
	if (name.isEmpty())
		return 0;

	for (Waypoint *way = g_waypointListHead; way; way = way->getNext())
	{
		if (compareWaypointName(way->getName(), name) == 0)
			return way;
	}

	return 0;
}

// TerrainLogic::getClosestWaypointOnPath, retail 0x001A8C70.
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

// TerrainLogic::getWaypointByPath, retail 0x001A8EB0.
Waypoint *TerrainLogic::getWaypointByPath(AsciiString label)
{
	if (label.isEmpty())
		return 0;

	for (Waypoint *way = g_waypointListHead; way; way = way->getNext()) {
		Bool match = compareWaypointPathLabel(way->getPathLabel1(), label) == 0 ||
			label.compareNoCase(way->getPathLabel2()) == 0 ||
			label.compareNoCase(way->getPathLabel3()) == 0;
		if (match) {
			while (way->getLinkSource())
				way = way->getLinkSource();
			return way;
		}
	}
	return 0;
}

// TerrainLogic::isPurposeOfPath, retail 0x001AAAC0.
//
// All three labels are compared even once one has matched, which is why this
// reads as three separate ifs rather than a short-circuited or.
Bool TerrainLogic::isPurposeOfPath(Waypoint *pWay, AsciiString label)
{
	if (label.isEmpty() || pWay == 0)
		return false;

	Bool match = false;
	if (label.compare(pWay->getPathLabel1()) == 0)
		match = true;
	if (label.compare(pWay->getPathLabel2()) == 0)
		match = true;
	if (label.compare(pWay->getPathLabel3()) == 0)
		match = true;

	return match;
}

// TerrainLogic::getWaterHandleByName, retail 0x001AAFD0.
const WaterHandle *TerrainLogic::getWaterHandleByName(AsciiString name)
{
	if (name.compare("Water Grid") == 0)
		return &g_bfmeGridWaterHandle;

	PolygonTrigger *trig = g_bfmePolygonTriggerTable->m_head;
	while (trig)
	{
		if (compareTriggerName(trig->getTriggerName(), name) == 0 && trig->isWaterArea())
			return trig->getWaterHandle();
		trig = trig->getNext();
	}

	return 0;
}
