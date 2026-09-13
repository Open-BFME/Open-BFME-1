// cl: /DNDEBUG /MD
// readable body of ?postRender@ScreenDefaultFilter@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
//
// Retail 0x007D46D0: ScreenDefaultFilter::postRender.  BFME passes Coord2D by
// value (ret 10h) and draws the fullscreen blit through a helper instead of
// inlining DrawPrimitiveUP.  Twin: ZH W3DShaderManager.cpp postRender.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	float x;
	float y;
};

struct BfmeDevice;
struct BfmeDeviceVt
{
	char pad[0x104];
	void (__stdcall *SetTexture)(BfmeDevice *self, int stage, void *tex);
};
struct BfmeDevice
{
	BfmeDeviceVt *vt;
};

extern "C" BfmeDevice *g_bfmeO1145;

void *__cdecl bfmeEndRenderToTexture(void);
void __cdecl bfmeDrawFilterUV(int a, int b, Coord2D *uv);

class ScreenDefaultFilter
{
public:
	virtual int init();
	virtual int shutdown();
	virtual bool preRender(bool &, int &);
	virtual bool postRender(int mode, Coord2D scroll, bool &extra);
	virtual bool setup(int);
	virtual int set(int mode);
	virtual void reset();
};

bool ScreenDefaultFilter::postRender(int mode, Coord2D scroll, bool &extra)
{
	void *tex = bfmeEndRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *dev = g_bfmeO1145;
	dev->vt->SetTexture(dev, 0, tex);

	Coord2D uv;
	uv.x = 1.0f;
	uv.y = 1.0f;
	bfmeDrawFilterUV(-1, 0, &uv);
	reset();
	return true;
}
