// cl: /DNDEBUG /MD /EHsc
// readable body of ?doModCameraFinalLookToward@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doModCameraLookToward@ScriptActions@@IAEXABVAsciiString@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// readable body of ?doResetCamera@ScriptActions@@IAEXABVAsciiString@@MMM@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Every ScriptActions action that drives the tactical view:
//
//   0x002EDB50  doCameraTetherNamed         lock the camera onto a named unit
//   0x002EDE20  doModCameraMoveToSelection  centre on the selected drawables
//   0x002F5900  doC3CameraShake             shake at a waypoint
//   0x002F8C60  doModCameraLookToward       arm 32, CAMERA_MOD_LOOK_TOWARD
//   0x002F8D70  doModCameraFinalLookToward  arm 31, its slot-0x94 twin
//   0x002F8E80  doResetCamera               arm 19, RESET_CAMERA
//
// The three waypoint-name bodies walk the waypoint list and compare names
// inline, which is why they were kept out of ScriptActions.cpp; the other three
// reach the same singleton by other routes. All six end in one virtual call on
// TheTacticalView, so the vtable below is what they really share.

#include <string.h>

#pragma intrinsic(memcmp)

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;
typedef unsigned int DrawableID;

class Drawable;
class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D(void) {}

	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
};

// BFME's string block: the character count is a word at data+4 and the
// characters begin at data+8.
struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;							///< retail data+0x04
	unsigned short m_unreconstructed_06;
};

// One data pointer. Only the name compare reads through it; the other bodies
// take it by reference and hand it straight on, which is why two of the four
// files that held these bodies declared the pointer as a bare char *.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const BfmeAsciiStringData *m_data;
};

// Waypoint::getName returns a retail AsciiString by value. Naming the returned
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

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

// The by-value string temporary TerrainLogic slot 31 takes.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	BfmeWaypointNameString getName(void) const;			// ILT 0x0001026C
	Waypoint *getNext(void) const { return m_next; }

	unsigned char m_unmodelled_000[0x0C];
	Coord3D m_location;									// +0x0C
	unsigned char m_unmodelled_018[0x04];
	Waypoint *m_next;									// +0x1C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void _tl_0() = 0; virtual void _tl_1() = 0;
	virtual void _tl_2() = 0; virtual void _tl_3() = 0;
	virtual void _tl_4() = 0; virtual void _tl_5() = 0;
	virtual void _tl_6() = 0; virtual void _tl_7() = 0;
	virtual void _tl_8() = 0; virtual void _tl_9() = 0;
	virtual void _tl_10() = 0; virtual void _tl_11() = 0;
	virtual void _tl_12() = 0; virtual void _tl_13() = 0;
	virtual void _tl_14() = 0; virtual void _tl_15() = 0;
	virtual void _tl_16() = 0; virtual void _tl_17() = 0;
	virtual void _tl_18() = 0; virtual void _tl_19() = 0;
	virtual void _tl_20() = 0; virtual void _tl_21() = 0;
	virtual void _tl_22() = 0; virtual void _tl_23() = 0;
	virtual void _tl_24() = 0; virtual void _tl_25() = 0;
	virtual void _tl_26() = 0; virtual void _tl_27() = 0;
	virtual void _tl_28() = 0; virtual void _tl_29() = 0;
	virtual Waypoint *getFirstWaypoint(void) = 0;		// slot 30, +0x78
	virtual Waypoint *getWaypointByName(BfmeAsciiStringArg) = 0;	// slot 31, +0x7C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameClient/Include/GameClient/Drawable.h
class Drawable
{
public:
	Drawable *getNextDrawable(void) const
	{
		return *(Drawable **)((char *)this + 0x104);
	}

	Bool isSelected(void) const
	{
		return *(const unsigned char *)((const char *)this + 0x3ac) != 0;
	}

	const Coord3D *getPosition(void) const;
};

class ClientRoot4120
{
public:
	virtual void _gc_0(void) = 0;
	virtual void _gc_1(void) = 0;
	virtual void _gc_2(void) = 0;
	virtual void _gc_3(void) = 0;
	virtual void _gc_4(void) = 0;
	virtual void _gc_5(void) = 0;
	virtual void _gc_6(void) = 0;
	virtual void _gc_7(void) = 0;
	virtual void _gc_8(void) = 0;
	virtual void _gc_9(void) = 0;
	virtual void _gc_10(void) = 0;
	virtual void _gc_11(void) = 0;
	virtual Drawable *firstDrawable(void) = 0;
};

