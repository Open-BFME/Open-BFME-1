// BFME W3DView::zoomCamera, retail 0x0073FDD0.
// BFME places this camera state at different offsets from the Zero Hour twin.
// The setter at 0x0002A1B2 receives three float stack words, but the existing
// address-derived helper declaration uses void pointers. The member-pointer
// cast preserves that verified call target while keeping the source readable.

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

class W3DView;

class Gen0073C970Owner
{
	friend class W3DView;

	void updateOneFrame();
};

class W3DView
{
public:
	virtual void zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut);

private:
	char m_padding0000[0x6C];
	Real m_zoom;
	char m_padding0074[0x1E0 - 0x74];
	Int m_zcNumFrames;
	Int m_zcCurFrame;
	Int m_zcAngle;
	Real m_zcStartZoom;
	Real m_zcEndZoom;
	char m_padding01F4[0x1FC - 0x1F4];
	BfmeThingBRD m_zcEase;
	Bool m_doingZoomCamera;
};

void W3DView::zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut)
{
	Int &duration = milliseconds;
	register W3DView *view = this;
	if (duration < 1) {
		duration = 1;
	}
	view->m_zcNumFrames = duration / TheAnimationMsPerStep;
	if (view->m_zcNumFrames < 1) {
		view->m_zcNumFrames = 1;
	}
	view->m_zcStartZoom = view->m_zoom;
	view->m_zcEndZoom = finalZoom;
	view->m_zcCurFrame = 0;
	view->m_doingZoomCamera = true;
	typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
	SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
	(view->m_zcEase.*setEase)(easeIn, easeOut, (Real)duration);
	if (duration == 1) {
		((Gen0073C970Owner *)view)->updateOneFrame();
	}
}
