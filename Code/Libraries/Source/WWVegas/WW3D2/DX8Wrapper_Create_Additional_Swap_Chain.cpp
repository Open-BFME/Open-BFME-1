// cl: /DNDEBUG /MD /EHsc
// readable body of ?Create_Additional_Swap_Chain@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
// DX8Wrapper::Create_Additional_Swap_Chain retail 0x00905620.
// ZH windowed D3DPRESENT_PARAMETERS fill plus D3D9 CreateAdditionalSwapChain
// (vtable +0x34). SwapEffect is D3DSWAPEFFECT_COPY (3), not the D3D8 VSYNC alias.

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

struct IDirect3DSwapChain8;
struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *reserved[13];
	long (__stdcall *CreateAdditionalSwapChain)(
		IDirect3DDevice8 *self,
		D3DPRESENT_PARAMETERS *params,
		IDirect3DSwapChain8 **ppSwapChain);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

enum
{
	D3DSWAPEFFECT_COPY = 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static IDirect3DSwapChain8 *Create_Additional_Swap_Chain(void *render_window);

private:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned D3DCallCount;
	static D3DPRESENT_PARAMETERS _PresentParameters;
};

// ?Create_Additional_Swap_Chain@DX8Wrapper@@SAPAUIDirect3DSwapChain8@@PAX@Z
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