class BfmeDrawableWithID
{
public:
	DrawableID bfmeGetID(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual BfmeDrawableWithID *getDrawable(void) const = 0;

private:
	char m_pad[0x70];

public:
	ObjectID m_id;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _se_0(void) = 0; virtual void _se_1(void) = 0;
	virtual void _se_2(void) = 0; virtual void _se_3(void) = 0;
	virtual void _se_4(void) = 0; virtual void _se_5(void) = 0;
	virtual void _se_6(void) = 0; virtual void _se_7(void) = 0;
	virtual void _se_8(void) = 0; virtual void _se_9(void) = 0;
	virtual void _se_10(void) = 0; virtual void _se_11(void) = 0;
	virtual void _se_12(void) = 0; virtual void _se_13(void) = 0;
	virtual void _se_14(void) = 0; virtual void _se_15(void) = 0;
	virtual void _se_16(void) = 0; virtual void _se_17(void) = 0;
	virtual void _se_18(void) = 0; virtual void _se_19(void) = 0;
	virtual void _se_20(void) = 0; virtual void _se_21(void) = 0;
	virtual void _se_22(void) = 0; virtual void _se_23(void) = 0;
	virtual void _se_24(void) = 0; virtual void _se_25(void) = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

// One vtable, four prefixes of it. The four files these bodies came from
// modelled it as TacticalView (42 slots), BfmeTacticalView (103), and View
// (39 and 50), each stopping after the last entry its own body called. The
// pinned spelling of the singleton is ?TheTacticalView@@3PAVView@@A, so View is
// the name, and every slot any of them reached is stated here at its offset.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
#define BFME_VIEW_SLOT(name) virtual void name(void) = 0;
	BFME_VIEW_SLOT(slot000) BFME_VIEW_SLOT(slot004) BFME_VIEW_SLOT(slot008) BFME_VIEW_SLOT(slot00C)
	BFME_VIEW_SLOT(slot010) BFME_VIEW_SLOT(slot014) BFME_VIEW_SLOT(slot018) BFME_VIEW_SLOT(slot01C)
	BFME_VIEW_SLOT(slot020) BFME_VIEW_SLOT(slot024) BFME_VIEW_SLOT(slot028) BFME_VIEW_SLOT(slot02C)
	BFME_VIEW_SLOT(slot030) BFME_VIEW_SLOT(slot034) BFME_VIEW_SLOT(slot038) BFME_VIEW_SLOT(slot03C)
	BFME_VIEW_SLOT(slot040) BFME_VIEW_SLOT(slot044) BFME_VIEW_SLOT(slot048) BFME_VIEW_SLOT(slot04C)
	BFME_VIEW_SLOT(slot050) BFME_VIEW_SLOT(slot054) BFME_VIEW_SLOT(slot058) BFME_VIEW_SLOT(slot05C)
	BFME_VIEW_SLOT(slot060) BFME_VIEW_SLOT(slot064) BFME_VIEW_SLOT(slot068) BFME_VIEW_SLOT(slot06C)
	BFME_VIEW_SLOT(slot070) BFME_VIEW_SLOT(slot074) BFME_VIEW_SLOT(slot078) BFME_VIEW_SLOT(slot07C)
	BFME_VIEW_SLOT(slot080) BFME_VIEW_SLOT(slot084) BFME_VIEW_SLOT(slot088) BFME_VIEW_SLOT(slot08C)
	virtual void cameraModLookToward(Coord3D *pLoc) = 0;                          // slot 36, +0x090
	virtual void cameraModFinalLookToward(Coord3D *pLoc) = 0;                     // slot 37, +0x094
	virtual void cameraModFinalMoveTo(Coord3D *location) = 0;                     // slot 38, +0x098
	BFME_VIEW_SLOT(slot09C) BFME_VIEW_SLOT(slot0A0)
	virtual void Add_Camera_Shake(const Coord3D *, Real, Real, Real) = 0;         // slot 41, +0x0A4
	BFME_VIEW_SLOT(slot0A8) BFME_VIEW_SLOT(slot0AC) BFME_VIEW_SLOT(slot0B0) BFME_VIEW_SLOT(slot0B4)
	BFME_VIEW_SLOT(slot0B8) BFME_VIEW_SLOT(slot0BC) BFME_VIEW_SLOT(slot0C0)
	virtual void resetCamera(Coord3D *pLoc, Int milliseconds, float easeIn, float easeOut) = 0;// slot 49, +0x0C4
	BFME_VIEW_SLOT(slot0C8) BFME_VIEW_SLOT(slot0CC) BFME_VIEW_SLOT(slot0D0) BFME_VIEW_SLOT(slot0D4)
	BFME_VIEW_SLOT(slot0D8) BFME_VIEW_SLOT(slot0DC) BFME_VIEW_SLOT(slot0E0) BFME_VIEW_SLOT(slot0E4)
	BFME_VIEW_SLOT(slot0E8) BFME_VIEW_SLOT(slot0EC) BFME_VIEW_SLOT(slot0F0) BFME_VIEW_SLOT(slot0F4)
	BFME_VIEW_SLOT(slot0F8) BFME_VIEW_SLOT(slot0FC) BFME_VIEW_SLOT(slot100) BFME_VIEW_SLOT(slot104)
	BFME_VIEW_SLOT(slot108) BFME_VIEW_SLOT(slot10C) BFME_VIEW_SLOT(slot110) BFME_VIEW_SLOT(slot114)
	BFME_VIEW_SLOT(slot118) BFME_VIEW_SLOT(slot11C) BFME_VIEW_SLOT(slot120) BFME_VIEW_SLOT(slot124)
	BFME_VIEW_SLOT(slot128) BFME_VIEW_SLOT(slot12C) BFME_VIEW_SLOT(slot130) BFME_VIEW_SLOT(slot134)
	BFME_VIEW_SLOT(slot138) BFME_VIEW_SLOT(slot13C) BFME_VIEW_SLOT(slot140) BFME_VIEW_SLOT(slot144)
	BFME_VIEW_SLOT(slot148) BFME_VIEW_SLOT(slot14C) BFME_VIEW_SLOT(slot150) BFME_VIEW_SLOT(slot154)
	BFME_VIEW_SLOT(slot158) BFME_VIEW_SLOT(slot15C) BFME_VIEW_SLOT(slot160) BFME_VIEW_SLOT(slot164)
	BFME_VIEW_SLOT(slot168) BFME_VIEW_SLOT(slot16C) BFME_VIEW_SLOT(slot170) BFME_VIEW_SLOT(slot174)
	BFME_VIEW_SLOT(slot178) BFME_VIEW_SLOT(slot17C)
	virtual void setCameraLock(ObjectID id) = 0;                                  // slot 96, +0x180
	virtual void snapToCameraLock(void) = 0;                                      // slot 97, +0x184
	virtual void twoArguments(int first, int second) = 0;                         // slot 98, +0x188
	virtual void oneArgument(float value) = 0;                                    // slot 99, +0x18C
	BFME_VIEW_SLOT(slot190) BFME_VIEW_SLOT(slot194)
	virtual void setCameraLockDrawableID(DrawableID id) = 0;                      // slot 102, +0x198
#undef BFME_VIEW_SLOT
};

extern TerrainLogic *TheTerrainLogic;					// 0x012EF4CC
extern View *TheTacticalView;							// 0x012F1600
extern ClientRoot4120 *TheGameClient;
extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doCameraTetherNamed(const AsciiString &unit, Bool snapToUnit, float play);
	void doModCameraMoveToSelection(void);
	void doC3CameraShake(const AsciiString &, Real, Real, Real);
	void doModCameraLookToward(const AsciiString& waypoint);
	void doModCameraFinalLookToward(const AsciiString& waypoint);
	void doResetCamera(const AsciiString& waypoint, float sec, float easeIn, float easeOut);

