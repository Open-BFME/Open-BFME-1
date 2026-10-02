// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD
#include "dx8wrapper.h"

// readable body of ?postRender@ScreenDefaultFilter@@: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
//
// Retail 0x007D46D0: ScreenDefaultFilter::postRender.  BFME passes Coord2D by
// value (ret 10h) and draws the fullscreen blit through a helper instead of
// inlining DrawPrimitiveUP.  Twin: ZH W3DShaderManager.cpp postRender.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

	BfmeDevice *dev = reinterpret_cast<BfmeDevice *>(DX8Wrapper::_Get_D3D_Device8());
	dev->vt->SetTexture(dev, 0, tex);

	Coord2D uv;
	uv.x = 1.0f;
	uv.y = 1.0f;
	bfmeDrawFilterUV(-1, 0, &uv);
	reset();
	return true;
}
