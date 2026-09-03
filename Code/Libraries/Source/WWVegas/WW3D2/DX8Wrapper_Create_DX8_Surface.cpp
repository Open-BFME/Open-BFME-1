// cl: /DNDEBUG /MD /EHsc
// readable body of ?_Create_DX8_Surface@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
// DX8Wrapper::_Create_DX8_Surface(width, height, format, pool)
// retail 0x00904CE0. BFME wraps D3D9 CreateOffscreenPlainSurface (vtable +0x90)
// on the D3D8-typed device pointer and bumps the DX8 call counter.

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN_00904CE0
};

enum _D3DPOOL
{
	D3DPOOL_DEFAULT_00904CE0
};
typedef _D3DPOOL D3DPOOL;

class IDirect3DSurface9;
struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *reserved[36];
	long (__stdcall *CreateOffscreenPlainSurface)(
		IDirect3DDevice8 *self,
		unsigned width,
		unsigned height,
		WW3DFormat format,
		D3DPOOL pool,
		IDirect3DSurface9 **ppSurface,
		void *sharedHandle);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Create_DX8_Surface(
		unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);

private:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned D3DCallCount;
};

// ?_Create_DX8_Surface@DX8Wrapper@@SAPAVIDirect3DSurface9@@IIW4WW3DFormat@@W4_D3DPOOL@@@Z
IDirect3DSurface9 *DX8Wrapper::_Create_DX8_Surface(
	unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool)
{
	IDirect3DSurface9 *surface = 0;
	D3DDevice->lpVtbl->CreateOffscreenPlainSurface(
		D3DDevice, width, height, format, pool, &surface, 0);
	++D3DCallCount;
	return surface;
}
