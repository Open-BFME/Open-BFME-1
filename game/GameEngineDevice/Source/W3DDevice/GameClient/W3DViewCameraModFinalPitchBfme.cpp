// BFME W3DView::cameraModFinalPitch, retail 0x0073C440 (171 bytes).
// The W3DView vtable at 0x011217A0 maps slot 33 to this body. Its call through
// vtable slot +0xF0 matches pitchCamera, while cameraModFinalZoom calls +0xE8.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define TheAnimationMsPerStep (*(Int *)0x012BB1CC)

struct ParabolicEase
{
	Real in;
	Real out;
};

struct RotateCameraState
{
	Int numFrames;
	Int curFrame;
	Int startTimeMultiplier;
	Int endTimeMultiplier;
	Int numHoldFrames;
	ParabolicEase ease;
	Bool trackObject;
	unsigned char padding[3];
	Real startAngle;
	Real endAngle;
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
	BFME_W3D_SLOT(36) BFME_W3D_SLOT(37) BFME_W3D_SLOT(38)
	BFME_W3D_SLOT(39) BFME_W3D_SLOT(40) BFME_W3D_SLOT(41)
	BFME_W3D_SLOT(42) BFME_W3D_SLOT(43) BFME_W3D_SLOT(44)
	BFME_W3D_SLOT(45) BFME_W3D_SLOT(46) BFME_W3D_SLOT(47)
	BFME_W3D_SLOT(48) BFME_W3D_SLOT(49) BFME_W3D_SLOT(50)
	BFME_W3D_SLOT(51) BFME_W3D_SLOT(52) BFME_W3D_SLOT(53)
	BFME_W3D_SLOT(54) BFME_W3D_SLOT(55) BFME_W3D_SLOT(56)
	BFME_W3D_SLOT(57) BFME_W3D_SLOT(58) BFME_W3D_SLOT(59)
	virtual void pitchCamera(Real finalPitch, Int milliseconds,
		Real easeIn, Real easeOut);
	virtual void cameraModFinalPitch(Real finalPitch, Real easeIn, Real easeOut);

private:
	char padding0004[0x1ac - 4];
	RotateCameraState rotateCamera;
	char padding01d4[0x1dc - 0x1d4];
	Bool doingRotateCamera;
	char padding01dd[0x284 - 0x1dd];
	Int totalTimeMilliseconds;
	Int elapsedTimeMilliseconds;
	char padding028c[0x2354 - 0x28c];
	Int cameraMovementMode;
};

#undef BFME_W3D_SLOT

void W3DView::cameraModFinalPitch(Real finalPitch, Real easeIn, Real easeOut)
{
	if (doingRotateCamera)
	{
		Real time = (rotateCamera.numFrames + rotateCamera.numHoldFrames -
			rotateCamera.curFrame) * TheAnimationMsPerStep;
		pitchCamera(finalPitch, time, time * easeIn, time * easeOut);
	}
	if (cameraMovementMode == 1)
	{
		Real time = totalTimeMilliseconds - elapsedTimeMilliseconds;
		pitchCamera(finalPitch, time, time * easeIn, time * easeOut);
	}
}
