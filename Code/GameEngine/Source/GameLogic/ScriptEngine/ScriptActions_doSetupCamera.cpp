// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: ScriptActions::doSetupCamera, retail 0x002F25E0, 207 bytes.
//
// The retail body passes both waypoint names by value through BFME's TerrainLogic
// slot 31.  StringInline.h preserves the in-place AsciiString temporary that the
// MSVC 7.1 body uses at each virtual call.

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

class Waypoint
{
public:
	unsigned char m_beforeLocation[0x0c];
	Coord3D m_location;
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
	virtual void moveCameraTo(const Coord3D *position, Int milliseconds,
		Int stutterMilliseconds, Bool snap, Real easeIn, Real easeOut) = 0;
	virtual void _v25() = 0; virtual void _v26() = 0;
	virtual void _v27() = 0; virtual void _v28() = 0;
	virtual void _v29() = 0;
	virtual void cameraModFinalZoom(Real zoom, Real easeIn, Real easeOut) = 0;
	virtual void _v31() = 0; virtual void _v32() = 0;
	virtual void cameraModFinalPitch(Real pitch, Real easeIn, Real easeOut) = 0;
	virtual void _v34() = 0; virtual void _v35() = 0;
	virtual void cameraModLookToward(Coord3D *position) = 0;
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doSetupCamera(const AsciiString &waypoint, Real zoom, Real pitch,
		const AsciiString &lookAtWaypoint);
};

void ScriptActions::doSetupCamera(const AsciiString &waypoint, Real zoom,
	Real pitch, const AsciiString &lookAtWaypoint)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
	if (way == 0)
		return;

	Coord3D position;
	position.x = way->m_location.x;
	position.y = way->m_location.y;
	position.z = way->m_location.z;
	Waypoint *lookAt = TheTerrainLogic->getWaypointByName(lookAtWaypoint);
	if (lookAt == 0)
		return;

	Coord3D destination;
	destination.x = lookAt->m_location.x;
	destination.y = lookAt->m_location.y;
	destination.z = lookAt->m_location.z;
	TheTacticalView->moveCameraTo(&position, 0, 0, true, 0.0f, 0.0f);
	TheTacticalView->cameraModLookToward(&destination);
	TheTacticalView->cameraModFinalPitch(pitch, 0.0f, 0.0f);
	TheTacticalView->cameraModFinalZoom(zoom, 0.0f, 0.0f);
}
