// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN_008FC560
};

enum _D3DPOOL
{
	D3DPOOL_DEFAULT_008FC560
};
typedef _D3DPOOL D3DPOOL;

class IDirect3DSurface9;

class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Create_DX8_Surface(
		unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);
};

class SurfaceClass
{
public:
	SurfaceClass(unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);

private:
	IDirect3DSurface9 *D3DSurface;
};

SurfaceClass::SurfaceClass(unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool)
{
	D3DSurface = DX8Wrapper::_Create_DX8_Surface(width, height, format, pool);
}
