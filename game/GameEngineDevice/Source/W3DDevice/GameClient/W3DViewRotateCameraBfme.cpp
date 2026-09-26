// BFME W3DView::rotateCamera, retail 0x0073BDD0.
// The BFME vtable places this five-argument camera rotation at slot 50.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define TheAnimationMsPerStep (*(Int *)0x012BB1CC)

class BfmeThingBRD
{
public:
	void bfmeDoBRD(void *, void *, void *);

private:
	char m_body[8];
};

struct RotateCameraInfo
{
	Int numFrames;
	Int curFrame;
	Int startTimeMultiplier;
	Int endTimeMultiplier;
	Int numHoldFrames;
	BfmeThingBRD ease;
	Bool trackObject;
	char padding01c9[0x1cc - 0x1c9];
	Real startAngle;
	Real endAngle;
};

class W3DView
{
public:
	virtual void rotateCamera(Real rotations, Int milliseconds, Bool flag,
		Real easeIn, Real easeOut);

private:
	char m_padding0004[0x28 - 0x04];
	Real m_angle;
	char m_padding002c[0x1ac - 0x2c];
	RotateCameraInfo m_rcInfo;
	char m_padding01d4[0x1dc - 0x1d4];
	Bool m_doingRotateCamera;
	char m_padding01dd[0x23c4 - 0x1dd];
	Int m_timeMultiplier;
	char m_padding23c8[0x2428 - 0x23c8];
	Bool m_field2428;
};

void W3DView::rotateCamera(Real rotations, Int milliseconds, Bool flag,
	Real easeIn, Real easeOut)
{
	Int &duration = milliseconds;
	register W3DView *view = this;
	view->m_rcInfo.numHoldFrames = 0;
	view->m_rcInfo.trackObject = false;
	if (duration < 1)
	{
		duration = 1;
	}
	view->m_rcInfo.numFrames = duration / TheAnimationMsPerStep;
	if (view->m_rcInfo.numFrames < 1)
	{
		view->m_rcInfo.numFrames = 1;
	}
	view->m_rcInfo.endAngle = view->m_angle + (*(Real *)0x01087B10) * rotations;
	view->m_rcInfo.startAngle = view->m_angle;
	view->m_doingRotateCamera = true;
	view->m_rcInfo.curFrame = 0;
	view->m_rcInfo.startTimeMultiplier = view->m_timeMultiplier;
	view->m_rcInfo.endTimeMultiplier = view->m_timeMultiplier;
	typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
	SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
	(view->m_rcInfo.ease.*setEase)(easeIn, easeOut, (Real)duration);
	view->m_field2428 = flag;
}
