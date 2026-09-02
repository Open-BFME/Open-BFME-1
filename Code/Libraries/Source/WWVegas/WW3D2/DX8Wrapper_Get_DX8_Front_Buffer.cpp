// cl: /DNDEBUG /MD /EHsc
// DX8Wrapper::_Get_DX8_Front_Buffer retail 0x00904FF0.
// ZH CreateImageSurface/GetFrontBuffer, BFME D3D9 GetDisplayMode(0),
// CreateOffscreenPlainSurface (A8R8G8B8, D3DPOOL_SCRATCH), GetFrontBufferData.

struct D3DDISPLAYMODE
{
	unsigned Width;
	unsigned Height;
	unsigned RefreshRate;
	unsigned Format;
};

class IDirect3DSurface9;
struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *reserved0[8];
	long (__stdcall *GetDisplayMode)(IDirect3DDevice8 *self, unsigned swapChain, D3DDISPLAYMODE *mode);
	void *reserved1[24];
	long (__stdcall *GetFrontBufferData)(IDirect3DDevice8 *self, unsigned swapChain, IDirect3DSurface9 *dest);
	void *reserved2[2];
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

enum
{
	D3DFMT_A8R8G8B8 = 21,
	D3DPOOL_SCRATCH = 3
};

class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();

private:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned D3DCallCount;
};

// ?_Get_DX8_Front_Buffer@DX8Wrapper@@SAPAVIDirect3DSurface9@@XZ
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
