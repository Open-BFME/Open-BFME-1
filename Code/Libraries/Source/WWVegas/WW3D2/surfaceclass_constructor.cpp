// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??0SurfaceClass@@: Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.cpp

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Create_DX8_Surface(
		unsigned width, unsigned height, WW3DFormat format, D3DPOOL pool);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
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
