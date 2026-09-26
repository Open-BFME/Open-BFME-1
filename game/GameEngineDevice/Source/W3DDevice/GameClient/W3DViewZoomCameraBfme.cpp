// BFME W3DView::zoomCamera, retail 0x0073FC40.
// The constructor at 0x00745B10 places this state at +0x208 and its active
// flag at +0x228. The duration-one path calls zoomCameraOneFrame through the
// thunk at 0x0002ACA2, which separates this body from cameraUpdate at
// 0x0073FDD0.

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
	virtual void zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut);

private:
	void zoomCameraOneFrame();

	char m_padding0000[0x38];
	Real m_zoom;
	char m_padding0040[0x208 - 0x40];
	Int m_zcNumFrames;
	Int m_zcCurFrame;
	Real m_zcStartZoom;
	Real m_zcEndZoom;
	char m_padding0218[0x220 - 0x218];
	BfmeThingBRD m_zcEase;
	Bool m_doingZoomCamera;
};

void W3DView::zoomCamera(Real finalZoom, Int milliseconds, Real easeIn, Real easeOut)
{
	Int &duration = milliseconds;
	register W3DView *view = this;
	view->m_doingZoomCamera = true;
	if (duration < 1) {
		duration = 1;
	}
	Int frames = duration / TheAnimationMsPerStep;
	if (frames < 1) {
		frames = 1;
	}
	view->m_zcNumFrames = frames;
	view->m_zcStartZoom = view->m_zoom;
	view->m_zcEndZoom = finalZoom;
	view->m_zcCurFrame = 0;
	typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
	SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
	(view->m_zcEase.*setEase)(easeIn, easeOut, (Real)duration);
	if (duration == 1) {
		view->zoomCameraOneFrame();
	}
}
