// cl: /DNDEBUG /MD /EHs-c-
// BFME W3DView::cameraModFinalTimeMultiplier, retail 0x0073C2D0 (261 bytes).
//
// The public identity is proved by the named ScriptActions caller for
// CAMERA_MOD_SET_FINAL_SPEED_MULTIPLIER and the shipped W3DView declaration.
// BFME's constructor at 0x00745B10 installs the primary W3DView vftable
// 0x011217A0; the neighboring matched W3DView methods and camera dispatcher
// use the same object.  The four contiguous BFME per-frame state blocks and
// the rotate state below come from those matched methods, not from an empty
// overlay or an address-only cast.

typedef float Real;
typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern double g_bfmeSubB3;

// The retail path calls CRT double floor, then uses BaseType.h's two-instruction
// x87 rounding helper. A C++ integer cast uses truncation semantics instead;
// this tiny original helper preserves the active FPU rounding mode.
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

// The matched camera one-frame bodies establish this two-Real easing object.
struct ParabolicEase
{
	Real in;
	Real out;
};

// BFME camera-update state at +0x1E0.  The state body at 0x0073C970 proves
// the frame/start/end/ease/active offsets; this method additionally proves the
// final time-multiplier word at +0x1F8.
struct CameraUpdateState
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Int unmodelled08;              // +0x08
	Real start;                    // +0x0C
	Real end;                      // +0x10
	Int unmodelled14;              // +0x14
	Int endTimeMultiplier;         // +0x18
	ParabolicEase ease;            // +0x1C
	Bool active;                   // +0x24
};

// BFME zoom state at +0x208.  0x0073C7C0 proves the block and active flag;
// this method proves the intervening final-time word at +0x21C.
struct ZoomCameraState
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Real startZoom;                // +0x08
	Real endZoom;                  // +0x0C
	Int unmodelled10;              // +0x10
	Int endTimeMultiplier;         // +0x14
	ParabolicEase ease;            // +0x18
	Bool active;                   // +0x20
};

// BFME pitch state at +0x22C.  0x0073FCF0 and 0x0073C890 prove the frame,
// pitch and easing offsets; this method proves its final-time word at +0x248.
struct PitchCameraState
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Real angle;                    // +0x08
	Real finalPitch;               // +0x0C
	Real startPitch;               // +0x10
	Real endPitch;                 // +0x14
	Int unmodelled18;              // +0x18
	Int endTimeMultiplier;         // +0x1C
	ParabolicEase ease;            // +0x20
	Bool active;                   // +0x28
};

// BFME alternate camera-update state at +0x258.  0x0073CA40 proves the
// frame/start/end/ease/active offsets; this method proves +0x270.
struct AlternateCameraState
{
	Int numFrames;                 // +0x00
	Int curFrame;                  // +0x04
	Int unmodelled08;              // +0x08
	Real start;                    // +0x0C
	Real end;                      // +0x10
	Int unmodelled14;              // +0x14
	Int endTimeMultiplier;         // +0x18
	ParabolicEase ease;            // +0x1C
	Bool active;                   // +0x24
};

// The already-matched rotate setter establishes this complete state at
// +0x1AC, including endTimeMultiplier at +0x1B8 and active at +0x1DC.
struct RotateCameraState
{
	Int numFrames;
	Int curFrame;
	Int startTimeMultiplier;
	Int endTimeMultiplier;
	Int numHoldFrames;
	ParabolicEase ease;
	Bool trackObject;
	unsigned char unmodelled1D[3];
	Real startAngle;
	Real endAngle;
};

#define BFME_W3D_SLOT(n) virtual void slot##n() = 0;

class W3DView
{
public:
	// Constructor 0x00745B10 installs vftable 0x011217A0.  Its slot 32
	// thunk chain (vftable +0x80) lands at this body's 0x0073C2D0 entry;
	// the earlier slots are retained as neutral ABI positions only.
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
	BFME_W3D_SLOT(30) BFME_W3D_SLOT(31)
	virtual void cameraModFinalTimeMultiplier(Int finalMultiplier);

private:
	char padding0004[0x1AC - 4];
	RotateCameraState rotateCamera; // +0x1AC, active at +0x1DC
	char padding1D4[0x1DC - 0x1D4];
	Bool doingRotateCamera;         // +0x1DC
	char padding1DD[0x1E0 - 0x1DD];
	CameraUpdateState cameraUpdate; // +0x1E0, active at +0x204
	ZoomCameraState zoomCamera;     // +0x208, active at +0x228
	PitchCameraState pitchCamera;   // +0x22C, active at +0x254
	AlternateCameraState alternateCamera; // +0x258, active at +0x27C
	// The four state blocks end at the compiler's +0x280 boundary.  The
	// matched retail path array begins at +0x1AE4; this explicit real gap
	// keeps that member at its proven offset rather than relying on an empty
	// overlay.
	char padding280[0x1AE4 - 0x280];
	Real waySegmentLength[0x101];   // +0x1AE4
	Real totalDistance;             // +0x1EE8
	char unmodelled1EEC[8];
	Int timeMultiplier[0xFF];        // +0x1EF4, indexed from [i+1]
	Int numWaypoints;                // +0x22F0
	char padding22F4[0x2354 - 0x22F4];
	Int cameraMovementMode;          // +0x2354; mode 1 is waypoint movement
	char padding2358[0x23C4 - 0x2358];
	Int timeMultiplierDefault;       // +0x23C4
};

#undef BFME_W3D_SLOT

// ?cameraModFinalTimeMultiplier@W3DView@@UAEXH@Z
void W3DView::cameraModFinalTimeMultiplier(Int finalMultiplier)
{
	if (zoomCamera.active)
		zoomCamera.endTimeMultiplier = finalMultiplier;
	if (pitchCamera.active)
		pitchCamera.endTimeMultiplier = finalMultiplier;
	if (cameraUpdate.active)
		cameraUpdate.endTimeMultiplier = finalMultiplier;
	if (alternateCamera.active)
		alternateCamera.endTimeMultiplier = finalMultiplier;
	if (doingRotateCamera)
		rotateCamera.endTimeMultiplier = finalMultiplier;
	if (cameraMovementMode == 1)
	{
		Int i;
		Real curDistance = 0;
		for (i = 0; i < numWaypoints; i++)
		{
			curDistance += waySegmentLength[i];
			Real factor2 = curDistance / totalDistance;
			Real factor1 = g_bfmeSubB3 - factor2;
			timeMultiplier[i + 1] = REAL_TO_INT_FLOOR(
				0.5 + timeMultiplier[i + 1] * factor1 + finalMultiplier * factor2);
		}
	}
	else
	{
		timeMultiplierDefault = finalMultiplier;
	}
}

#undef REAL_TO_INT_FLOOR
