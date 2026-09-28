// ?rotateCameraOneFrame@W3DView@@AAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// BFME W3DView::rotateCameraOneFrame, retail 0x00743860 (676 bytes).
//
// Identity: the matched W3DView::updateCameraMovements body at 0x00744530
// calls this helper on its own this under m_doingRotateCamera (+0x1DC); the
// ZH twin (GeneralsMD W3DView.cpp rotateCameraOneFrame) matches its shape.
// BFME additions over ZH: the disabled-camera path also clears the byte at
// +0x2428; the tracking path copies only x/y of the target position and
// interpolates targetObjectPos.z into the Real at +0x138; the tracking
// time-multiplier floor goes through the float overload (?floor@@YAMM@Z)
// while the plain path uses the CRT double floor.
//
// Shape notes: curFrame/numFrames are cached locals (retail uses the cached
// values after findObjectByID); after the first normAngle the frame count is
// re-read into a fresh local and numFrames is reassigned, which is what puts
// the re-reads on retail's stack slots. normAngle is W3DView.cpp's file-static
// helper (matched there at 0x0073A900); its body must be visible here for
// retail's register use across the calls (EDX kept live), so the same static
// definition is repeated in this TU. The TU keeps a local, address-derived
// W3DView layout like the other BFME one-frame camera bodies.

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

// W3DView.cpp's file-static normalizer (retail 0x0073A900, matched there).
// Retail keeps EDX live across its calls, which the compiler only does when
// the body is visible in the caller's TU, so the same definition sits here.
#define PI 3.14159265359f
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

// Two floors: the tracking branch hands a Real to the out-of-line float
// overload (?floor@@YAMM@Z), the plain branch the CRT double floor.
extern "C" __declspec(dllimport) double __cdecl floor(double);
Real floor(Real);

__forceinline long fast_float2long_round(Real value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

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
		Coord3D targetObjectPos;
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
	Bool m_unreconstructed2428;
};

// ?rotateCameraOneFrame@W3DView@@AAEXXZ
void W3DView::rotateCameraOneFrame(void)
{
	Int curFrame = ++m_rcInfo.curFrame;
	if (TheWritableGlobalData->m_disableCameraMovement) {
		if (curFrame >= m_rcInfo.numFrames + m_rcInfo.numHoldFrames) {
			m_doingRotateCamera = false;
			m_freezeTimeForCameraMovement = false;
		}
		m_unreconstructed2428 = false;
		return;
	}

	Int numFrames = m_rcInfo.numFrames;
	if (m_rcInfo.trackObject)
	{
		if (curFrame <= numFrames + m_rcInfo.numHoldFrames)
		{
			const Object *obj = TheGameLogic->findObjectByID(m_rcInfo.target.targetObjectID);
			if (obj)
			{
				m_rcInfo.target.targetObjectPos.x = obj->getPosition()->x;
				m_rcInfo.target.targetObjectPos.y = obj->getPosition()->y;
			}
			m_unreconstructed0138 = ((Real)curFrame) / numFrames * m_rcInfo.target.targetObjectPos.z;
			const Vector2 dir(m_rcInfo.target.targetObjectPos.x - m_pos.x,
				m_rcInfo.target.targetObjectPos.y - m_pos.y);
			const Real dirLength = dir.Length();
			if (dirLength >= 0.1f)
			{
				Real angle = WWMath::Acos(dir.X / dirLength);
				if (dir.Y < 0.0f) {
					angle = -angle;
				}
				angle -= 1.5707964f;
				normAngle(angle);

				Int frame = m_rcInfo.curFrame;
				numFrames = m_rcInfo.numFrames;
				if (frame <= numFrames)
				{
					Real factor = m_rcInfo.ease(((Real)frame) / numFrames);
					Real angleDiff = angle - m_angle;
					normAngle(angleDiff);
					angleDiff *= factor;
					m_angle += angleDiff;
					normAngle(m_angle);
					m_timeMultiplier = m_rcInfo.startTimeMultiplier + fast_float2long_round(floor(
						(Real)(0.5 + (m_rcInfo.endTimeMultiplier - m_rcInfo.startTimeMultiplier) * factor)));
				}
				else
				{
					m_angle = angle;
				}
			}
		}
	}
	else if (curFrame <= numFrames)
	{
		Real factor = m_rcInfo.ease(((Real)curFrame) / numFrames);
		m_angle = WWMath::Lerp(m_rcInfo.angle.startAngle, m_rcInfo.angle.endAngle, factor);
		normAngle(m_angle);
		m_timeMultiplier = m_rcInfo.startTimeMultiplier + fast_float2long_round(
			floor(0.5 + (m_rcInfo.endTimeMultiplier - m_rcInfo.startTimeMultiplier) * factor));
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
