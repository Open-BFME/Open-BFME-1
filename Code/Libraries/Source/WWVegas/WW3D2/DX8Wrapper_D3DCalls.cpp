// cl: /DNDEBUG /MD /EHsc
// readable body of ?Create_Additional_Swap_Chain@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
// readable body of ?_Create_DX8_Surface@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
// readable body of ?_Get_DX8_Front_Buffer@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
// readable body of ?Find_Color_Mode@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp

// The four DX8Wrapper entry points that reach straight through a Direct3D
// vtable: the swap-chain and surface creators at 0x00905620 and 0x00904CE0,
// the front-buffer grab at 0x00904FF0 and the display-mode search at
// 0x009021C0. Each bumps D3DCallCount once per call it makes.
//
// They sit outside dx8wrapper.cpp because each needs the raw COM layout, and
// they sit together because they need the SAME one -- three of them index the
// device vtable and one indexes the interface vtable.
#include <string.h>

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN_00904CE0
};

enum _D3DPOOL
{
	D3DPOOL_DEFAULT_00904CE0
};
typedef _D3DPOOL D3DPOOL;

typedef unsigned int UINT;
typedef long HRESULT;

enum _D3DFORMAT {};

struct D3DDISPLAYMODE
{
	UINT Width;
	UINT Height;
	UINT RefreshRate;
	_D3DFORMAT Format;
};

struct D3DPRESENT_PARAMETERS
{
	unsigned BackBufferWidth;
	unsigned BackBufferHeight;
	unsigned BackBufferFormat;
	unsigned BackBufferCount;
	unsigned MultiSampleType;
	unsigned MultiSampleQuality;
	unsigned SwapEffect;
	void *hDeviceWindow;
	int Windowed;
	int EnableAutoDepthStencil;
	unsigned AutoDepthStencilFormat;
	unsigned Flags;
	unsigned FullScreen_RefreshRateInHz;
	unsigned PresentationInterval;
};

class IDirect3DSurface9;
struct IDirect3DSwapChain8;
struct IDirect3DDevice8;

