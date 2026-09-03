// ?rotateCameraTowardPosition@W3DView@@UAEXPBUCoord3D@@HMM_N@Z
// partial score=0.92 date=2026-09-03
// cl: /DNDEBUG /MD
// BFME W3DView::rotateCameraTowardPosition, retail 0x0073FA90.

#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

class WWMath
{
public:
	static Real Acos(Real value);

	static __forceinline Real Sqrt(Real value)
	{
		__asm {
			fld [value]
			fsqrt
		}
	}
};

class Vector2
{
public:
	Vector2() {}
	Vector2(Real x, Real y) { X = x; Y = y; }
	Real Length() const;
	Real Length2() const;
	Real X;
	Real Y;
};

__forceinline Real Vector2::Length() const
{
	return (Real)WWMath::Sqrt(Length2());
}

__forceinline Real Vector2::Length2() const
{
	return X * X + Y * Y;
}

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class ParabolicEase
{
public:
	void setEaseTimes(Real easeIn, Real easeOut);

private:
	Real m_in;
	Real m_out;
};

class W3DView
{
public:
	virtual void rotateCameraTowardPosition(const Coord3D *pLoc, Int milliseconds,
		Real easeIn, Real easeOut, Bool reverseRotation);
	const Coord3D *getPosition() const { return &m_pos; }

private:
	char m_padding004[0x0C - 0x04];
	Coord3D m_pos;
	char m_padding018[0x28 - 0x18];
	Real m_angle;
	char m_padding02C[0x1AC - 0x2C];
	Int m_rcNumFrames;
	Int m_rcCurFrame;
	Int m_rcStartTimeMultiplier;
	Int m_rcEndTimeMultiplier;
	Int m_rcNumHoldFrames;
	ParabolicEase m_rcEase;
	Bool m_rcTrackObject;
	char m_padding1C9[0x1CC - 0x1C9];
	union
	{
		unsigned int m_rcTargetObjectID;
		Real m_rcStartAngle;
	};
	union
	{
		Real m_rcEndAngle;
		Coord3D m_rcTargetObjectPos;
	};
	char m_padding1DC[0x23C4 - 0x1DC];
	Int m_timeMultiplier;
};

extern Int TheW3DFrameLengthInMsec;
extern Real g_bfmePiOverTwo;
extern Real g_bfmeTwoPi;
	 extern void normAngle(Real &angle);

void W3DView::rotateCameraTowardPosition(const Coord3D *pLoc, Int milliseconds,
	Real easeIn, Real easeOut, Bool reverseRotation)
{
	m_rcNumHoldFrames = 0;
	m_rcTrackObject = false;

	if (milliseconds < 1) {
		milliseconds = 1;
	}
	m_rcNumFrames = milliseconds / TheW3DFrameLengthInMsec;
	if (m_rcNumFrames < 1) {
		m_rcNumFrames = 1;
	}

	Vector2 dir(m_pos.x, m_pos.y);
	dir.X = pLoc->x - dir.X;
	dir.Y = pLoc->y - dir.Y;
	const Real dirLength = dir.Length();
	if (dirLength < 0.1f) {
		return;
	}

	Real angle = WWMath::Acos(dir.X / dirLength);
	if (dir.Y < 0.0f) {
		angle = -angle;
	}
	angle -= g_bfmePiOverTwo;
	normAngle(angle);

	if (reverseRotation) {
		if (m_angle < angle) {
			angle -= g_bfmeTwoPi;
		} else {
			angle += g_bfmeTwoPi;
		}
	}

	m_rcCurFrame = 0;
	m_rcStartAngle = m_angle;
	m_rcEndAngle = angle;
	m_rcStartTimeMultiplier = m_timeMultiplier;
	m_rcEndTimeMultiplier = m_timeMultiplier;
	m_rcEase.setEaseTimes(easeIn / milliseconds, easeOut / milliseconds);
}
