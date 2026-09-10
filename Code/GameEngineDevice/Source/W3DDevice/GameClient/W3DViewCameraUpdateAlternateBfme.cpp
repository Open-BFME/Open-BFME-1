// BFME W3DView::cameraUpdateAlternate, retail 0x0073FE80.
//
// Vtable slot +0xF4 and the call to 0x0073CA40 identify this as the setter for
// the alternate camera-update state at +0x258. The state blends the view value
// at +0x30 and clears its active flag at +0x27C.

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

class W3DView
{
public:
	virtual void cameraUpdateAlternate(Real finalValue, Int milliseconds, Real easeIn, Real easeOut);

private:
	void cameraUpdateAlternateOneFrame();

	char m_padding0000[0x2C];
	Real m_cameraValue;
	char m_padding0034[0x258 - 0x34];
	Int m_cuaNumFrames;
	Int m_cuaCurFrame;
	char m_padding0260[0x264 - 0x260];
	Real m_cuaStart;
	Real m_cuaEnd;
	char m_padding026C[0x274 - 0x26C];
	BfmeThingBRD m_cuaEase;
	Bool m_doingCameraUpdateAlternate;
};

void W3DView::cameraUpdateAlternate(Real finalValue, Int milliseconds, Real easeIn, Real easeOut)
{
	Int &duration = milliseconds;
	register W3DView *view = this;
	if (duration < 1) {
		duration = 1;
	}
	view->m_cuaNumFrames = duration / TheAnimationMsPerStep;
	if (view->m_cuaNumFrames < 1) {
		view->m_cuaNumFrames = 1;
	}
	view->m_cuaStart = view->m_cameraValue;
	view->m_cuaEnd = finalValue;
	view->m_cuaCurFrame = 0;
	view->m_doingCameraUpdateAlternate = true;
	typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
	SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
	(view->m_cuaEase.*setEase)(easeIn, easeOut, (Real)duration);
	if (duration == 1) {
		view->cameraUpdateAlternateOneFrame();
	}
}
