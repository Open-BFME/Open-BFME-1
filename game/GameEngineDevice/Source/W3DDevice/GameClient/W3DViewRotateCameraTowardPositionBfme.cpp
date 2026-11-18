// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DView::rotateCameraTowardPosition, retail 0x0073FA90 (336 B, ret 0x14).
// ilt_oracle CONFIRMS the class-keyed decoration
// ?rotateCameraTowardPosition@W3DView@@UAEXPBVCoord3D@@HMM_N@Z here (the
// struct-keyed PBUCoord3D spelling is contradicted).
//
// Zero Hour's body with BFME's tail, read off the bytes:
// - WWMath::Sqrt is the library's inline-asm version (fld [val] / fsqrt /
//   fstp [retval]), so the squared length and the root both go through
//   memory, and WWMath::Acos is (float)acos, the _CIacos intrinsic.
// - The reverse-rotation end angle is one conditional expression stored
//   straight into the rotate info (angle is not written back), with 2*PI as a
//   literal.
// - BFME's ParabolicEase::setEaseTimes takes (easeIn, easeOut, duration) and
//   the view raises its rotate-camera flag at +0x1DC (as rotateCamera does).
// - Retail shares the dead pLoc argument slot between the Sqrt result and
//   angle, so angle lives in a block of its own after the length check.

#include <math.h>

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"



#include "wwmath.h"

#include "vector2.h"

// class-gate: allow Coord3D canonical header is struct-keyed; retail ILT proves the class-keyed mangling
class Coord3D
{
public:
	Real x;
	Real y;
	Real z;
};

class ParabolicEase
{
public:
	void setEaseTimes(Real easeIn, Real easeOut, Real totalTime);

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
	Bool m_doingRotateCamera;
	char m_padding1DD[0x23C4 - 0x1DD];
	Int m_timeMultiplier;
};

extern Int TheW3DFrameLengthInMsec;


extern void __fastcall normAngle(Real &angle);	// 0x0073A900

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
	if (dirLength < 0.100000001f) {
		return;
	}

	{
		Real angle = WWMath::Acos(dir.X / dirLength);
		if (dir.Y < 0.0f) {
			angle = -angle;
		}
		angle -= 1.57079637f;
		normAngle(angle);

		m_rcEndAngle = reverseRotation ? (m_angle < angle ? angle - 6.2831855f : angle + 6.2831855f) : angle;
		m_rcStartAngle = m_angle;
		m_rcCurFrame = 0;
		m_doingRotateCamera = true;
		m_rcStartTimeMultiplier = m_timeMultiplier;
		m_rcEndTimeMultiplier = m_timeMultiplier;
		m_rcEase.setEaseTimes(easeIn, easeOut, (Real)milliseconds);
	}
}
