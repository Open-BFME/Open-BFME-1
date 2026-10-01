// cl: /DNDEBUG /MD /EHsc
// reset() (vtable slot 6, right after set) of the BFME screen filters whose
// set() bodies live in their own replica TUs:
//   ScreenZoomFilter    0x007D2230  vtable 0x011289D4
//   ScreenHilightFilter 0x007D7480  vtable 0x01128B88
//   Rva007D85C0         0x007D75E0  vtable 0x01128BAC
//   Rva007DCA80         0x007DB9D0  vtable 0x01128C5C
//   Rva007D1AA0         0x007D0C80  vtable 0x011289B0
//   Rva007D31C0         0x007D2310  vtable 0x01128A2C
// Like ScreenBWFilter::reset they clear stage 0 and the pixel shader through
// the D3D9 device (SetTexture slot 65, SetPixelShader slot 107), then tail
// into DX8Wrapper::Invalidate_Cached_Render_States. Only the zoom filter keeps
// ScreenBWFilter's texture-first order; the last two twins only clear the
// texture, like ScreenDefaultFilter::reset.

enum FilterModes { FM_NULL_MODE };

struct IDirect3DDevice8;

class DX8Wrapper
{
public:
	static void Invalidate_Cached_Render_States(void);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

protected:
	static IDirect3DDevice8 *D3DDevice;
};

typedef long (__stdcall *BfmeFilterSetTextureFn)(void *device, unsigned long stage, void *texture);
typedef long (__stdcall *BfmeFilterSetPixelShaderFn)(void *device, void *shader);

enum
{
	BFME_FILTER_SET_TEXTURE_SLOT = 65,
	BFME_FILTER_SET_PIXEL_SHADER_SLOT = 107
};

static __forceinline void filterSetTexture(unsigned long stage, void *texture)
{
	void *device = DX8Wrapper::_Get_D3D_Device8();
	(*(BfmeFilterSetTextureFn **)device)[BFME_FILTER_SET_TEXTURE_SLOT](device, stage, texture);
}

static __forceinline void filterSetPixelShader(void *shader)
{
	void *device = DX8Wrapper::_Get_D3D_Device8();
	(*(BfmeFilterSetPixelShaderFn **)device)[BFME_FILTER_SET_PIXEL_SHADER_SLOT](device, shader);
}

class ScreenZoomFilter
{
protected:
	virtual int set(FilterModes mode);
	virtual void reset(void);
};

class ScreenHilightFilter
{
protected:
	virtual int set(FilterModes mode);
	virtual void reset(void);
};

class Rva007D85C0
{
protected:
	virtual int set(FilterModes mode);
	virtual void reset(void);
};

class Rva007DCA80
{
protected:
	virtual int set(FilterModes mode);
	virtual void reset(void);
};

class Rva007D1AA0
{
protected:
	virtual int set(FilterModes mode);
	virtual void reset(void);
};

class Rva007D31C0
{
protected:
	virtual int set(FilterModes mode);
	virtual void reset(void);
};

void ScreenZoomFilter::reset(void)
{
	filterSetTexture(0, 0);
	filterSetPixelShader(0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}

void ScreenHilightFilter::reset(void)
{
	filterSetPixelShader(0);
	filterSetTexture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}

void Rva007D85C0::reset(void)
{
	filterSetPixelShader(0);
	filterSetTexture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}

void Rva007DCA80::reset(void)
{
	filterSetPixelShader(0);
	filterSetTexture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}

void Rva007D1AA0::reset(void)
{
	filterSetTexture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}

void Rva007D31C0::reset(void)
{
	filterSetTexture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}