// Slot INDEX names each entry; the reserved runs between them are what proves
// the index. BFME links against D3D9 while keeping Zero Hour's D3D8 type names.
//   [8]  GetDisplayMode              +0x20
//   [13] CreateAdditionalSwapChain   +0x34
//   [33] GetFrontBufferData          +0x84
//   [36] CreateOffscreenPlainSurface +0x90
struct IDirect3DDevice8Vtbl
{
	void *reserved0[8];
	long (__stdcall *GetDisplayMode)(IDirect3DDevice8 *self, unsigned swapChain, D3DDISPLAYMODE *mode);
	void *reserved1[4];
	long (__stdcall *CreateAdditionalSwapChain)(
		IDirect3DDevice8 *self,
		D3DPRESENT_PARAMETERS *params,
		IDirect3DSwapChain8 **ppSwapChain);
	void *reserved2[19];
	long (__stdcall *GetFrontBufferData)(IDirect3DDevice8 *self, unsigned swapChain, IDirect3DSurface9 *dest);
	void *reserved3[2];
	long (__stdcall *CreateOffscreenPlainSurface)(
		IDirect3DDevice8 *self,
		unsigned width,
		unsigned height,
		unsigned format,
		unsigned pool,
		IDirect3DSurface9 **ppSurface,
		void *sharedHandle);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

class IDirect3D8;
struct IDirect3D8Vtbl
{
	void *reserved[6];
	UINT (__stdcall *GetAdapterModeCount)(IDirect3D8 *self, UINT adapter, _D3DFORMAT format);
	HRESULT (__stdcall *EnumAdapterModes)(IDirect3D8 *self, UINT adapter, _D3DFORMAT format, UINT mode, D3DDISPLAYMODE *displayMode);
};

class IDirect3D8
{
public:
	IDirect3D8Vtbl *lpVtbl;
};

enum
{
	D3DSWAPEFFECT_COPY = 3,			// not the D3D8 VSYNC alias
	D3DFMT_A8R8G8B8 = 21,
	D3DPOOL_SCRATCH = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static IDirect3DSwapChain8 *Create_Additional_Swap_Chain(void *render_window);
	static IDirect3DSurface9 *_Create_DX8_Surface(
		unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();

protected:
	// Protected, not private: retail mangles these as ?Find_Color_Mode@DX8Wrapper@@KA_N...
	// and ?D3DInterface@DX8Wrapper@@1PAVIDirect3D8@@A.
	static IDirect3D8 *D3DInterface;
	static bool __cdecl Find_Color_Mode(_D3DFORMAT colorbuffer, int resx, int resy, UINT *mode);

private:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned D3DCallCount;
	static D3DPRESENT_PARAMETERS _PresentParameters;
};

// ?Create_Additional_Swap_Chain@DX8Wrapper@@SAPAUIDirect3DSwapChain8@@PAX@Z
// Zero Hour's windowed present-parameter fill, then CreateAdditionalSwapChain.
IDirect3DSwapChain8 *DX8Wrapper::Create_Additional_Swap_Chain(void *render_window)
{
	D3DPRESENT_PARAMETERS params = { 0 };
	params.BackBufferFormat = _PresentParameters.BackBufferFormat;
	params.BackBufferCount = 1;
	params.MultiSampleType = 0;
	params.hDeviceWindow = render_window;
	params.SwapEffect = D3DSWAPEFFECT_COPY;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 1;
	params.AutoDepthStencilFormat = _PresentParameters.AutoDepthStencilFormat;
	params.Flags = 0;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	IDirect3DSwapChain8 *swap_chain = 0;
	D3DDevice->lpVtbl->CreateAdditionalSwapChain(D3DDevice, &params, &swap_chain);
	++D3DCallCount;
	return swap_chain;
}

// ?_Create_DX8_Surface@DX8Wrapper@@SAPAVIDirect3DSurface9@@IIW4WW3DFormat@@W4_D3DPOOL@@@Z
// BFME wraps D3D9's CreateOffscreenPlainSurface on the D3D8-typed device
// pointer where Zero Hour called CreateImageSurface.
IDirect3DSurface9 *DX8Wrapper::_Create_DX8_Surface(
	unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool)
{
	IDirect3DSurface9 *surface = 0;
	D3DDevice->lpVtbl->CreateOffscreenPlainSurface(
		D3DDevice, width, height, format, pool, &surface, 0);
	++D3DCallCount;
	return surface;
}

// ?_Get_DX8_Front_Buffer@DX8Wrapper@@SAPAVIDirect3DSurface9@@XZ
// ZH CreateImageSurface/GetFrontBuffer, BFME D3D9 GetDisplayMode(0),
// CreateOffscreenPlainSurface (A8R8G8B8, D3DPOOL_SCRATCH), GetFrontBufferData.
IDirect3DSurface9 *DX8Wrapper::_Get_DX8_Front_Buffer()
{
	D3DDISPLAYMODE mode;
	D3DDevice->lpVtbl->GetDisplayMode(D3DDevice, 0, &mode);
	++D3DCallCount;

	IDirect3DSurface9 *fb = 0;
	D3DDevice->lpVtbl->CreateOffscreenPlainSurface(
		D3DDevice, mode.Width, mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &fb, 0);
	++D3DCallCount;

	D3DDevice->lpVtbl->GetFrontBufferData(D3DDevice, 0, fb);
	++D3DCallCount;
	return fb;
}

// ?Find_Color_Mode@DX8Wrapper@@KA_NW4_D3DFORMAT@@HHPAI@Z
// The adapter's mode list is walked twice: once to find the first mode of the
// requested size and format, then on from there to find where that run ends.
bool __cdecl DX8Wrapper::Find_Color_Mode(_D3DFORMAT colorbuffer, int resx, int resy, UINT *mode)
{
	UINT i, j, modemax;
	UINT rx, ry;
	D3DDISPLAYMODE dmode;
	memset(&dmode, 0, sizeof(D3DDISPLAYMODE));

	rx = static_cast<UINT>(resx);
	ry = static_cast<UINT>(resy);
	bool found = false;
	modemax = D3DInterface->lpVtbl->GetAdapterModeCount(D3DInterface, 0, colorbuffer);

	i = 0;
	while (i < modemax && !found) {
		D3DInterface->lpVtbl->EnumAdapterModes(D3DInterface, 0, colorbuffer, i, &dmode);
		if (dmode.Width == rx && dmode.Height == ry && dmode.Format == colorbuffer)
			found = true;
		++i;
	}

	--i;
	if (!found)
		return false;

	bool stillok = true;
	j = i;
	while (j < modemax && stillok) {
		D3DInterface->lpVtbl->EnumAdapterModes(D3DInterface, 0, colorbuffer, j, &dmode);
		if (dmode.Width == rx && dmode.Height == ry && dmode.Format == colorbuffer)
			stillok = true;
		else
			stillok = false;
		++j;
	}

	if (!stillok)
		*mode = j - 2;
	else
		*mode = i;
	return true;
}
