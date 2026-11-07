// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// W3DView::setupWaypointPath, retail 0x00740F60 (599 B, ret 0x10): BFME form of Zero Hour
// W3DView::setupWaypointPath
// (GeneralsMD W3DView.cpp); heading loop is out-of-line Rva00740440::rva00740440. Handoff:
// targets/game/reverse/attempt_support/20261107-00740f60-setup-waypoint-path.md
#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

#include "wwmath.h"
#include "vector2.h"
#include "vector3.h"

#include "Lib/Coord3D.h"

struct WaypointRecord
{
	Coord3D position;
	void *name;
	Int flags;
};

// The camera waypoint-path record at W3DView+0x280.
class Rva00740440
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void configure(Int timeMultiplier, Int shutter, Real easeIn, Real easeOut,
		Int arg4, Int arg5);
	void rva00740440(Bool orient, Real angle, Int firstWaypoint);	// 0x00740440
	// Inlined into the caller through the +0x280 receiver (EDI); retail's dead
	// lea of &cameraAngle[numWaypoints+2] is the end pointer.
	void startAngles(Real angle)
	{
		Real *begin = cameraAngle;
		Real *end = begin + numWaypoints + 2;
		begin[1] = angle;
		end[-1] = end[-2];
		begin[0] = begin[1];
	}

	char m_padding0004[0x2c - 0x04];
	WaypointRecord waypoints[259];		// +0x002C
	Real cameraAngle[255];				// +0x1468
	Real waySegLength[257];				// +0x1864
	Real totalDistance;					// +0x1C68
	Real initialGroundHeight;			// +0x1C6C
	Real finalGroundHeight;				// +0x1C70
	char m_padding1C74[0x2070 - 0x1C74];
	Int numWaypoints;					// +0x2070
};

class Rva0045A000
{
public:
	Real sample(Real x, Real y);		// 0x00459B10
	char m_padding0000[0x1c];
	Bool m_ready;
	char m_padding001d[0x70 - 0x1d];
};

struct Rva003FD060TerrainLogic
{
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) = 0;
};
extern Rva003FD060TerrainLogic *TheTerrainLogic;

#define V(N) virtual void slot##N() = 0
class W3DView
{
public:
	V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);
	V(14);V(15);V(16);V(17);V(18);V(19);V(20);V(21);V(22);V(23);V(24);V(25);V(26);
	virtual void slot27(Int value) = 0;
	V(28);V(29);V(30);V(31);V(32);V(33);V(34);V(35);V(36);V(37);V(38);V(39);V(40);
	V(41);V(42);V(43);V(44);V(45);V(46);V(47);V(48);V(49);V(50);V(51);V(52);V(53);
	V(54);V(55);V(56);V(57);V(58);V(59);V(60);V(61);V(62);
	virtual Real getAngle() = 0;		// vtable +0xFC

private:
	void setupWaypointPath(Int shutter, Bool orient, Real easeIn, Real easeOut);

	char m_padding0004[0x1dc - 0x04];
	Bool m_doingRotateCamera;					// +0x1DC
	char m_padding01dd[0x280 - 0x1dd];
	Rva00740440 m_mcwpInfo;						// +0x280
	char m_padding22f4[0x2354 - 0x22f4];
	Int m_doingMoveCameraOnWaypointPath;		// +0x2354
	char m_padding2358[0x23c4 - 0x2358];
	Int m_timeMultiplier;						// +0x23C4
	char m_padding23c8[0x23f8 - 0x23c8];
	Real m_groundLevel;							// +0x23F8
	char m_padding23fc[0x2448 - 0x23fc];
	Rva0045A000 m_heightField;					// +0x2448
};

void W3DView::setupWaypointPath(Int shutter, Bool orient, Real easeIn, Real easeOut)
{
	m_mcwpInfo.configure(m_timeMultiplier, shutter, easeIn, easeOut, 0, 1);
	Int i;
	m_mcwpInfo.totalDistance = 0;
	for (i = 1; i < m_mcwpInfo.numWaypoints; i++) {
		const Coord3D &a = m_mcwpInfo.waypoints[i].position;
		const Coord3D &b = m_mcwpInfo.waypoints[i+1].position;
		Vector2 dir(b.x - a.x, b.y - a.y);
		m_mcwpInfo.waySegLength[i] = dir.Length();
		m_mcwpInfo.totalDistance += m_mcwpInfo.waySegLength[i];
	}
	m_mcwpInfo.waySegLength[0] = 0;
	m_mcwpInfo.waySegLength[m_mcwpInfo.numWaypoints] = m_mcwpInfo.waySegLength[0];
	m_mcwpInfo.waySegLength[m_mcwpInfo.numWaypoints+1] = 0;

	m_mcwpInfo.rva00740440(orient, getAngle(), -1);
	m_mcwpInfo.startAngles(getAngle());
	m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints] = m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints-1];
	m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints+1] = m_mcwpInfo.cameraAngle[m_mcwpInfo.numWaypoints];
	for (i = m_mcwpInfo.numWaypoints-1; i > 1; i--) {
		m_mcwpInfo.cameraAngle[i] = (m_mcwpInfo.cameraAngle[i] + m_mcwpInfo.cameraAngle[i-1]) / 2;
	}

	const Coord3D &last = m_mcwpInfo.waypoints[m_mcwpInfo.numWaypoints].position;
	// 12-byte frame local; VC7.1 drops the dead z store.
	Vector3 finalPos(last.x, last.y, last.z);
	m_mcwpInfo.initialGroundHeight = m_groundLevel;
	m_mcwpInfo.finalGroundHeight = TheTerrainLogic->getGroundHeight(finalPos.X, finalPos.Y);
	if (m_heightField.m_ready)
		m_mcwpInfo.finalGroundHeight = m_heightField.sample(finalPos.X, finalPos.Y);

	m_doingMoveCameraOnWaypointPath = m_mcwpInfo.numWaypoints > 1;
	slot27(0);
	m_doingRotateCamera = false;
}
