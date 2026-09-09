// ?rotateCameraOneFrame@W3DView@@AAEXXZ
// partial score=0.55 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// BFME W3DView::rotateCameraOneFrame, retail 0x00743860 (676 bytes).
//
// The matched W3DView::updateCameraMovements body at 0x00744530 calls this
// helper on its own this under the flag at +0x1DC.  The retail boundary is
// the complete 0x00743860..0x00743B03 body, including its final ret; the
// generated row is the only current claim for that range.  This TU keeps the
// BFME camera layout local, as the shared W3DView header has a different
// state ordering.

#include <math.h>
#include "vector2.h"

typedef float Real;
typedef int Int;
typedef bool Bool;
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7FFFFFFF
};

// The shipped GlobalData.h spells this as TheGlobalData through the writable
// singleton.  The disable flag is proven at GlobalData+0xA74 by the matched
// W3D camera one-frame siblings.
class GlobalData
{
public:
	char m_unreconstructed_000[0xA74];
	Bool m_disableCameraMovement;
};

extern GlobalData *TheWritableGlobalData;
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Coord2D
{
	Real x;
	Real y;
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// Upstream ParabolicEase is an eight-byte value object.  Its matched
// operator() body is the callee used by the adjacent one-frame bodies.
class ParabolicEase
{
public:
	Real operator()(Real param) const;

private:
	Real m_in;
	Real m_out;
};

// W3DView.cpp's normalizer is the matched cdecl/fastcall helper at 0x0073A900.
extern void __fastcall normAngle(Real &angle);

// BaseType's BFME build uses this image constant for PI/2.
#define BFME_PI_OVER_TWO (*(const Real *)0x01097114)

// The camera methods use the CRT double floor followed by the active-FPU
// rounding helper in this BFME image; retain that established local shape.
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern double g_bfmeSubB3;

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

struct RotateCameraInfo
{
	Int numFrames;
	Int curFrame;
	Int startTimeMultiplier;
	Int endTimeMultiplier;
	Int numHoldFrames;
	ParabolicEase ease;
	Bool trackObject;
	char padding01c9[0x1CC - 0x1C9];
	struct Target
	{
		ObjectID targetObjectID;
		struct TargetPosition
		{
			Real x;
			Real y;
			TargetPosition &operator=(const Coord3D &other)
			{
				x = other.x;
				y = other.y;
				return *this;
			}
		} targetObjectPos;
		Real targetObjectPosZ;
	};
	struct Angle
	{
		Real startAngle;
		Real endAngle;
	};
	union
	{
		Target target;
		Angle angle;
	};
};

class W3DView
{
private:
	void rotateCameraOneFrame(void);

	char padding0000[0x0C];
	Coord3D m_pos;
	char padding0018[0x28 - 0x18];
	Real m_angle;
	char padding002C[0x138 - 0x2C];
	Real m_unreconstructed0138;
	char padding013C[0x1AC - 0x13C];
	RotateCameraInfo m_rcInfo;
	Bool m_doingRotateCamera;
	char padding01DD[0x23C0 - 0x1DD];
	Bool m_freezeTimeForCameraMovement;
	Int m_timeMultiplier;
	char padding23C8[0x2428 - 0x23C8];
	Bool m_field2428;
};

// ?rotateCameraOneFrame@W3DView@@AAEXXZ
void W3DView::rotateCameraOneFrame(void)
{
	m_rcInfo.curFrame++;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (m_rcInfo.curFrame >= m_rcInfo.numFrames + m_rcInfo.numHoldFrames) {
			m_doingRotateCamera = false;
			m_freezeTimeForCameraMovement = false;
		}
		return;
	}

	if (m_rcInfo.trackObject)
	{
		if (m_rcInfo.curFrame <= m_rcInfo.numFrames + m_rcInfo.numHoldFrames)
		{
			const Object *obj = TheGameLogic->findObjectByID(m_rcInfo.target.targetObjectID);
			if (obj)
			{
				m_rcInfo.target.targetObjectPos = *obj->getPosition();
			}
			const Vector2 dir(m_rcInfo.target.targetObjectPos.x - m_pos.x,
				m_rcInfo.target.targetObjectPos.y - m_pos.y);
			const Real dirLength = dir.Length();
			if (dirLength >= 0.1f)
			{
				Real angle = WWMath::Acos(dir.X / dirLength);
				if (dir.Y < 0.0f) {
					angle = -angle;
				}
				angle -= BFME_PI_OVER_TWO;
				normAngle(angle);

				if (m_rcInfo.curFrame <= m_rcInfo.numFrames)
				{
					Real factor = m_rcInfo.ease(((Real)m_rcInfo.curFrame) / m_rcInfo.numFrames);
					Real angleDiff = angle - m_angle;
					normAngle(angleDiff);
					angleDiff *= factor;
					m_angle += angleDiff;
					normAngle(m_angle);
					m_timeMultiplier = m_rcInfo.startTimeMultiplier + REAL_TO_INT_FLOOR(
						0.5 + (m_rcInfo.endTimeMultiplier - m_rcInfo.startTimeMultiplier) * factor);
				}
				else
				{
					m_angle = angle;
				}
			}
		}
	}
	else if (m_rcInfo.curFrame <= m_rcInfo.numFrames)
	{
		Real factor = m_rcInfo.ease(((Real)m_rcInfo.curFrame) / m_rcInfo.numFrames);
		m_angle = WWMath::Lerp(m_rcInfo.angle.startAngle, m_rcInfo.angle.endAngle, factor);
		normAngle(m_angle);
		m_timeMultiplier = m_rcInfo.startTimeMultiplier + REAL_TO_INT_FLOOR(
			0.5 + (m_rcInfo.endTimeMultiplier - m_rcInfo.startTimeMultiplier) * factor);
	}

	if (m_rcInfo.curFrame >= m_rcInfo.numFrames + m_rcInfo.numHoldFrames) {
		m_doingRotateCamera = false;
		m_freezeTimeForCameraMovement = false;
		if (!m_rcInfo.trackObject)
		{
			m_angle = m_rcInfo.angle.endAngle;
		}
	}
}

#undef REAL_TO_INT_FLOOR
#undef BFME_PI_OVER_TWO
