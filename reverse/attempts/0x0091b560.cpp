// ?Check_Texture_Format_Support@DX8Caps@@AAEXW4WW3DFormat@@ABU_D3DCAPS8@@@Z
// partial score=0.88 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Banked near-miss for Check_Texture_Format_Support @ 0x0091B560.
// Memset-105 path is byte-exact. Loop computes DXT FourCC as
// 0x315456A2-this+p but /O2 folds hash+p into a constant and clobbers edi.

class IDirect3D8;
typedef unsigned int UINT;
typedef unsigned int DWORD;
typedef long HRESULT;
typedef enum _D3DDEVTYPE { D3DDEVTYPE_HAL = 1 } D3DDEVTYPE;
typedef enum _D3DFORMAT { D3DFMT_UNKNOWN = 0 } D3DFORMAT;
typedef enum _D3DRESOURCETYPE { D3DRTYPE_TEXTURE = 3 } D3DRESOURCETYPE;
struct D3DCAPS8 { D3DDEVTYPE DeviceType; UINT AdapterOrdinal; };
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
class StringClass;
class DX8Caps
{
	void Check_Texture_Format_Support(WW3DFormat display_format, const D3DCAPS8 &caps);
};

struct BFME_DX8Caps_CheckTextureFormatFields
{
	char pad[0x13e];
	bool supportTextureFormat[105];
	char padAfterFormats[0x2a0 - 0x1a7];
	IDirect3D8 *direct3D;
};

typedef HRESULT (__stdcall *CheckDeviceFormatProc)(
	IDirect3D8 *d3d, UINT Adapter, D3DDEVTYPE DeviceType,
	D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);

void DX8Caps::Check_Texture_Format_Support(WW3DFormat display_format, const D3DCAPS8 &caps)
{
	bool *p = ((BFME_DX8Caps_CheckTextureFormatFields *)this)->supportTextureFormat;
	if (display_format == WW3D_FORMAT_UNKNOWN) {
		memset(p, 0, 105);
		return;
	}

	unsigned hash = 0x315456A2u - (unsigned)this;
	unsigned i = 0;
	do {
		unsigned fmt;
		if (i < 100) {
			fmt = i;
		} else {
			fmt = hash + (unsigned)p;
		}
		IDirect3D8 *d3d = ((BFME_DX8Caps_CheckTextureFormatFields *)this)->direct3D;
		HRESULT hr = (*(CheckDeviceFormatProc **)d3d)[0x28 / 4](
			d3d, caps.AdapterOrdinal, caps.DeviceType,
			(D3DFORMAT)display_format, 0, D3DRTYPE_TEXTURE, (D3DFORMAT)fmt);
		*p = ((int)hr >= 0);
		++p;
		++i;
	} while (i < 105);
}
