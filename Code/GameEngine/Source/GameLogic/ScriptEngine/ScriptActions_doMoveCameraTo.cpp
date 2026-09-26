// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: ScriptActions::doMoveCameraTo, retail 0x002F24F0, 186 bytes.
//
// Zero Hour walks the waypoint list; BFME looks the name up twice instead --
// TerrainLogic slot 31 by value (as ScriptActions_doSetupCamera.cpp does) and
// View's own marker lookup at 0x0045C9E0, reached through ILT 0x00036A43 with
// ECX = TheTacticalView, unadjusted -- and prefers the marker's +0x08 Coord3D over the
// waypoint's +0x0C location. View slot 24 (+0x60) takes the marker pointer
// where Zero Hour passes the stutter time.
//
// Scope matters: `destination` lives in the block entered after both lookups.
// At function scope VC7.1 treats the call-returned pointers as possible
// aliases of the address-taken local and interleaves each 12-byte copy
// (load, store, load, store); scoped after the calls it loads all three
// words first, as retail does.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

	unsigned char m_beforeLocation[0x0c];
	Coord3D m_location;
};

// Layout shared with Code/GameEngine/Source/GameClient/CameraMarkerListFind.cpp;
// the Coord3D at +0x08 is what this body copies.
struct Rva0045C9E0CameraMarker
{
	unsigned char m_pad00[0x08];
	Coord3D m_coord08;
};

class TerrainLogic
{
public:
	virtual void _tl0() = 0; virtual void _tl1() = 0;
	virtual void _tl2() = 0; virtual void _tl3() = 0;
	virtual void _tl4() = 0; virtual void _tl5() = 0;
	virtual void _tl6() = 0; virtual void _tl7() = 0;
	virtual void _tl8() = 0; virtual void _tl9() = 0;
	virtual void _tl10() = 0; virtual void _tl11() = 0;
	virtual void _tl12() = 0; virtual void _tl13() = 0;
	virtual void _tl14() = 0; virtual void _tl15() = 0;
	virtual void _tl16() = 0; virtual void _tl17() = 0;
	virtual void _tl18() = 0; virtual void _tl19() = 0;
	virtual void _tl20() = 0; virtual void _tl21() = 0;
	virtual void _tl22() = 0; virtual void _tl23() = 0;
	virtual void _tl24() = 0; virtual void _tl25() = 0;
	virtual void _tl26() = 0; virtual void _tl27() = 0;
	virtual void _tl28() = 0; virtual void _tl29() = 0;
	virtual void _tl30() = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0;
};

class View
{
public:
	virtual void _v0() = 0; virtual void _v1() = 0;
	virtual void _v2() = 0; virtual void _v3() = 0;
	virtual void _v4() = 0; virtual void _v5() = 0;
	virtual void _v6() = 0; virtual void _v7() = 0;
	virtual void _v8() = 0; virtual void _v9() = 0;
	virtual void _v10() = 0; virtual void _v11() = 0;
	virtual void _v12() = 0; virtual void _v13() = 0;
	virtual void _v14() = 0; virtual void _v15() = 0;
	virtual void _v16() = 0; virtual void _v17() = 0;
	virtual void _v18() = 0; virtual void _v19() = 0;
	virtual void _v20() = 0; virtual void _v21() = 0;
	virtual void _v22() = 0; virtual void _v23() = 0;
	virtual void moveCameraTo(const Coord3D *position,
		const Rva0045C9E0CameraMarker *marker,
		Int milliseconds, Bool orient, Real easeIn, Real easeOut) = 0;

	Rva0045C9E0CameraMarker *findMarker0045C9E0(const AsciiString &name) const;
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doMoveCameraTo(const AsciiString &waypoint, Real sec,
		Real cameraStutterSec, Real easeIn, Real easeOut);
};

void ScriptActions::doMoveCameraTo(const AsciiString &waypoint, Real sec,
	Real cameraStutterSec, Real easeIn, Real easeOut)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	Rva0045C9E0CameraMarker *marker = TheTacticalView->findMarker0045C9E0(waypoint);
	if (way != 0 || marker != 0)
	{
		Coord3D destination;
		if (way != 0)
			destination = *way->getLocation();
		if (marker != 0)
			destination = marker->m_coord08;

		TheTacticalView->moveCameraTo(&destination, marker, sec * 1000,
			true, easeIn * 1000.0f, easeOut * 1000.0f);
	}
}
