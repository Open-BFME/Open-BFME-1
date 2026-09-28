// ?moveAlongWaypointPath@W3DView@@AAEXH@Z
// partial score=0.78 date=2026-09-28
// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DView::moveAlongWaypointPath, retail 0x0073CB10.
//
// The owner is proved by the named updateCameraMovements caller, the adjacent
// W3DView camera bodies, and the primary vftable installed by 0x00745B10.
// The path records and their 20-byte stride are the witnessed
// Rva00740AE0-derived layout used by the matched BFME camera-path methods.
//
// 2026-09-28 rewrite (333 of 1540 bytes differ, was 1142): ZH division by
// totalTime (MSVC turns the pair into one reciprocal), the first ease result kept
// as a local because BFME lerps the ground level by it, WWMath::Lerp for the
// angle / time multiplier / ground level, a file-static normAngle so EDX stays
// live across the calls, inline updateMinMax for the early-exit clamp, and the
// GlobalData view declared as a struct to match the pinned mangled name.
// Remaining: before the factor<0.5 branch retail hoists this+curSeg*20 into ECX
// (both arms start with identical lea pairs); ours builds it in EAX per arm, so
// the arms and tail differ by an EAX/ECX swap and 6 bytes.

typedef float Real;
typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor(double);

extern const Real g_bfmeK1253;
extern const Real g_rva001B5860TwoPi;

