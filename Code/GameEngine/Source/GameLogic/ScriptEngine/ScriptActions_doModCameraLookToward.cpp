// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: ScriptActions::doModCameraLookToward, retail 0x002F8C60, 211 bytes,
// and its twin doModCameraFinalLookToward, retail 0x002F8D70, 211 bytes.
//
// Identity: executeAction's jump table reaches 0x002F8C60 from arm 32 and
// 0x002F8D70 from arm 31, which are ZH CAMERA_MOD_LOOK_TOWARD and
// CAMERA_MOD_FINAL_LOOK_TOWARD.  The arm numbering is unshifted this low in the
// table -- arm 3 is the matched VICTORY body and arms 40/41 are the matched
// create-on-team pair.  Each body is the ZH line for line: walk the waypoint
// list, compare names, copy the location and hand it to the tactical view.
//
// Own TU rather than a body in ScriptActions.cpp for two reasons:
//
//   - There is no fs:[0] SEH prologue even though getName returns a class with
//     a destructor by value, so retail compiled this TU without /EH.
//   - BFME inlines the AsciiString comparison that the reference header leaves
//     as an out-of-line operator==.  It is a three-way compare: the shorter
//     length bounds an inline memcmp and the length difference breaks the tie.
//     Both operands read the length from data+4 and the characters from data+8
//     and substitute the empty literal for a null data pointer.
#include <string.h>

#pragma intrinsic(memcmp)

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// BFME's string block: the character count is a word at data+4 and the
// characters begin at data+8.
struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;							///< retail data+0x04
	unsigned short m_unreconstructed_06;
};

// The parameter type only has to mangle as AsciiString; it is taken by
// reference here and never destroyed, so it needs no destructor.
class AsciiString
{
public:
	const BfmeAsciiStringData *m_data;
};

// Waypoint::getName returns a retail AsciiString by value.  Naming the returned
// class AsciiString would emit the destructor name that the ledger already
// resolves to a different thunk, so the returned class carries its own name and
// its destructor is pinned as an alias of the AsciiString destructor.
class BfmeWaypointNameString
{
	friend class ScriptActions;

private:
	~BfmeWaypointNameString();							///< retail AsciiString destructor 0x00887940

	const BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	BfmeWaypointNameString getName(void) const;			// ILT 0x0001026C

	Waypoint *getNext(void) const { return m_next; }

