// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug
// BFME W3DView::cameraModLookToward, retail 0x0073FF30 / 497 bytes.
// Identity is fixed by the W3DView vtable slot used by ScriptActions and by
// the canonical waypoint-heading algorithm immediately before the final-look
// variant in W3DView.cpp.
// Retail's 0x40 frame shares one scalar slot between WWMath::Sqrt's inlined
// argument and the heading: VC7.1 overlaps them only because the heading is
// declared in its own block, a sibling of the inlined Sqrt scope.

#include "vector2.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

#include "ascii_string.h"

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
};

struct Rva0073FF30Elem
{
	Coord3D position;
	AsciiString unknown0c;
	Int unknown10;
};

class Rva0073FF30Base
{
public:
	virtual void dummy();

	Int unknown04;
	Int unknown08;
	char unknown0c[4];
	char unknown10[8];
	Int unknown18;
	Int unknown1c;
	Int unknown20;
	char unknown24;
	Int unknown28;
};

class Rva0073FF30CameraPath : public Rva0073FF30Base
{
public:
	Rva0073FF30Elem waypoints[259];
	Real cameraAngles[256];
	Real unknownSegments[256];
	Real unknownTotal;
	Real unknownCurrent;
	char padding1c70[0x2070 - 0x1c70];
	Int numWaypoints;
};

extern void __fastcall normAngle(Real &angle);

#define BFME_W3D_SLOT(n) virtual void slot##n() = 0;

class W3DView
{
public:
	BFME_W3D_SLOT(0)  BFME_W3D_SLOT(1)  BFME_W3D_SLOT(2)
	BFME_W3D_SLOT(3)  BFME_W3D_SLOT(4)  BFME_W3D_SLOT(5)
	BFME_W3D_SLOT(6)  BFME_W3D_SLOT(7)  BFME_W3D_SLOT(8)
	BFME_W3D_SLOT(9)  BFME_W3D_SLOT(10) BFME_W3D_SLOT(11)
	BFME_W3D_SLOT(12) BFME_W3D_SLOT(13) BFME_W3D_SLOT(14)
	BFME_W3D_SLOT(15) BFME_W3D_SLOT(16) BFME_W3D_SLOT(17)
	BFME_W3D_SLOT(18) BFME_W3D_SLOT(19) BFME_W3D_SLOT(20)
	BFME_W3D_SLOT(21) BFME_W3D_SLOT(22) BFME_W3D_SLOT(23)
	BFME_W3D_SLOT(24) BFME_W3D_SLOT(25) BFME_W3D_SLOT(26)
	virtual void slot27(Bool enabled) = 0;
	BFME_W3D_SLOT(28) BFME_W3D_SLOT(29)
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31) BFME_W3D_SLOT(32)
	BFME_W3D_SLOT(33) BFME_W3D_SLOT(34) BFME_W3D_SLOT(35)
	virtual void cameraModLookToward(Coord3D *pLoc);

private:
	void moveAlongWaypointPath(Int frames);

	char padding0004[0x138 - 4];
	Int m_field138;
	char padding013c[0x1dc - 0x13c];
	Bool doingRotateCamera;
	char padding1dd[0x280 - 0x1dd];
	Rva0073FF30CameraPath cameraPath;
	char padding22f4[0x2354 - 0x22f4];
	Int cameraMovementMode;
};

#undef BFME_W3D_SLOT

void W3DView::cameraModLookToward(Coord3D *pLoc)
{
	if (doingRotateCamera) {
		return;
	}
	if (cameraMovementMode == 1) {
		Int i;
		for (i = 2; i <= cameraPath.numWaypoints; ++i) {
			Coord3D start, middle, end;
			start = cameraPath.waypoints[i - 1].position;
			start.x += cameraPath.waypoints[i].position.x;
			start.y += cameraPath.waypoints[i].position.y;
			start.x /= 2;
			start.y /= 2;
			middle = cameraPath.waypoints[i].position;
			end = cameraPath.waypoints[i].position;
			end.x += cameraPath.waypoints[i + 1].position.x;
			end.y += cameraPath.waypoints[i + 1].position.y;
			end.x /= 2;
			end.y /= 2;

			Coord3D result = start;
			result.x += 0.5f * (end.x - start.x);
			result.y += 0.5f * (end.y - start.y);
			result.x += 0.25f * (middle.x - end.x + middle.x - start.x);
			result.y += 0.25f * (middle.y - end.y + middle.y - start.y);
			result.z = 0;

			Vector2 direction(pLoc->x - result.x, pLoc->y - result.y);
			const Real directionLength = direction.Length();
			if (directionLength < 0.1f) {
				continue;
			}
			{
				// Own block: lets the heading reuse the Sqrt argument's slot.
				Real angle = WWMath::Acos(direction.X / directionLength);
				if (direction.Y < 0.0f) {
					angle = -angle;
				}
				angle -= 1.5707963705062866f;
				normAngle(angle);
				cameraPath.cameraAngles[i] = angle;
			}
		}
		if (cameraPath.unknown04 == 1) {
			moveAlongWaypointPath(1);
			cameraMovementMode = 1;
			m_field138 = false;
			slot27(false);
		}
	}
}