struct Rva006C9270GlobalData
{
	char padding0000[0xA74];
	Bool m_disableCameraMovement;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class ParabolicEase
{
public:
	Real operator()(Real value) const;

private:
	Real m_in;
	Real m_out;
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

struct Coord2D
{
	Real x;
	Real y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

inline Real minf(Real a, Real b) { return b > a ? a : b; }
inline Real maxf(Real a, Real b) { return b < a ? a : b; }

struct Rva00740AE0Elem
{
	Coord3D position;
	char name[4];
	Int unknown10;
};

class Rva00740AE0Base
{
public:
	virtual void dummy();

	Int totalTimeMilliseconds;
	Int elapsedTimeMilliseconds;
	char unknown0c[4];
	ParabolicEase ease;
	Real currentDistance;
	Real segmentStartDistance;
	Int curSegment;
	Int unknown24;
	Int rollingAverageFrames;
};

class Rva00740440CameraPath : public Rva00740AE0Base
{
public:
	Rva00740AE0Elem waypoints[259];
	Real cameraAngles[255];
	Real waySegmentLengths[0x101];
	Real totalDistance;
	Real groundStart;
	Real groundEnd;
	Int timeMultiplier[0xFF];
	Int numWaypoints;
};

class Rva0073B8C0
{
public:
	void reset();
};

class Rva006DF550
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void rva006DF110(Coord3D *out, Real *angle);
};

inline void updateMinMax(Real *minimum, Real value, Real *maximum)
{
	if (value < *minimum) {
		*minimum = value;
		return;
	}
	if (value > *maximum) {
		*maximum = value;
	}
}


#define PI 3.14159265359f

namespace WWMath
{
	inline Real Lerp(Real a, Real b, Real t) { return a + (b - a) * t; }
}

// Normalizes angle to +- PI (the W3DView.cpp file-static helper; retail calls it
// with the angle in ECX and keeps EDX live across it).
static void normAngle(Real &angle)
{
	if (angle < -10*PI) {
		angle = 0;
	}
	if (angle > 10*PI) {
		angle = 0;
	}
	while (angle < -PI) {
		angle += 2*PI;
	}
	while (angle > PI) {
		angle -= 2*PI;
	}
}

__forceinline long fast_float2long_round(Real value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

__forceinline Real bfme_crt_floor(Real value)
{
	return (Real)floor((double)value);
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(bfme_crt_floor((Real)(x))))

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
	virtual void setInt23BC(Int value);

private:
	void moveAlongWaypointPath(Int milliseconds);
	void setPosition(const Coord3D *value) { position = *value; }

	char padding0004[0x0C - 4];
	Coord3D position;
	char padding0018[0x28 - 0x18];
	Real angle;
	char padding002C[0xA0 - 0x2C];
	Real scale;
	char padding00A4[0x280 - 0xA4];
	Rva00740440CameraPath cameraPath;
	char padding22F4[0x2354 - 0x22F4];
	Int cameraMovementMode;
	char padding2358[0x23C0 - 0x2358];
	Bool freezeTimeForCameraMovement;
	char padding23C1[0x23C4 - 0x23C1];
	Int timeMultiplierValue;
	char padding23C8[0x23D8 - 0x23C8];
	Coord3D cameraOffset;
	char padding23E4[0x23F8 - 0x23E4];
	Real groundLevel;
	Region2D cameraConstraint;
	Bool cameraConstraintValid;
	char padding240D[0x24B8 - 0x240D];
	Rva006DF550 cameraLimits;
};

#undef BFME_W3D_SLOT

void W3DView::moveAlongWaypointPath(Int milliseconds)
{
	cameraPath.elapsedTimeMilliseconds += milliseconds;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (cameraPath.elapsedTimeMilliseconds > cameraPath.totalTimeMilliseconds) {
			((Rva0073B8C0 *)this)->reset();
			freezeTimeForCameraMovement = false;
		}
		return;
	}
	if (cameraPath.elapsedTimeMilliseconds > cameraPath.totalTimeMilliseconds) {
		cameraMovementMode = 0;
		setInt23BC(0);
		freezeTimeForCameraMovement = false;
		angle = cameraPath.cameraAngles[cameraPath.numWaypoints];
		groundLevel = cameraPath.groundEnd;
		cameraLimits.rva006DF110(&cameraOffset, 0);
		cameraOffset.x *= scale;
		cameraOffset.y *= scale;
		Coord3D pos = cameraPath.waypoints[cameraPath.numWaypoints].position;
		pos.z = 0;
		setPosition(&pos);
		updateMinMax(&cameraConstraint.lo.x, pos.x, &cameraConstraint.hi.x);
		updateMinMax(&cameraConstraint.lo.y, pos.y, &cameraConstraint.hi.y);
		return;
	}

	const Real totalTime = cameraPath.totalTimeMilliseconds;
	const Real easedTime = cameraPath.ease(cameraPath.elapsedTimeMilliseconds / totalTime);
	const Real deltaTime = easedTime -
		cameraPath.ease((cameraPath.elapsedTimeMilliseconds - milliseconds) / totalTime);
	cameraPath.currentDistance += deltaTime * cameraPath.totalDistance;
	while (cameraPath.currentDistance - cameraPath.segmentStartDistance >=
		cameraPath.waySegmentLengths[cameraPath.curSegment]) {
		setInt23BC(cameraPath.waypoints[cameraPath.curSegment].unknown10);
		cameraPath.segmentStartDistance += cameraPath.waySegmentLengths[cameraPath.curSegment];
		cameraPath.curSegment++;
		if (cameraPath.curSegment >= cameraPath.numWaypoints) {
			cameraPath.totalTimeMilliseconds = 0;
			return;
		}
	}
	Real avgFactor = 1.0f / cameraPath.rollingAverageFrames;
	Real factor = (cameraPath.currentDistance - cameraPath.segmentStartDistance) /
		cameraPath.waySegmentLengths[cameraPath.curSegment];
	if (cameraPath.curSegment == cameraPath.numWaypoints - 1) {
		avgFactor = avgFactor + (1.0f - avgFactor) * factor;
	}
	Real angle1 = cameraPath.cameraAngles[cameraPath.curSegment];
	Real angle2 = cameraPath.cameraAngles[cameraPath.curSegment + 1];
	if (angle2 - angle1 > PI) angle1 += 2*PI;
	if (angle2 - angle1 < -PI) angle1 -= 2*PI;
	Real newAngle = WWMath::Lerp(angle1, angle2, factor);
	normAngle(newAngle);
	Real deltaAngle = newAngle - angle;
	normAngle(deltaAngle);
	angle += avgFactor * deltaAngle;
	normAngle(angle);

	Real timeMultiplier = WWMath::Lerp(cameraPath.timeMultiplier[cameraPath.curSegment],
		cameraPath.timeMultiplier[cameraPath.curSegment + 1], factor);
	timeMultiplierValue = REAL_TO_INT_FLOOR(timeMultiplier + 0.5f);
	groundLevel = WWMath::Lerp(cameraPath.groundStart, cameraPath.groundEnd, easedTime);
	cameraLimits.rva006DF110(&cameraOffset, 0);
	cameraOffset.x *= scale;
	cameraOffset.y *= scale;

	Coord3D start, mid, end;
	if (factor < 0.5f) {
		start = cameraPath.waypoints[cameraPath.curSegment - 1].position;
		start.x += cameraPath.waypoints[cameraPath.curSegment].position.x;
		start.y += cameraPath.waypoints[cameraPath.curSegment].position.y;
		start.x /= 2;
		start.y /= 2;
		mid = cameraPath.waypoints[cameraPath.curSegment].position;
		end = cameraPath.waypoints[cameraPath.curSegment].position;
		end.x += cameraPath.waypoints[cameraPath.curSegment + 1].position.x;
		end.y += cameraPath.waypoints[cameraPath.curSegment + 1].position.y;
		end.x /= 2;
		end.y /= 2;
		factor += 0.5f;
	} else {
		start = cameraPath.waypoints[cameraPath.curSegment].position;
		start.x += cameraPath.waypoints[cameraPath.curSegment + 1].position.x;
		start.y += cameraPath.waypoints[cameraPath.curSegment + 1].position.y;
		start.x /= 2;
		start.y /= 2;
		mid = cameraPath.waypoints[cameraPath.curSegment + 1].position;
		end = cameraPath.waypoints[cameraPath.curSegment + 1].position;
		end.x += cameraPath.waypoints[cameraPath.curSegment + 2].position.x;
		end.y += cameraPath.waypoints[cameraPath.curSegment + 2].position.y;
		end.x /= 2;
		end.y /= 2;
		factor -= 0.5f;
	}

	Coord3D result = start;
	result.x += factor * (end.x - start.x);
	result.y += factor * (end.y - start.y);
	result.x += (mid.x - end.x + mid.x - start.x) * (1 - factor) * factor;
	result.y += (mid.y - end.y + mid.y - start.y) * (1 - factor) * factor;
	result.z = 0;
	setPosition(&result);
	updateMinMax(&cameraConstraint.lo.x, result.x, &cameraConstraint.hi.x);
	updateMinMax(&cameraConstraint.lo.y, result.y, &cameraConstraint.hi.y);
}

#undef REAL_TO_INT_FLOOR
