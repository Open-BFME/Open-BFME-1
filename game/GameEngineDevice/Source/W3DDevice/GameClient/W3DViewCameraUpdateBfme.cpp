// BFME W3DView::cameraUpdate, retail 0x0073FDD0.
// The constructor at 0x00745B10 places this state at +0x1E0 and its active
// flag at +0x204. The duration-one path calls cameraUpdateOneFrame through
// the thunk at 0x000035E4, which identifies this setter separately from the
// zoom setter at 0x0073FC40.

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
	virtual void cameraUpdate(Real finalValue, Int milliseconds, Real easeIn, Real easeOut);

private:
	void cameraUpdateOneFrame();

	char m_padding0000[0x6C];
	Real m_cameraValue;
	char m_padding0074[0x1E0 - 0x74];
	Int m_cuNumFrames;
	Int m_cuCurFrame;
	char m_padding01E8[0x1EC - 0x1E8];
	Real m_cuStart;
	Real m_cuEnd;
	char m_padding01F4[0x1FC - 0x1F4];
	BfmeThingBRD m_cuEase;
	Bool m_doingCameraUpdate;
};

void W3DView::cameraUpdate(Real finalValue, Int milliseconds, Real easeIn, Real easeOut)
{
	Int &duration = milliseconds;
	register W3DView *view = this;
	if (duration < 1) {
		duration = 1;
	}
	view->m_cuNumFrames = duration / TheAnimationMsPerStep;
	if (view->m_cuNumFrames < 1) {
		view->m_cuNumFrames = 1;
	}
	view->m_cuStart = view->m_cameraValue;
	view->m_cuEnd = finalValue;
	view->m_cuCurFrame = 0;
	view->m_doingCameraUpdate = true;
	typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
	SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
	(view->m_cuEase.*setEase)(easeIn, easeOut, (Real)duration);
	if (duration == 1) {
		view->cameraUpdateOneFrame();
	}
}
