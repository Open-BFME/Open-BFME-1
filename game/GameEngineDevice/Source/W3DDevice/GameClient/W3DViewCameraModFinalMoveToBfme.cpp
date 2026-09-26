// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DView::cameraModFinalMoveTo, retail 0x0073C1B0 (228 bytes).
//
// The public identity is established by the named ScriptActions caller for
// CAMERA_MOD_FINAL_LOOK_TOWARD's final move and by the shipped W3DView
// declaration.  The primary W3DView constructor at 0x00745B10 installs
// vftable 0x011217A0; slot 38 (+0x98) follows its thunk to this body.
//
// The path member is not an invented byte overlay.  The matched
// Rva00740440CameraPathAngles.cpp view of the helper at 0x00740440 proves
// the Rva00740AE0Base-derived subobject and its 20-byte path records.  When
// embedded at W3DView +0x280, its inherited vptr puts m_waypoints at +0x2ac
// and m_numWaypoints at +0x22f0, exactly as used by this body.  The BFME
// camera dispatcher and matched camera methods independently prove the mode
// word at +0x2354 and rotate flag at +0x1dc.

typedef float Real;
typedef int Int;
typedef bool Bool;

// The upstream AsciiString occupies one pointer-sized word in each camera
// path record.  Its lifetime is owned by the real camera-path object; this
// method only reads/writes the proven Coord3D prefix.
#include "ascii_string.h"

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D *a)
	{
		x = a->x;
		y = a->y;
		z = a->z;
	}

	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}
};

class Rva00740AE0Base
{
public:
	virtual void dummy();

	Int m_04;
	Int m_08;
	char m_0c[4];
	char m_sub[8];
	Int m_18;
	Int m_1c;
	Int m_20;
	char m_24;
	Int m_28;
};

struct Rva00740AE0Elem
{
	Coord3D position;
	AsciiString name;
	Int m_10;
};

class Rva00740440CameraPath : public Rva00740AE0Base
{
public:
	Rva00740AE0Elem m_waypoints[255];
	Rva00740AE0Elem m_extraWaypoints[4];
	Real m_cameraAngles[256];
	Real m_waySegmentLengths[256];
	Real m_totalDistance;
	Real m_currentSegmentDistance;
	char m_padding1c70[0x2070 - 0x1c70];
	Int m_numWaypoints;
};

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
	BFME_W3D_SLOT(27) BFME_W3D_SLOT(28) BFME_W3D_SLOT(29)
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31) BFME_W3D_SLOT(32)
	BFME_W3D_SLOT(33) BFME_W3D_SLOT(34) BFME_W3D_SLOT(35)
	BFME_W3D_SLOT(36) BFME_W3D_SLOT(37)
	virtual void cameraModFinalMoveTo(Coord3D *pLoc);

private:
	char m_padding0004[0x1dc - 4];
	Bool m_doingRotateCamera;
	char m_padding1dd[0x280 - 0x1dd];
	Rva00740440CameraPath m_cameraPath;
	char m_padding22f4[0x2354 - 0x22f4];
	Int m_cameraMovementMode;
};

#undef BFME_W3D_SLOT

// ?cameraModFinalMoveTo@W3DView@@UAEXPAUCoord3D@@@Z
void W3DView::cameraModFinalMoveTo(Coord3D *pLoc)
{
	if (m_doingRotateCamera) {
		return;
	}
	if (m_cameraMovementMode == 1) {
		Int i;
		Coord3D delta, start;
		start = m_cameraPath.m_waypoints[m_cameraPath.m_numWaypoints].position;
		delta = *pLoc;
		delta.x -= start.x;
		delta.y -= start.y;
		delta.z -= start.z;
		for (i = 2; i <= m_cameraPath.m_numWaypoints; i++) {
			Coord3D start;
			start.set(&m_cameraPath.m_waypoints[i].position);
			start.add(&delta);
			m_cameraPath.m_waypoints[i].position = start;
		}
	}
}