	unsigned char m_unmodelled_000[0x0C];
	Coord3D m_location;									// +0x0C
	unsigned char m_unmodelled_018[0x04];
	Waypoint *m_next;									// +0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// BFME puts getFirstWaypoint at TerrainLogic vtable slot 30.
class TerrainLogic
{
public:
	virtual void _tl_0() = 0;
	virtual void _tl_1() = 0;
	virtual void _tl_2() = 0;
	virtual void _tl_3() = 0;
	virtual void _tl_4() = 0;
	virtual void _tl_5() = 0;
	virtual void _tl_6() = 0;
	virtual void _tl_7() = 0;
	virtual void _tl_8() = 0;
	virtual void _tl_9() = 0;
	virtual void _tl_10() = 0;
	virtual void _tl_11() = 0;
	virtual void _tl_12() = 0;
	virtual void _tl_13() = 0;
	virtual void _tl_14() = 0;
	virtual void _tl_15() = 0;
	virtual void _tl_16() = 0;
	virtual void _tl_17() = 0;
	virtual void _tl_18() = 0;
	virtual void _tl_19() = 0;
	virtual void _tl_20() = 0;
	virtual void _tl_21() = 0;
	virtual void _tl_22() = 0;
	virtual void _tl_23() = 0;
	virtual void _tl_24() = 0;
	virtual void _tl_25() = 0;
	virtual void _tl_26() = 0;
	virtual void _tl_27() = 0;
	virtual void _tl_28() = 0;
	virtual void _tl_29() = 0;
	virtual Waypoint *getFirstWaypoint(void) = 0;		// slot 30, +0x78
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
// BFME puts the two camera-mod look-toward entries at slots 36 and 37.
class View
{
public:
	virtual void _v_0() = 0;
	virtual void _v_1() = 0;
	virtual void _v_2() = 0;
	virtual void _v_3() = 0;
	virtual void _v_4() = 0;
	virtual void _v_5() = 0;
	virtual void _v_6() = 0;
	virtual void _v_7() = 0;
	virtual void _v_8() = 0;
	virtual void _v_9() = 0;
	virtual void _v_10() = 0;
	virtual void _v_11() = 0;
	virtual void _v_12() = 0;
	virtual void _v_13() = 0;
	virtual void _v_14() = 0;
	virtual void _v_15() = 0;
	virtual void _v_16() = 0;
	virtual void _v_17() = 0;
	virtual void _v_18() = 0;
	virtual void _v_19() = 0;
	virtual void _v_20() = 0;
	virtual void _v_21() = 0;
	virtual void _v_22() = 0;
	virtual void _v_23() = 0;
	virtual void _v_24() = 0;
	virtual void _v_25() = 0;
	virtual void _v_26() = 0;
	virtual void _v_27() = 0;
	virtual void _v_28() = 0;
	virtual void _v_29() = 0;
	virtual void _v_30() = 0;
	virtual void _v_31() = 0;
	virtual void _v_32() = 0;
	virtual void _v_33() = 0;
	virtual void _v_34() = 0;
	virtual void _v_35() = 0;
	virtual void cameraModLookToward(Coord3D *pLoc) = 0;			// slot 36, +0x90
	virtual void cameraModFinalLookToward(Coord3D *pLoc) = 0;	// slot 37, +0x94
	virtual void _v_38() = 0;
	virtual void _v_39() = 0;
	virtual void _v_40() = 0;
	virtual void _v_41() = 0;
	virtual void _v_42() = 0;
	virtual void _v_43() = 0;
	virtual void _v_44() = 0;
	virtual void _v_45() = 0;
	virtual void _v_46() = 0;
	virtual void _v_47() = 0;
	virtual void _v_48() = 0;
	// BFME takes the duration as an already-converted integer where the
	// reference header takes a Real.
	virtual void resetCamera(Coord3D *pLoc, Int milliseconds, float easeIn, float easeOut) = 0;	// slot 49, +0xC4
};

extern TerrainLogic *TheTerrainLogic;					// 0x012EF4CC
extern View *TheTacticalView;							// 0x012F1600

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptActions
{
protected:
	void doModCameraLookToward(const AsciiString& waypoint);
	void doModCameraFinalLookToward(const AsciiString& waypoint);
	void doResetCamera(const AsciiString& waypoint, float sec, float easeIn, float easeOut);

	static Int bfmeCompareNames(const BfmeWaypointNameString& self, const AsciiString& other);
};

// The inlined BFME AsciiString three-way compare.  `other` is read first, which
// is the order retail loads the two lengths in.
Int ScriptActions::bfmeCompareNames(const BfmeWaypointNameString& self, const AsciiString& other)
{
	const BfmeAsciiStringData *o = other.m_data;
	Int otherLen = o ? o->m_numChars : 0;
	const char *otherChars = (const char *)(o + 1);
	if (!o) {
		otherChars = "";
	}

	const BfmeAsciiStringData *s = self.m_data;
	Int selfLen = s ? s->m_numChars : 0;
	const char *selfChars = (const char *)(s + 1);
	if (!s) {
		selfChars = "";
	}

	Int shorter = selfLen < otherLen ? selfLen : otherLen;
	Int order = memcmp(selfChars, otherChars, shorter);
	if (order != 0) {
		return order;
	}
	return selfLen - otherLen;
}

void ScriptActions::doModCameraLookToward(const AsciiString& waypoint)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (bfmeCompareNames(way->getName(), waypoint) == 0) {
			Coord3D destination;
			destination.x = way->m_location.x;
			destination.y = way->m_location.y;
			destination.z = way->m_location.z;
			TheTacticalView->cameraModLookToward(&destination);
			break;
		}
	}
}

void ScriptActions::doModCameraFinalLookToward(const AsciiString& waypoint)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (bfmeCompareNames(way->getName(), waypoint) == 0) {
			Coord3D destination;
			destination.x = way->m_location.x;
			destination.y = way->m_location.y;
			destination.z = way->m_location.z;
			TheTacticalView->cameraModFinalLookToward(&destination);
			break;
		}
	}
}

void ScriptActions::doResetCamera(const AsciiString& waypoint, float sec, float easeIn, float easeOut)
{
	for (Waypoint *way = TheTerrainLogic->getFirstWaypoint(); way; way = way->getNext()) {
		if (bfmeCompareNames(way->getName(), waypoint) == 0) {
			Coord3D destination;
			destination.x = way->m_location.x;
			destination.y = way->m_location.y;
			destination.z = way->m_location.z;
			TheTacticalView->resetCamera(&destination, (Int)(sec * 1000.0f), easeIn * 1000.0f, easeOut * 1000.0f);
			break;
		}
	}
}
