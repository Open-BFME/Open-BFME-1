// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DNDEBUG /MD
#include "dx8wrapper.h"

// readable body of ?postRender@ScreenDefaultFilter@@: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
//
// Retail 0x007D46D0: ScreenDefaultFilter::postRender.  BFME passes Coord2D by
// value (ret 10h) and draws the fullscreen blit through a helper instead of
// inlining DrawPrimitiveUP.  Twin: ZH W3DShaderManager.cpp postRender.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord2D.h"

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


// Retail reaches W3DShaderManager::endRenderToTexture (0x00717420) through
// the ILT at 0x0003FAC6 (?j_0003fac6@@YAXXZ); the call names that thunk.
extern void j_0003fac6();
static __forceinline void *callEndRenderToTexture()
{
	typedef void *(__cdecl *Call)();
	union { void (*asFunction)(); Call asCall; } fnCast;
	fnCast.asFunction = j_0003fac6;
	return fnCast.asCall();
}
// Retail calls 0x00716AD0 through ILT 0x000196A0.
void ShaderViewportRva00716AD0(int color, bool flag, const Coord2D *uv);

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
	void *tex = callEndRenderToTexture();
	if (!tex)
		return false;
	if (!set(mode))
		return false;

	BfmeDevice *dev = reinterpret_cast<BfmeDevice *>(DX8Wrapper::_Get_D3D_Device8());
	dev->vt->SetTexture(dev, 0, tex);

	Coord2D uv;
	uv.x = 1.0f;
	uv.y = 1.0f;
	ShaderViewportRva00716AD0(-1, false, &uv);
	reset();
	return true;
}
