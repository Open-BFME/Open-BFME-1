// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// BFME camera-path angle helper at retail 0x00740440 (347 bytes, ret 0xC).
// Its only caller is 0x00740F60 (via ILT 0x00020266). The body is BFME's form
// of Zero Hour's W3DView::setupWaypointPath angle loop: it walks the path's
// waypoints and stores each segment's heading (acos of the normalised x step,
// mirrored for a negative y step, less pi/2, then normAngle). With orient off
// it fills the angles with the given one. The ILT oracle contradicts the old
// descriptive name, so the method keeps the address.

#include <math.h>
#include "vector2.h"

typedef float Real;
typedef bool Bool;

class Rva00740AE0Base
{
public:
	virtual void dummy();

	int m_04;
	int m_08;
	char m_0c[4];
	char m_sub[8];
	int m_18;
	int m_1c;
	int m_20;
	char m_24;
	int m_28;
};

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva00740AE0Elem
{
	Coord3D position;
	AsciiString name;
	int m_10;
};

extern void __fastcall normAngle(Real &angle);

class Rva00740440 : public Rva00740AE0Base
{
public:
	void rva00740440(Bool orient, Real angle, int firstWaypoint);

private:
	Rva00740AE0Elem m_waypoints[255];
	Rva00740AE0Elem m_extraWaypoints[4];
	Real m_cameraAngles[256];
	Real m_waySegmentLengths[256];
	Real m_totalDistance;
	Real m_currentSegmentDistance;
	char m_padding1c70[0x2070 - 0x1c70];
	int m_numWaypoints;
};

void Rva00740440::rva00740440(Bool orient, Real angle, int firstWaypoint)
{
	Real *cameraAngle = m_cameraAngles;
	int i;
	if (orient)
	{
		++cameraAngle;
		for (i = 2; i < m_numWaypoints + 2; ++i)
		{
			Vector2 direction;
			Real *current = &m_waypoints[i].position.x;
			Real *next = &m_waypoints[i + firstWaypoint].position.x;
			direction.X = *current - *next;
			direction.Y = current[1] - next[1];
			Real pathAngle = direction.Length2();
			pathAngle = WWMath::Sqrt(pathAngle);
			pathAngle = direction.X / pathAngle;
			if (pathAngle < -1.0f)
				pathAngle = -1.0f;
			if (pathAngle > 1.0f)
				pathAngle = 1.0f;
			if (direction.Y < 0.0f)
				pathAngle = -WWMath::Acos(pathAngle);
			else
				pathAngle = WWMath::Acos(pathAngle);
			pathAngle -= 1.57079637050628662109375f; // retail float32 pi/2
			normAngle(pathAngle);
			*cameraAngle++ = pathAngle;
		}
		m_cameraAngles[1] = angle;
		m_cameraAngles[0] = angle;
	}
	else
	{
		Real *end = cameraAngle + m_numWaypoints;
		for (Real *p = cameraAngle; p != end; ++p)
			*p = angle;
	}
}
