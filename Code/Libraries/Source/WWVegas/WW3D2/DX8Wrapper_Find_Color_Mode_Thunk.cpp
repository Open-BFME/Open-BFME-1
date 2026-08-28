// cl: /DNDEBUG /MD /EHsc
// readable body of ?Find_Color_Mode@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp
// Open-BFME5: lift the retail display-mode search to standalone C++.
#include <string.h>

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
protected:
	static IDirect3D8 *D3DInterface;
	static bool __cdecl Find_Color_Mode(_D3DFORMAT colorbuffer, int resx, int resy, UINT *mode);
};

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
