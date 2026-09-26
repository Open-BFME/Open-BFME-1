// cl: /DNDEBUG /DWIN32 /MD /Iinputs/reference/shims/stringinline
// Open-BFME: ScriptActions spline-camera action, retail 0x002F2790, 135 bytes.

#include "StringInline.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

enum WaypointPathType
{
	WAYPOINT_PATH_SPLINE = 6
};

// The spline type is read at +0x60 after TerrainLogic slot 34 returns the
// first waypoint carrying the requested path label.
class Waypoint
{
private:
	unsigned char m_unreconstructed_00[0x60];

public:
	WaypointPathType m_pathType;
};

// Retail TerrainLogic vtable 0x0109C428.  Slot 34 is also the null-position
// fallback called by the matched getClosestWaypointOnPath body.
class TerrainLogic
{
public:
#define BFME_TERRAIN_SLOT(index) virtual void slot##index(void) = 0;
	BFME_TERRAIN_SLOT(00) BFME_TERRAIN_SLOT(01)
	BFME_TERRAIN_SLOT(02) BFME_TERRAIN_SLOT(03)
	BFME_TERRAIN_SLOT(04) BFME_TERRAIN_SLOT(05)
	BFME_TERRAIN_SLOT(06) BFME_TERRAIN_SLOT(07)
	BFME_TERRAIN_SLOT(08) BFME_TERRAIN_SLOT(09)
	BFME_TERRAIN_SLOT(10) BFME_TERRAIN_SLOT(11)
	BFME_TERRAIN_SLOT(12) BFME_TERRAIN_SLOT(13)
	BFME_TERRAIN_SLOT(14) BFME_TERRAIN_SLOT(15)
	BFME_TERRAIN_SLOT(16) BFME_TERRAIN_SLOT(17)
	BFME_TERRAIN_SLOT(18) BFME_TERRAIN_SLOT(19)
	BFME_TERRAIN_SLOT(20) BFME_TERRAIN_SLOT(21)
	BFME_TERRAIN_SLOT(22) BFME_TERRAIN_SLOT(23)
	BFME_TERRAIN_SLOT(24) BFME_TERRAIN_SLOT(25)
	BFME_TERRAIN_SLOT(26) BFME_TERRAIN_SLOT(27)
	BFME_TERRAIN_SLOT(28) BFME_TERRAIN_SLOT(29)
	BFME_TERRAIN_SLOT(30) BFME_TERRAIN_SLOT(31)
	BFME_TERRAIN_SLOT(32) BFME_TERRAIN_SLOT(33)
#undef BFME_TERRAIN_SLOT
	virtual Waypoint *getWaypointByPath(AsciiString pathName) = 0; // +0x88
};

// Primary W3DView vtable 0x011217A0.  The body behind slot 25 is 0x00741250;
// the matched switch establishes the seven explicit argument slots below.
class View
{
public:
#define BFME_VIEW_SLOT(index) virtual void slot##index(void) = 0;
	BFME_VIEW_SLOT(00) BFME_VIEW_SLOT(01)
	BFME_VIEW_SLOT(02) BFME_VIEW_SLOT(03)
	BFME_VIEW_SLOT(04) BFME_VIEW_SLOT(05)
	BFME_VIEW_SLOT(06) BFME_VIEW_SLOT(07)
	BFME_VIEW_SLOT(08) BFME_VIEW_SLOT(09)
	BFME_VIEW_SLOT(10) BFME_VIEW_SLOT(11)
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13)
	BFME_VIEW_SLOT(14) BFME_VIEW_SLOT(15)
	BFME_VIEW_SLOT(16) BFME_VIEW_SLOT(17)
	BFME_VIEW_SLOT(18) BFME_VIEW_SLOT(19)
	BFME_VIEW_SLOT(20) BFME_VIEW_SLOT(21)
	BFME_VIEW_SLOT(22) BFME_VIEW_SLOT(23)
	BFME_VIEW_SLOT(24)
#undef BFME_VIEW_SLOT
	virtual void moveCameraAlongSplinePath(Waypoint *path,
		Int durationMilliseconds, Bool orient,
		Real easeInMilliseconds, Real easeOutMilliseconds,
		Real delayStartMilliseconds, Bool moveLocator) = 0; // +0x64
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doMoveCameraAlongSplinePath(const AsciiString &pathName,
		Real duration, Real cameraShutter, Real easeIn, Real easeOut,
		Real delayStart, Bool moveLocator);
};

// ?doMoveCameraAlongSplinePath@ScriptActions@@IAEXABVAsciiString@@MMMMM_N@Z
void ScriptActions::doMoveCameraAlongSplinePath(const AsciiString &pathName,
	Real duration, Real cameraShutter, Real easeIn, Real easeOut,
	Real delayStart, Bool moveLocator)
{
	Waypoint *path = TheTerrainLogic->getWaypointByPath(pathName);
	if (path == 0 || path->m_pathType != WAYPOINT_PATH_SPLINE)
		return;

	// The retail BFME action template retains cameraShutter, but this spline
	// dispatch does not consume it; the slot receives the constant orient flag.
	TheTacticalView->moveCameraAlongSplinePath(path,
		(Int)(duration * 1000.0f), true,
		easeIn * 1000.0f, easeOut * 1000.0f,
		delayStart * 1000.0f, moveLocator);
}
