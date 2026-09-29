// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DX8Wrapper::Set_Render_Target(IDirect3DSwapChain8*) lifted to standalone
// C++. Retail calls the swap chain's GetBackBuffer through vtable slot 0x14, one slot
// later than the stock D3D8 header (QueryInterface/AddRef/Release/Present/GetBackBuffer
// puts GetBackBuffer at 0x10); this build's IDirect3DSwapChain8 carries one extra
// reserved slot ahead of it, so the vtable below is a local replica shaped to match.

struct IDirect3DSurface8;
struct IDirect3DSwapChain8;

struct IDirect3DSurface8Vtbl
{
	void *QueryInterface;
	void *AddRef;
	long (__stdcall *Release)(IDirect3DSurface8 *self);
};

struct IDirect3DSurface8
{
public:
	IDirect3DSurface8Vtbl *lpVtbl;
};

struct IDirect3DSwapChain8Vtbl
{
	void *reserved[5];
	long (__stdcall *GetBackBuffer)(IDirect3DSwapChain8 *self, unsigned int backBuffer, int type, IDirect3DSurface8 **ppBackBuffer);
};

struct IDirect3DSwapChain8
{
public:
	IDirect3DSwapChain8Vtbl *lpVtbl;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSwapChain8 *swap_chain);
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);

private:
	// Retail static 0x01340548 (targets/game/reverse/dir32_addresses.csv records
	// ?IsRenderToTexture@DX8Wrapper@@0_NA).  MSVC encodes a data member's access
	// in the mangled name (private 0, protected 1, public 2), so this local
	// replica must declare it private to resolve to the recorded symbol.
	static bool IsRenderToTexture;
};

// ?Set_Render_Target@DX8Wrapper@@SAXPAUIDirect3DSwapChain8@@@Z
void DX8Wrapper::Set_Render_Target(IDirect3DSwapChain8 *swap_chain)
{
	//
	//	Get the back buffer for the swap chain
	//
	IDirect3DSurface8 *render_target = 0;
	swap_chain->lpVtbl->GetBackBuffer(swap_chain, 0, 0, &render_target);

	//
	//	Set this back buffer as the render targer
	//
	Set_Render_Target(render_target, true);

	//
	//	Release our hold on the back buffer
	//
	if (render_target != 0) {
		render_target->lpVtbl->Release(render_target);
		render_target = 0;
	}

	DX8Wrapper::IsRenderToTexture = false;
}
