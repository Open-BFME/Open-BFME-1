// ?cameraModFinalLookToward@W3DView@@UAEXPAUCoord3D@@@Z
// partial score=0.97 date=2026-09-08
// BFME W3DView::cameraModFinalLookToward, retail 0x007401A0.

#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

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

struct Rva00740AE0Elem
{
	Coord3D position;
	AsciiString name;
	Int unknown10;
};

class Rva00740AE0Base
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

class Rva00740440CameraPath : public Rva00740AE0Base
{
public:
	Rva00740AE0Elem waypoints[255];
	Rva00740AE0Elem extraWaypoints[4];
	Real cameraAngles[256];
	Real waySegmentLengths[256];
	Real totalDistance;
	Real currentSegmentDistance;
	char padding1c70[0x2070 - 0x1c70];
	Int numWaypoints;
};

class WWMath
{
public:
	static __forceinline Real Acos(Real value)
	{
		return (Real)acos(value);
	}

	static __forceinline Real Sqrt(Real value)
	{
		Real result;
		__asm {
			fld [value]
			fsqrt
			fstp [result]
		}
		return result;
	}
};

class Vector2
{
public:
	union {
		Real X;
		Real U;
	};
	union {
		Real Y;
		Real V;
	};

	__forceinline Vector2(void) {}
	__forceinline Vector2(Real x, Real y) : X(x), Y(y) {}

	__forceinline Real Length(void) const
	{
		return WWMath::Sqrt(Length2());
	}

	__forceinline Real Length2(void) const
	{
		return X * X + Y * Y;
	}
};

struct Direction2
{
	Real x;
	Real y;
};

extern Real g_bfmeScaleBK;
extern Real g_bfmeDefaultEG;
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
	BFME_W3D_SLOT(27) BFME_W3D_SLOT(28) BFME_W3D_SLOT(29)
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31) BFME_W3D_SLOT(32)
	BFME_W3D_SLOT(33) BFME_W3D_SLOT(34) BFME_W3D_SLOT(35)
	BFME_W3D_SLOT(36) BFME_W3D_SLOT(37)
	virtual void cameraModFinalLookToward(Coord3D *pLoc);

private:
	char padding0004[0x1dc - 4];
	Bool doingRotateCamera;
	char padding1dd[0x280 - 0x1dd];
	Rva00740440CameraPath cameraPath;
	char padding22f4[0x2354 - 0x22f4];
	Int cameraMovementMode;
};

#undef BFME_W3D_SLOT

void W3DView::cameraModFinalLookToward(Coord3D *pLoc)
{
	if (doingRotateCamera) {
		return;
	}
	if (cameraMovementMode == 1) {
		Int minimum = cameraPath.numWaypoints - 1;
		if (minimum <= 2) {
			minimum = 2;
		}
		for (Int i = minimum; i <= cameraPath.numWaypoints; ++i) {
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

			Real directionX = pLoc->x - result.x;
			Real directionY = pLoc->y - result.y;
			Real angle = directionX * directionX + directionY * directionY;
			Real directionLength;
			__asm {
				fld [angle]
				fsqrt
				fstp [directionLength]
			}
			if (directionLength < 0.1f) {
				continue;
			}
			angle = WWMath::Acos(directionX / directionLength);
			if (directionY < 0.0f) {
				angle = -angle;
			}
			angle -= g_bfmeDefaultEG;
			normAngle(angle);
			if (i == cameraPath.numWaypoints) {
				cameraPath.cameraAngles[i] = angle;
			} else {
				Real angleDelta = angle - cameraPath.cameraAngles[i];
				normAngle(angleDelta);
				angle = cameraPath.cameraAngles[i] + angleDelta / 2.0f;
				normAngle(angle);
				cameraPath.cameraAngles[i] = angle;
			}
		}
	}
}
