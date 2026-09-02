// ?postRender@ScreenZoomFilter@@UAE_NHUCoord2D@@AA_N@Z
// partial score=0.08 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Partial reconstruction of retail 0x007D5020. ScreenZoomFilter is BFME-only;
// Zero Hour has no twin. The confirmed entry skeleton ends the offscreen pass,
// invokes the filter's virtual set(mode), and requests the extra scene render.
// Identity/order evidence: init=0x007D2390, preRender=0x007D4A80,
// postRender=0x007D5020, following set-shaped body=0x007D62F0 (583 bytes).
// ABI evidence: retail ends in ret 10h, so Coord2D is by value, matching the
// already-landed ScreenDefaultFilter::postRender ABI.
// Retail skeleton: SEH frame, 0x138-byte locals, Set_Render_Target(NULL,true),
// virtual slot +0x14 set(mode), doExtraRender=true. It then computes viewport
// quad coordinates; uploads constants 0..7; sets cached render/texture states;
// constructs dynamic IB/VB access objects; draws two triangles; resets.

struct Coord2D
{
	float x;
	float y;
};

struct IDirect3DSurface8;

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *surface, bool useDefaultDepthBuffer);
};

class ScreenZoomFilter
{
public:
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &skipRender, int &scenePassMode);
	virtual bool postRender(int mode, Coord2D scrollDelta, bool &doExtraRender);
	virtual bool setup(int mode);

protected:
	virtual int set(int mode);
	virtual void reset();
};

class ZoomPostRenderUnwind
{
public:
	~ZoomPostRenderUnwind();
};

volatile int g_screenZoomPartialUnwind;

bool ScreenZoomFilter::postRender(int mode, Coord2D scrollDelta, bool &doExtraRender)
{
	ZoomPostRenderUnwind unwind;
	DX8Wrapper::Set_Render_Target(0, true);
	if (!set(mode))
		return false;

	doExtraRender = true;
	volatile float controlFlowSkeleton[77];
	try
	{
		controlFlowSkeleton[0] = scrollDelta.x;
		controlFlowSkeleton[1] = scrollDelta.y;
	}
	catch (...)
	{
		controlFlowSkeleton[0] = 0.0f;
	}
	return true;
}

ZoomPostRenderUnwind::~ZoomPostRenderUnwind()
{
	++g_screenZoomPartialUnwind;
}
