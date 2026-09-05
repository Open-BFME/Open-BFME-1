// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5 near-twin conversion.
// Twin: ?Set_Vertex_Shader_Constant@DX8Wrapper@@SAXHPBXH@Z @ 0x0071BEB0
//       (Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp, matched via
//       object-symbol on the same inline body dx8wrapper.h defines).
//
// This is DX8Wrapper::Set_Pixel_Shader_Constant, the sibling inline in the
// same header (dx8wrapper.h:756). Retail's device vtable slot for
// SetPixelShaderConstant is +0x1B4 (index 109); neither dx8wrapper.cpp's own
// D3D8 header (index 106, +0x1A8) nor reference/shims/d3d8_shim_validated.h
// (index 107, +0x1AC) land on that exact slot for this pair, so this
// TU-scoped interface just declares the 109 preceding vtable slots as
// anonymous placeholders and the real method at the slot retail calls. The
// extern globals below name-mangle identically to DX8Wrapper's real static
// members regardless of which header declared them.
#include <string.h>

struct IDirect3DDevice8
{
	virtual void __stdcall dummy000() = 0;
	virtual void __stdcall dummy001() = 0;
	virtual void __stdcall dummy002() = 0;
	virtual void __stdcall dummy003() = 0;
	virtual void __stdcall dummy004() = 0;
	virtual void __stdcall dummy005() = 0;
	virtual void __stdcall dummy006() = 0;
	virtual void __stdcall dummy007() = 0;
	virtual void __stdcall dummy008() = 0;
	virtual void __stdcall dummy009() = 0;
	virtual void __stdcall dummy010() = 0;
	virtual void __stdcall dummy011() = 0;
	virtual void __stdcall dummy012() = 0;
	virtual void __stdcall dummy013() = 0;
	virtual void __stdcall dummy014() = 0;
	virtual void __stdcall dummy015() = 0;
	virtual void __stdcall dummy016() = 0;
	virtual void __stdcall dummy017() = 0;
	virtual void __stdcall dummy018() = 0;
	virtual void __stdcall dummy019() = 0;
	virtual void __stdcall dummy020() = 0;
	virtual void __stdcall dummy021() = 0;
	virtual void __stdcall dummy022() = 0;
	virtual void __stdcall dummy023() = 0;
	virtual void __stdcall dummy024() = 0;
	virtual void __stdcall dummy025() = 0;
	virtual void __stdcall dummy026() = 0;
	virtual void __stdcall dummy027() = 0;
	virtual void __stdcall dummy028() = 0;
	virtual void __stdcall dummy029() = 0;
	virtual void __stdcall dummy030() = 0;
	virtual void __stdcall dummy031() = 0;
	virtual void __stdcall dummy032() = 0;
	virtual void __stdcall dummy033() = 0;
	virtual void __stdcall dummy034() = 0;
	virtual void __stdcall dummy035() = 0;
	virtual void __stdcall dummy036() = 0;
	virtual void __stdcall dummy037() = 0;
	virtual void __stdcall dummy038() = 0;
	virtual void __stdcall dummy039() = 0;
	virtual void __stdcall dummy040() = 0;
	virtual void __stdcall dummy041() = 0;
	virtual void __stdcall dummy042() = 0;
	virtual void __stdcall dummy043() = 0;
	virtual void __stdcall dummy044() = 0;
	virtual void __stdcall dummy045() = 0;
	virtual void __stdcall dummy046() = 0;
	virtual void __stdcall dummy047() = 0;
	virtual void __stdcall dummy048() = 0;
	virtual void __stdcall dummy049() = 0;
	virtual void __stdcall dummy050() = 0;
	virtual void __stdcall dummy051() = 0;
	virtual void __stdcall dummy052() = 0;
	virtual void __stdcall dummy053() = 0;
	virtual void __stdcall dummy054() = 0;
	virtual void __stdcall dummy055() = 0;
	virtual void __stdcall dummy056() = 0;
	virtual void __stdcall dummy057() = 0;
	virtual void __stdcall dummy058() = 0;
	virtual void __stdcall dummy059() = 0;
	virtual void __stdcall dummy060() = 0;
	virtual void __stdcall dummy061() = 0;
	virtual void __stdcall dummy062() = 0;
	virtual void __stdcall dummy063() = 0;
	virtual void __stdcall dummy064() = 0;
	virtual void __stdcall dummy065() = 0;
	virtual void __stdcall dummy066() = 0;
	virtual void __stdcall dummy067() = 0;
	virtual void __stdcall dummy068() = 0;
	virtual void __stdcall dummy069() = 0;
	virtual void __stdcall dummy070() = 0;
	virtual void __stdcall dummy071() = 0;
	virtual void __stdcall dummy072() = 0;
	virtual void __stdcall dummy073() = 0;
	virtual void __stdcall dummy074() = 0;
	virtual void __stdcall dummy075() = 0;
	virtual void __stdcall dummy076() = 0;
	virtual void __stdcall dummy077() = 0;
	virtual void __stdcall dummy078() = 0;
	virtual void __stdcall dummy079() = 0;
	virtual void __stdcall dummy080() = 0;
	virtual void __stdcall dummy081() = 0;
	virtual void __stdcall dummy082() = 0;
	virtual void __stdcall dummy083() = 0;
	virtual void __stdcall dummy084() = 0;
	virtual void __stdcall dummy085() = 0;
	virtual void __stdcall dummy086() = 0;
	virtual void __stdcall dummy087() = 0;
	virtual void __stdcall dummy088() = 0;
	virtual void __stdcall dummy089() = 0;
	virtual void __stdcall dummy090() = 0;
	virtual void __stdcall dummy091() = 0;
	virtual void __stdcall dummy092() = 0;
	virtual void __stdcall dummy093() = 0;
	virtual void __stdcall dummy094() = 0;
	virtual void __stdcall dummy095() = 0;
	virtual void __stdcall dummy096() = 0;
	virtual void __stdcall dummy097() = 0;
	virtual void __stdcall dummy098() = 0;
	virtual void __stdcall dummy099() = 0;
	virtual void __stdcall dummy100() = 0;
	virtual void __stdcall dummy101() = 0;
	virtual void __stdcall dummy102() = 0;
	virtual void __stdcall dummy103() = 0;
	virtual void __stdcall dummy104() = 0;
	virtual void __stdcall dummy105() = 0;
	virtual void __stdcall dummy106() = 0;
	virtual void __stdcall dummy107() = 0;
	virtual void __stdcall dummy108() = 0;
	virtual long __stdcall SetPixelShaderConstant(unsigned reg, const void *data, unsigned count) = 0;
};

class Vector4
{
public:
	float X, Y, Z, W;
};

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Set_Pixel_Shader_Constant(int reg, const void *data, int count);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

private:
	static IDirect3DDevice8 *D3DDevice;
	static Vector4 Pixel_Shader_Constants[8];
};

// ?Set_Pixel_Shader_Constant@DX8Wrapper@@SAXHPBXH@Z
void DX8Wrapper::Set_Pixel_Shader_Constant(int reg, const void *data, int count)
{
	int memsize = sizeof(Vector4) * count;

	// may be incorrect if shaders are created and destroyed dynamically
	if (memcmp(data, &Pixel_Shader_Constants[reg], memsize) == 0)
		return;

	memcpy(&Pixel_Shader_Constants[reg], data, memsize);
	DX8Wrapper::_Get_D3D_Device8()->SetPixelShaderConstant(reg, data, count);
	number_of_DX8_calls++;
}