	static Int bfmeCompareNames(const BfmeWaypointNameString& self, const AsciiString& other);
};

// The inlined BFME AsciiString three-way compare.  `other` is read first, which
// is the order retail loads the two lengths in.  Retail has no such function --
// it is inlined into all three waypoint-name bodies, which byte-match whether or
// not this is declared __forceinline -- so there is no address to put in a row.
// ?bfmeCompareNames@ScriptActions@@KAHABVBfmeWaypointNameString@@ABVAsciiString@@@Z absent-from-retail
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

// ?doCameraTetherNamed@ScriptActions@@IAEXABVAsciiString@@_NM@Z
void ScriptActions::doCameraTetherNamed(const AsciiString &unit, Bool snapToUnit, float play)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (theObj)
	{
		TheTacticalView->setCameraLock(theObj->m_id);
		TheTacticalView->setCameraLockDrawableID(theObj->getDrawable()->bfmeGetID());
		if (snapToUnit)
			TheTacticalView->snapToCameraLock();
		TheTacticalView->oneArgument(play);
		TheTacticalView->twoArguments(0, 0);
	}
}

// ?doModCameraMoveToSelection@ScriptActions@@IAEXXZ
void ScriptActions::doModCameraMoveToSelection(void)
{
	Int count = 0;
	Coord3D destination;
	destination.x = destination.y = destination.z = 0;

	for (Drawable *draw = TheGameClient->firstDrawable(); draw; draw = draw->getNextDrawable())
	{
		if (draw->isSelected())
		{
			Coord3D position = *draw->getPosition();
			destination.x += position.x;
			destination.y += position.y;
			destination.z += position.z;
			count++;
		}
	}

	if (count)
	{
		destination.z /= count;
		destination.x /= count;
		destination.y /= count;
		TheTacticalView->cameraModFinalMoveTo(&destination);
	}
}

// ?doC3CameraShake@ScriptActions@@IAEXABVAsciiString@@MMM@Z
void ScriptActions::doC3CameraShake(
	const AsciiString &waypointName, Real amplitude, Real duration, Real radius)
{
	Waypoint *waypoint = TheTerrainLogic->getWaypointByName(waypointName);
	TheTacticalView->Add_Camera_Shake(
		waypoint->getLocation(), radius, duration, amplitude);
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
